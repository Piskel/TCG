#ifndef HAND_H
#define HAND_H

#include <list>

#include "CardCollection.h"

class Hand: public CardCollection, public sf::Drawable, public sf::Transformable
{
    public:
        Hand();
        virtual ~Hand();

        void addCard(std::unique_ptr<Card> card);
        std::unique_ptr<Card> takeCard(int index);

        void sortCards();

        void clickEvent();
        std::unique_ptr<Card> getSelectedCard();

        void arrangeCards();
        void setHeight(int height);
        void update(sf::RenderWindow& window);


    private:
        //inherited from SFML. Allow the card to be an SFML-like entity
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        int m_hoveredCard = -1;
        int m_selectedCardId = -1;
        int m_height;

        std::unique_ptr<Card> m_selectedCard;
};

#endif // HAND_H
