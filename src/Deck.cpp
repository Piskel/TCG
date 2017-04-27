#include "Deck.h"

#include <random>

Deck::Deck()
{
    //ctor
}

Deck::~Deck()
{
    //dtor
}

void Deck::shuffle(int n)
{
    int max = getCardCount();

    if (getCardCount() == 0)
        return;

    for (int i = 0; i < n; i++)
    {
        std::mt19937 rng;
        rng.seed(std::random_device()());
        std::uniform_int_distribution<std::mt19937::result_type> wow(0,max-1);

        std::unique_ptr<Card> tmp = CardCollection::takeCard(wow(rng));
        m_cards.push_back(std::move(tmp));
    }
}

void Deck::setHeight(int height)
{
    std::list<std::unique_ptr<Card> >::const_iterator it;
    int i = 0;
    for(it = m_cards.begin(); it != m_cards.end(); it++)
    {
        (**it).setHeight(height);

        i++;
    }
}

void Deck::arrangeCards()
{
    std::list<std::unique_ptr<Card> >::const_iterator it;
    int i = 0;
    for(it = m_cards.begin(); it != m_cards.end(); it++)
    {
        (**it).setPosition(0, -i*2);

        i++;
    }
}

std::unique_ptr<Card> Deck::takeCard()
{
    return CardCollection::takeCard(getCardCount()-1);
}

void Deck::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

    states.transform *= getTransform();
    //states.texture = NULL;
    for (unsigned int i = 0; i < getCardCount(); i++)
        target.draw(getCard(i), states);
}
