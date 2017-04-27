#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include "Hand.h"
#include "Deck.h"
#include "Board.h"

enum State{IDLE, ATTACK, ANIMATION};

class Game
{
    public:
        Game();
        virtual ~Game();

        void placeElements(sf::Vector2u screenSize);
        void gameLoop(sf::RenderWindow& window, Deck& deck);

    protected:
    private:
        //Deck m_deck;
        Hand m_hand;
        Board m_board, m_enemyBoard;


};

#endif // GAME_H
