#include <iostream>

#include "Game.h"


int main()
{
    // Create the main window
    sf::ContextSettings settings;
    settings.antialiasingLevel = 16;

    sf::RenderWindow app(sf::VideoMode(1920, 1080), "Wow", sf::Style::Default, settings);
    app.setFramerateLimit(0);

    app.clear(sf::Color::Yellow);
    app.display();

    Assets::load();

    // Load a sprite to display
    sf::Texture textureBapt;
    if (!textureBapt.loadFromFile("assets/img/BAPT.jpg"))
        return EXIT_FAILURE;

    sf::Texture textureVampire;
    if (!textureVampire.loadFromFile("assets/img/vampire.png"))
        return EXIT_FAILURE;

    sf::Texture textureZombie;
    if (!textureZombie.loadFromFile("assets/img/zombie.jpg"))
        return EXIT_FAILURE;

    sf::Texture textureAlchimist;
    if (!textureAlchimist.loadFromFile("assets/img/alchimiste.png"))
        return EXIT_FAILURE;

    sf::Texture textureBack;
    if (!textureBack.loadFromFile("assets/img/back.png"))
        return EXIT_FAILURE;

    sf::Texture texturePoulet;
    if (!texturePoulet.loadFromFile("assets/img/poulet.png"))
        return EXIT_FAILURE;

    sf::Sprite deckSprite(textureBack);
    deckSprite.setScale(400/880.0, 400/880.0);
    deckSprite.setPosition(20, 500);

    Hand mdr;
    Board board;

    std::unique_ptr<Card> card = std::make_unique<Card>("Bonsoir");

    card->setPosition(sf::Vector2f(600, 450));
    card->setHeight(500);

    Card card2("Vampire");
    card2.setTexture(&textureVampire);
    card2.setDescription("Fuite|Quand cette carte est detruite, elle|retourne dans la main du joueur |l'ayant invoquee, mais elle coute|un mana de plus.");
    card2.setCost(3);
    card2.setType(MONSTER);

    Card poulet("Poulet Infernal");
    poulet.setTexture(&texturePoulet);
    poulet.setDescription("Fuite|Quand cette carte est detruite, elle|retourne dans la main du joueur |l'ayant invoquee, mais elle coute|un mana de plus.");
    poulet.setCost(8);
    poulet.setType(MONSTER);
    poulet.setShiny();

    Card zombie("Zombie");
    zombie.setTexture(&textureZombie);
    zombie.setDescription("Charge|Cette carte peut attaquer le tour|ou elle est posee.");
    zombie.setCost(2);
    zombie.setType(MONSTER);

    Card alchimist("Alchimiste");
    alchimist.setTexture(&textureAlchimist);
    alchimist.setDescription("Fabrication de potions|Genere un point de magie par tour.");
    alchimist.setCost(3);
    alchimist.setType(WIZARD);

    Card bapt("Baptiste");
    bapt.setTexture(&textureBapt);
    bapt.setPosition(sf::Vector2f(700, 450));
    bapt.setHeight(500);
    bapt.setCost(5);
    bapt.setDescription("Baptiste|Ajoute un bonus de cinq a votre|capital swag.");

    sf::Text text;
    text.setString("C'est tres le menu, bonsoir");
    text.setColor(sf::Color::White);
    text.setFont(Assets::getCardsTitleFont());

    mdr.addCard(std::make_unique<Card>(card2));
    mdr.addCard(std::make_unique<Card>("Salut"));
    mdr.addCard(std::make_unique<Card>(card2));
    //mdr.addCard(Card::cardFactory(1));
    mdr.addCard(std::make_unique<Card>(bapt));
    mdr.addCard(std::make_unique<Card>(zombie));
    //mdr.addCard(Card::cardFactory(1));
    mdr.addCard(std::make_unique<Card>(card2));
    //mdr.addCard(Card::cardFactory(1));

    Card salut = mdr.getCard(0);
    salut.getName();
    salut.setName("Bonsoir");
    Card mdr2 = mdr.getCard(0);
    mdr2.setPosition(400, 400);
    //salut.setPosition(400, 400);

    Deck deck;

    for (unsigned int i = 0; i < 5; i++)
        deck.addCard(std::make_unique<Card>(card2));
    for (unsigned int i = 0; i < 6; i++)
        deck.addCard(std::make_unique<Card>(zombie));
    for (unsigned int i = 0; i < 5; i++)
        deck.addCard(std::make_unique<Card>(bapt));
    for (unsigned int i = 0; i < 5; i++)
        deck.addCard(std::make_unique<Card>(alchimist));
    for (unsigned int i = 0; i < 2; i++)
        deck.addCard(std::make_unique<Card>(poulet));

    card2.setShiny();
    alchimist.setShiny();
    bapt.setShiny();

    deck.addCard(std::make_unique<Card>(card2));
    deck.addCard(std::make_unique<Card>(bapt));
    deck.addCard(std::make_unique<Card>(alchimist));
    //deck.shuffle(1000);

    Game game;
    game.gameLoop(app, deck);

    return EXIT_SUCCESS;
}
