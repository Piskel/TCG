#ifndef ASSETS_H
#define ASSETS_H

#include <SFML/Graphics.hpp>
#include <unordered_map>

class Assets
{
    public:
        Assets();
        virtual ~Assets();

        static void load();
        static sf::Texture const& getTexture(std::string);
        static std::unordered_map<std::string, sf::Texture const&> getTextures();
        static sf::Font const& getCardsTitleFont();
        static sf::Font const& getCardsDescriptionFont();
        static sf::Texture const& getCardTextureNormal();
        static sf::Texture const& getCardTextureMonster();
        static sf::Texture const& getCardBack();
        static sf::Texture const& getCardTexture(int index);
        static sf::Texture const& getShinyTexture();
        static sf::Texture const& getShinyBackgroundTexture();
        static sf::Texture const& getHighlight();
    protected:
        static sf::Font m_cardsTitleFont;
        static sf::Font m_cardsDescriptionFont;
        static sf::Texture m_cardTextureNormal;
        static sf::Texture m_cardTextureMonster;
        static sf::Texture m_cardBack;
        static sf::Texture m_shinyTexture;
        static sf::Texture m_shinyBackgroundTexture;
        static sf::Texture m_highlightTexture;
        static std::vector<sf::Texture> m_cardTextures;
        std::unordered_map<std::string, sf::Texture> m_textures;

};

#endif // ASSETS_H
