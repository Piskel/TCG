#ifndef CARDCOLLECTION_H
#define CARDCOLLECTION_H

#include <list>

#include "Card.h"

class CardCollection
{
    public:
        CardCollection();
        //CardCollection(CardCollection const& collection);

        //CardCollection& operator=(CardCollection const& card);
        //virtual ~CardCollection();

        void addCard(std::unique_ptr<Card> card);
        Card popCard(Card);

        std::list<std::unique_ptr<Card>> const& getCards() const; //rework the prototype. Const ref ?
        Card const& getCard(int index) const;
        std::unique_ptr<Card> takeCard(int index);
        Card* getCardPtr(int index);
        int getCardCount() const;

    protected:
        std::list<std::unique_ptr<Card>> m_cards;
};

#endif // CARDCOLLECTION_H
