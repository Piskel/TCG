#include "Game.h"
#include <iostream>
#include <stack>

Game::Game()
{
    //ctor
}

Game::~Game()
{
    //dtor
}

void Game::placeElements(sf::Vector2u screenSize)
{
    m_hand.setPosition(0.5 * screenSize.x, 0.85*screenSize.y);
    m_hand.setHeight(0.28*screenSize.y);

    m_board.setPosition(0.5*screenSize.x, 0.53*screenSize.y);
    m_board.setHeight(0.22*screenSize.y);

    //m_enemyBoard.setReverted();
    m_enemyBoard.setPosition(0.5*screenSize.x, 0.252*screenSize.y);
    m_enemyBoard.setHeight(0.22*screenSize.y);

}

void Game::gameLoop(sf::RenderWindow& app, Deck& m_deck)
{
    sf::Vector2u screenSize = app.getSize();

    m_deck.shuffle(10000);

    sf::Clock clock;

    std::stack<State> states;

    placeElements(screenSize);

    for(unsigned int i = 0; i < 3; i++)
    {
        std::unique_ptr<Card> c = m_deck.takeCard();
        c->reveal();
        m_enemyBoard.addCard(std::move(c));
    }
    m_deck.setHeight(0.28*screenSize.y);
    m_deck.arrangeCards();

    m_deck.setPosition(0.1 * screenSize.x, 0.85*screenSize.y);

    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("img/background.png");

    sf::Text fpsText;
    fpsText.setFont(Assets::getCardsTitleFont());

    sf::Sprite background(backgroundTexture);

    int i = 0;

    while (app.isOpen())
    {
        float fps = 1/clock.getElapsedTime().asSeconds();
        clock.restart();

        if (i%120 == 0)
        fpsText.setString(std::to_string(fps) + " fps");

        /*if (i % 20 == 0)
            text.setString(std::to_string(fps) + " fps - " + std::to_string(deck.getCardCount()) + " cartes dans le deck");*/

        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();

            if (event.type == sf::Event::MouseButtonReleased)
            {
                m_hand.clickEvent();
                m_board.clickEvent();
            }
            if (event.type == sf::Event::Resized)
            {
                //placeItems();
                app.setSize(sf::Vector2u(event.size.width, event.size.height));
                screenSize = app.getSize();
                std::cout << "Resize event: " << event.size.width << "px, " << event.size.height << "px\n";
                placeElements(sf::Vector2u(screenSize));
            }

            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Return)
                {
                    if (m_deck.getCardCount() > 0)
                        m_hand.addCard(m_deck.takeCard());
                }
            }
        }

        std::unique_ptr<Card> c = m_hand.getSelectedCard();
        if (c != nullptr)
        {
            c->setRotation(0);
            //c->setHeight(0.25*screenSize.y);
            m_board.addCard(std::move(c));
            m_board.arrangeCards();
            /*card->setRotation(0);
            card->setPosition(500, 250);*/
        }

        m_hand.update(app);
        m_board.update(app);
        m_enemyBoard.update(app);

        app.clear(sf::Color(170, 190, 220));

        app.draw(background);
        app.draw(m_board);
        app.draw(m_enemyBoard);
        app.draw(m_deck);

        //app.draw(mdr2);
        app.draw(m_hand);
        app.draw(fpsText);
        app.display();

        i++;
    }
}
