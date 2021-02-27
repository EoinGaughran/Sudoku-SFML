////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Animation.h"

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

    sf::RectangleShape tux(sf::Vector2f(100.0f, 150.0f));
    
    tux.setTexture(&tuxTexture);
    tux.setOrigin(50.0f, 75.0f);
    tux.setPosition(width/2, height/2);

    Animation animation(&tuxTexture, sf::Vector2u(3, 9), 0.3f);

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

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
            tux.move(-0.1f, 0.0f);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)){
            tux.move(0.0f, -0.1f);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
            tux.move(0.0f, 0.1f);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
            tux.move(0.1f, 0.0f);
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            player.setPosition((float) mousePos.x, (float) mousePos.y);
        }

        animation.Update(0, deltaTime);
        tux.setTextureRect(animation.uvRect);

        window.clear(sf::Color(150, 150, 150));
        window.draw(player);
        window.draw(tux);
        window.display();
    }

    return EXIT_SUCCESS;
}