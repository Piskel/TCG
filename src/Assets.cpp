#include "Assets.h"
#include "Card.h"
#include <iostream>

sf::Font Assets::m_cardsTitleFont;
sf::Font Assets::m_cardsDescriptionFont;
sf::Texture Assets::m_cardTextureNormal;
sf::Texture Assets::m_cardTextureMonster;
sf::Texture Assets::m_cardBack;
sf::Texture Assets::m_shinyTexture;
sf::Texture Assets::m_shinyBackgroundTexture;
sf::Texture Assets::m_highlightTexture;

std::vector<sf::Texture> Assets::m_cardTextures;

Assets::Assets()
{

}

Assets::~Assets()
{
    //dtor
}

void Assets::load()
{
    std::cout << "Chargement des resources...\n";

    if(!m_cardsTitleFont.loadFromFile("assets/enchantedland.otf"))
        std::cout << "Impossible de charger la police de caractères.\n";

    if(!m_cardsDescriptionFont.loadFromFile("assets/tuerscardboard.ttf"))
        std::cout << "Impossible de charger la police de caractères.\n";

    m_cardTextures.resize(2);

    if(!m_cardTextures[NORMAL].loadFromFile("assets/img/layout.png"))
        std::cout << "Impossible de charger le canvas de la carte #mdr\n";

    if(!m_cardTextures[MONSTER].loadFromFile("assets/img/layout-monster.png"))
        std::cout << "Impossible de charger le canvas de la carte #mdr\n";

    if(!m_cardTextures[WIZARD].loadFromFile("assets/img/layout-magician.png"))
        std::cout << "Impossible de charger le canvas de la carte #mdr\n";



    if(!m_cardBack.loadFromFile("assets/img/back.png"))
        std::cout << "Impossible de charger le dos de la carte #mdr\n";

    if(!m_shinyTexture.loadFromFile("assets/img/shiny.png"))
        std::cout << "Impossible de charger le dos de la carte #mdr\n";

    if(!m_shinyBackgroundTexture.loadFromFile("assets/img/shiny-background.png"))
        std::cout << "Impossible de charger le dos de la carte #mdr\n";

    if(!m_highlightTexture.loadFromFile("assets/img/highlight.png"))
        std::cout << "Impossible de charger le highlight de la carte #mdr\n";

    std::cout << "Hola\n";
}

sf::Texture const& Assets::getCardTexture(int index)
{
    return m_cardTextures[index];
}

sf::Font const& Assets::getCardsTitleFont()
{
    return m_cardsTitleFont;
}

sf::Font const& Assets::getCardsDescriptionFont()
{
    return m_cardsDescriptionFont;
}
/*
sf::Texture const& Assets::getCardTextureNormal()
{
    return m_cardTextureNormal;
}

sf::Texture const& Assets::getCardTextureMonster()
{
    return m_cardTextureMonster;
}*/

sf::Texture const& Assets::getCardBack()
{
    return m_cardBack;
}

sf::Texture const& Assets::getShinyTexture()
{
    return m_shinyTexture;
}

sf::Texture const& Assets::getShinyBackgroundTexture()
{
    return m_shinyBackgroundTexture;
}

sf::Texture const& Assets::getHighlight()
{
    return m_highlightTexture;
}
