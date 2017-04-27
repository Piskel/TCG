#ifndef DECK_H
#define DECK_H

#include <array>
#include <list>

#include "CardCollection.h"


class Deck: public CardCollection, public sf::Drawable, public sf::Transformable
{
    public:
        Deck();
        virtual ~Deck();

        Deck& operator=(Deck const& deck);

        void shuffle(int numberOfSwaps);
        void setHeight(int height);
        void arrangeCards();
        std::unique_ptr<Card> takeCard();

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif // DECK_H
