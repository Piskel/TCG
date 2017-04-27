#include "Card.h"

#include<iostream>

#include "split.h"

Card::Card()
{
    init();
    //houpla le vide
}

Card::Card(const Card& card)
{
    init();
    setName(card.getName());
    setCost(card.m_cost);
    setTexture(card.m_cardTexture);
    updateRenderTexture();
    setPosition(card.getPosition());
    setDescription(card.m_description);
    setType(card.m_type);
    if(card.m_shiny)
        setShiny();
}

Card::Card(std::string name, int cost, int life, int defence, int stamina, int attack)
{
    init();

    setName(name);
    setCost(cost);
    m_life = life;
    m_defence = defence;
    m_stamina = stamina;
    m_attack = attack;
}

Card::~Card()
{
    //dtor
}

Card& Card::operator=(Card const& card)
{
    return card.copy();
}

Card& Card::copy() const
{
    Card card;
    card.init();
    card.setName(getName());
    card.setCost(m_cost);
    card.setTexture(m_cardTexture);
    card.updateRenderTexture();
    card.setPosition(getPosition());
    card.setDescription(m_description);
    card.setType(m_type);
    //card.updateRenderTexture();
    if(m_shiny)
        card.setShiny();

    return card;
}

void Card::init()
{
    m_ratio = 1;

    m_cardTexture = nullptr;

    //Fonts
    m_nameText.setFont(Assets::getCardsTitleFont());
    m_costText.setFont(Assets::getCardsTitleFont());

    m_nameText.setCharacterSize(105);
    m_costText.setCharacterSize(90);

    m_nameText.setColor(sf::Color::Black);
    m_costText.setColor(sf::Color::White);

    m_textDescription[0].setStyle(sf::Text::Bold);

    //description
    for (unsigned int i = 0; i < m_textDescription.size(); i++)
    {
        //m_textDescription[i].setString("mdrrrr");
        m_textDescription[i].setFont(Assets::getCardsDescriptionFont());
        m_textDescription[i].setCharacterSize(32);
        m_textDescription[i].setColor(sf::Color::Black);

    }

    setDescription("No description");
}

std::string Card::getName() const
{
    return m_name;
}

sf::Sprite const& Card::getSprite() const
{
    return m_sprite;
}

sf::FloatRect Card::getBounds() const
{
    sf::FloatRect rect = m_sprite.getLocalBounds();
    rect.left += getPosition().x;
    rect.top += getPosition().y;
    return rect;
    //tg pierre
}

std::unique_ptr<Card> Card::cardFactory(int id, int number)
{
    // some database interaction right here right now

    return std::make_unique<Card>("Carte Neuve"); //c++14 <3
}

void Card::placeText()
{
    m_nameText.setPosition(m_renderTexture.getSize().x/2.0 - m_nameText.getLocalBounds().width/(2.0) + 25, -8);
    m_costText.setPosition(55.0, 8.0);

    for (unsigned int i = 0; i < m_textDescription.size(); i++)
        m_textDescription[i].setPosition(75, 450 + i*38);

}

void Card::reveal()
{
    m_hidden = false;
    updateRenderTexture();
}

void Card::updateRenderTexture()
{
    m_renderTexture.create(620, 880);

    sf::Sprite card;
    sf::Sprite shiny;
    sf::Sprite shinyBackground;

    if (m_hidden)
    {
        card.setTexture(Assets::getCardBack());
        m_renderTexture.clear(sf::Color::Transparent);
        m_renderTexture.draw(card);

        m_renderTexture.display();

        m_sprite.setTexture(m_renderTexture.getTexture());
        m_sprite.setOrigin(m_renderTexture.getSize().x/(2.0), m_renderTexture.getSize().y/(2.0));
        return;
    }

    if(m_shiny)
    {
        shiny.setTexture(Assets::getShinyTexture());
        shinyBackground.setTexture(Assets::getShinyBackgroundTexture());
        shinyBackground.setScale(1. + m_ratio/2, 1 + m_ratio/2);
        //shinyBackground.setRotation(-getRotation());
    }

    card.setTexture(Assets::getCardTexture(m_type));

    sf::Sprite image;

    if (m_cardTexture != nullptr)
        image.setTexture(*m_cardTexture);

    image.setPosition(80, 120);

    placeText();

    m_renderTexture.clear(sf::Color::Transparent);
    m_renderTexture.draw(card);

    if (m_shiny)
    {
        m_renderTexture.draw(shiny);
        m_renderTexture.draw(shinyBackground);
    }

    m_renderTexture.draw(image);
    m_renderTexture.draw(m_nameText);
    m_renderTexture.draw(m_costText);


    for (unsigned int i = 0; i < m_textDescription.size(); i++)
        m_renderTexture.draw(m_textDescription[i]);

    m_renderTexture.display();

    m_sprite.setTexture(m_renderTexture.getTexture());
    m_sprite.setOrigin(m_renderTexture.getSize().x/(2.0), m_renderTexture.getSize().y/(2.0));
}

//scaling the card
void Card::setHeight(int height)
{
    m_ratio = height/880.0;

    if (m_sprite.getScale().x != m_ratio)
    {
        m_sprite.setScale(m_ratio, m_ratio);
        updateRenderTexture();
    }
}

void Card::setName(std::string name)
{
    m_name = name;
    m_nameText.setString(name);
    updateRenderTexture();
}

void Card::setDescription(std::string description)
{
    m_description = description;
    std::vector<std::string> sub = split(description, '|');

    for (unsigned int i = 0; i < m_textDescription.size(); i++)
    {
        if (i < sub.size())
        {
            m_textDescription[i].setString(sub[i]);
        }
    }

    updateRenderTexture();
}

void Card::setShiny()
{
    m_shiny = true;
}


void Card::setCost(int cost)
{
    if (cost < 0)
        cost = 0;

    m_cost = cost;
    m_costText.setString(std::to_string(cost));
    updateRenderTexture();
}

void Card::setTexture(sf::Texture *texture)
{
    m_cardTexture = texture;
    updateRenderTexture();
    m_sprite.setOrigin(m_renderTexture.getSize().x/2, m_renderTexture.getSize().y/2); //setiing he origin at the center of the srpite
}

void Card::setType(int type)
{
    m_type = type;
    updateRenderTexture();
}
