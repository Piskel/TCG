#include "Hand.h"

#include <iostream>
#include <cmath>

Hand::Hand()
{
    m_selectedCard = nullptr;
}

Hand::~Hand()
{
    //dtor
}

std::unique_ptr<Card> Hand::takeCard(int index)
{
    std::unique_ptr<Card> card = (CardCollection::takeCard(index));
    arrangeCards();
    return std::move(card);
}

void Hand::arrangeCards()
{
    float gap = 60;
    int cards = getCardCount();

    std::list<std::unique_ptr<Card>>::const_iterator it;
    int i = 0;

    for (it = m_cards.begin(); it != m_cards.end(); ++it)
    {
        (*it)->setPosition(gap/2-cards*gap/2 + i*gap, 0);
        (*it)->setRotation(0.05*(gap/2-cards*gap/2 + i*gap));
        i++;
    }
}

void Hand::addCard(std::unique_ptr<Card> card)
{
    card->reveal();
    CardCollection::addCard(std::move(card));
    arrangeCards();
}

void Hand::update(sf::RenderWindow& window)
{
    std::list<std::unique_ptr<Card>>::const_iterator it;
    int i = 0;

    m_hoveredCard = -1;

    //arrangeCards();

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    int distanceMin = 100;

    for (it = m_cards.begin(); it != m_cards.end(); ++it)
    {
        //sf::FloatRect bounds = (**it).getBounds();

        int xpos = (*it)->getPosition().x + getPosition().x;

        int distance = std::abs(xpos - mousePos.x);

        if ((distanceMin > distance) && (abs(getPosition().y - mousePos.y) < m_height/2.0))
        {
            m_hoveredCard = i;
            distanceMin = distance;
        }
        i++;
    }

    i = 0;

    for (it = m_cards.begin(); it != m_cards.end(); ++it)
    {
        if (m_hoveredCard == i)
        {
            (*it)->setHeight(m_height*1.6);
            (*it)->setPosition((*it)->getPosition().x, -0.3*m_height);
        }
        else
        {
            (*it)->setHeight(m_height);
            (*it)->setPosition((*it)->getPosition().x, 0);
        }
        i++;
    }

    if (m_selectedCardId != -1)
    {
        m_selectedCard = takeCard(m_selectedCardId);
        //m_cards.remove(takeCard(m_selectedCardId));
        m_selectedCardId = -1;
    }
}

void Hand::setHeight(int height)
{
    std::list<std::unique_ptr<Card>>::const_iterator it;

    for (it = m_cards.begin(); it != m_cards.end(); ++it)
    {
        (**it).setHeight(height);
    }

    m_height = height;

    arrangeCards();
}

void Hand::clickEvent()
{
    std::list<std::unique_ptr<Card>>::const_iterator it;

    m_selectedCardId = m_hoveredCard;
}

std::unique_ptr<Card> Hand::getSelectedCard()
{
    return std::move(m_selectedCard);
}

void Hand::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    //states.texture = NULL;
    for(unsigned int i = 0; i < getCardCount(); i++)
        target.draw(getCard(i), states);
    if (m_hoveredCard != -1 && m_hoveredCard < m_cards.size())
        target.draw(getCard(m_hoveredCard), states);
}
