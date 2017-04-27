#include "CardCollection.h"
#include <iostream>



CardCollection::CardCollection()
{
    //ctor
}

void CardCollection::addCard(std::unique_ptr<Card> card)
{
    m_cards.push_back(std::move(card));
}

Card const& CardCollection::getCard(int index) const
{
    std::list<std::unique_ptr<Card>>::const_iterator it;
    int i = 0;

    for (it = m_cards.begin(); it != m_cards.end(); ++it)
    {
        if (i == index)
        {
            return **it;
        }
        i++;
    }

    throw std::out_of_range("in a CardCollection object (get): index out of range: " + std::to_string(index) + ". List size: " + std::to_string(m_cards.size()));
}

std::unique_ptr<Card> CardCollection::takeCard(int index)
{
    std::list<std::unique_ptr<Card>>::iterator it;
    int i = 0;

    std::unique_ptr<Card> card = nullptr;

    for (it = m_cards.begin(); it != m_cards.end(); ++it)
    {
        if (i == index)
        {
            card = std::move(*it);
            m_cards.remove(*it);
            break;
        }
        i++;
    }

    if (card != nullptr)
    {
        return std::move(card);
    }
    else
        throw std::out_of_range("in a CardCollection object (take): index out of range: " + std::to_string(index) + ". List size: " + std::to_string(m_cards.size()));
}

Card* CardCollection::getCardPtr(int index)
{
    std::list<std::unique_ptr<Card>>::const_iterator it;
    int i = 0;

    for (it = m_cards.begin(); it != m_cards.end(); ++it)
    {
        if (i == index)
        {
            return &**it; //cheating ?
        }
        i++;
    }

    throw std::out_of_range("in a CardCollection object (getPtr): index out of range: " + std::to_string(index) + ". List size: " + std::to_string(m_cards.size()));
}

int CardCollection::getCardCount() const
{
    return m_cards.size();
}
