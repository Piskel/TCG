#ifndef CARD_H
#define CARD_H

/**
* @class Card
*
* The base class for all Cards. Is virtual. Actually it's not, sorry.
*
* @file Card.h
*
*/

#include <SFML/Graphics.hpp>

#include "Assets.h"

enum{NORMAL, MONSTER, WIZARD};

class Card : public sf::Drawable, public sf::Transformable
{
    public:
        Card();
        Card(const Card&);
        Card(std::string name, int cost=1, int life=1, int defence=1, int stamina=1, int attack=1);
        virtual ~Card();

        Card& operator=(Card const& card);

        Card& copy() const;
        void init();

        static std::unique_ptr<Card> cardFactory(int id, int number=1); //some database interactions here

        int getCost() const;
        int getId() const;
        std::string getName() const;

        sf::Sprite const& getSprite() const;
        sf::FloatRect getBounds() const;

        void reveal();

        void setLife(int life);
        void setCost(int cost);
        void setName(std::string name);
        void setDescription(std::string description);

        void setShiny();

        void setTexture(sf::Texture *texture);
        void updateRenderTexture();

        void setHeight(int height);
        void setType(int type);

    private:
        void placeText();

        int m_id;
        std::string m_name;
        std::string m_description;
        int m_cost; //the mana cost of the card
        int m_life; //... seems obvious
        int m_defence;
        int m_stamina;
        int m_attack;

        int m_type = 0;

        bool m_hidden = true;
        bool m_shiny = false;

        std::array<sf::Text, 7> m_textDescription;

        float m_ratio = 1;

        sf::Sprite m_sprite;
        sf::Texture* m_cardTexture;
        sf::RenderTexture m_renderTexture;

        sf::Text m_nameText;
        sf::Text m_costText;


        //inherited from SFML. Allow the card to be an SFML-like entity
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            states.transform *= getTransform();
            //states.texture = NULL;
            target.draw(m_sprite, states);
        }
};

#endif // CARD_H
