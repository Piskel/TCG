#ifndef BOARD_H
#define BOARD_H

#include "CardCollection.h"

class Board: public CardCollection, public sf::Drawable, public sf::Transformable
{
    public:
        Board();
        virtual ~Board();

        void addCard(std::unique_ptr<Card> card);
        void arrangeCards();

        void setReverted();

        void setHeight(int height);
        void clickEvent();
        void update(sf::RenderWindow& window);

    private:
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        int m_height = 880;
        int m_hoveredCard = -1;
        int m_selectedCardId = -1;
        bool m_reverted = false;
        std::unique_ptr<Card> m_selectedCard = nullptr;
};

#endif // BOARD_H
