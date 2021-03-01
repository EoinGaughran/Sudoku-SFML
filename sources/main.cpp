////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <SFML/Graphics.hpp>
#include <iostream>
#include <Player.h>

#define GLAD_GL_IMPLEMENTATION
#include "gl.h"

#ifdef SFML_SYSTEM_IOS
#include <SFML/Main.hpp>
#endif

int main()
{
    int height = 480;
    int width = 640;

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(width, height), "SFML window with OpenGL", sf::Style::Close | sf::Style::Resize);

    float cubeSize = 48.0;
    
    sf::RectangleShape player(sf::Vector2f(cubeSize, cubeSize));
    //player.setFillColor(sf::Color::Red);
    player.setOrigin(cubeSize/2, cubeSize/2);

    sf::Texture texture;
    if (!texture.loadFromFile("../../res/textures/heart.png")){
        std::cout << "Image didn't load." << std::endl;
    }

    player.setTexture(&texture);
    player.setPosition(width/2, height/2);

    ////////////////
    //// TUX ///////
    ////////////////

    sf::Texture tuxTexture;
    tuxTexture.loadFromFile("../../res/textures/tux.png");

    Player tux(&tuxTexture, sf::Vector2u(3, 9), 0.3f, 100.0f);

    // Create a clock for measuring the time elapsed
    sf::Clock clock;
    float deltaTime = 0.0f;

    // Start the game loop
    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();

        sf::Event game;
        while(window.pollEvent(game)){

            switch (game.type)
            {

            case sf::Event::Closed:

                window.close();
                break;

            case sf::Event::Resized:
                //std::cout << "New window width: " << game.size.width << " New window height: " << game.size.height << std::endl;
                printf("New hhwindow width: %i New window height %i\n", game.size.width, game.size.height);
                break;

            case sf::Event::TextEntered:

                if (game.text.unicode < 128)
                    std::cout << "ASCII character typed: " << static_cast<char>(game.text.unicode) << std::endl;
            }
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            player.setPosition((float) mousePos.x, (float) mousePos.y);
        }

        tux.Update(deltaTime);

        window.clear(sf::Color(150, 150, 150));
        window.draw(player);
        tux.Draw(window);
        window.display();
    }

    return EXIT_SUCCESS;
}