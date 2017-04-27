#include "Board.h"

Board::Board()
{
    //ctor
}

Board::~Board()
{
    //dtor
}

void Board::addCard(std::unique_ptr<Card> card)
{
    card->setHeight(m_height);
    CardCollection::addCard(std::move(card));
    arrangeCards();
}

void Board::setHeight(int height)
{
    std::list<std::unique_ptr<Card>>::iterator it;

    m_height = height;

    for (it = m_cards.begin(); it != m_cards.end(); it++)
    {
        (*it)->setHeight(m_height);
    }
    arrangeCards();
}

void Board::arrangeCards()
{
    std::list<std::unique_ptr<Card>>::iterator it;

    int gap = m_height*0.74;
    int s = m_cards.size();
    int i = 0;

    for (it = m_cards.begin(); it != m_cards.end(); it++)
    {
        int posx = gap/2.0 + i*gap - gap*(s/2.0);
        (*it)->setPosition(posx, 0);
        i++;
    }
}

void Board::clickEvent()
{
    std::list<std::unique_ptr<Card>>::const_iterator it;

    m_selectedCardId = m_hoveredCard;
}


void Board::update(sf::RenderWindow& window)
{
    std::list<std::unique_ptr<Card>>::const_iterator it;
    int i = 0;

    m_hoveredCard = -1;

    arrangeCards();

    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    int distanceMin = 100;

    for (it = m_cards.begin(); it != m_cards.end(); ++it)
    {
        //sf::FloatRect bounds = (**it).getBounds();

        int xpos = (*it)->getPosition().x + getPosition().x;

        int distance;

        if (m_reverted)
            distance = std::abs(-(*it)->getPosition().x + getPosition().x - mousePos.x);
        else
            distance = std::abs(xpos - mousePos.x);

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
            (*it)->setHeight(m_height*1.05);
        }
        else
        {
            (*it)->setHeight(m_height);
        }
        i++;
    }

    if (m_selectedCardId != -1)
    {
        //m_selectedCard = takeCard(m_selectedCardId);
        //m_cards.remove(takeCard(m_selectedCardId));
        //m_selectedCardId = -1;
    }
}

void Board::setReverted()
{
    m_reverted = true;
    setRotation(180);
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

    states.transform *= getTransform();
    //states.texture = NULL;
    std::list<std::unique_ptr<Card> >::const_iterator it;

    for(it = m_cards.begin(); it != m_cards.end(); ++it)
    {
        target.draw(**it, states);
    }

    if (m_selectedCardId != -1)
    {
        sf::Sprite highlight(Assets::getHighlight());
        highlight.setOrigin(350, 480);
        highlight.setPosition(getCard(m_selectedCardId).getPosition());
        highlight.setScale(m_height/880.0, m_height/880.0);
        target.draw(highlight, states);
        target.draw(getCard(m_selectedCardId), states);
    }
}
