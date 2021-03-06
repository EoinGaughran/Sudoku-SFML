////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <SFML/Graphics.hpp>
#include <iostream>
#include <Player.h>
#include <Platform.h>
#include <vector>
#include <Board.h>

static const float VIEW_HEIGHT = 512.0f;

void ResizeView(const sf::RenderWindow& window, sf::View& view){

    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main()
{
    int height = 480;
    int width = 640;

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(width, height), "SFML window with OpenGL", sf::Style::Close | sf::Style::Resize);
    sf::View view(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(VIEW_HEIGHT, VIEW_HEIGHT));

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
    int textureRows = 9;
    int textureColumns = 3;

    Player tux(
        &tuxTexture,
        sf::Vector2u(textureColumns,textureRows),
        0.3f,
        100.0f,
        200.0f
    );

    std::vector<Platform> platforms;

    platforms.push_back(Platform(
        nullptr,
        sf::Vector2f(400.0f, 200.0f),
        sf::Vector2f(700.0f, 200.0f)
    ));

    platforms.push_back(Platform(
        nullptr,
        sf::Vector2f(400.0f, 200.0f),
        sf::Vector2f(700.0f, 0.0f)
    ));

    platforms.push_back(Platform(
        nullptr,
        sf::Vector2f(1000.0f, 200.0f),
        sf::Vector2f(700.0f, 500.0f)
    ));

    tux.setPosition(sf::Vector2f(width/2, height/2));

    sf::Font font;
    if (!font.loadFromFile("../../res/fonts/heebo/Heebo-Medium.ttf"))
    {
        // error...
    }

    //Create Board
    Board board(sf::Vector2u(9,9), sf::Vector2f(50.0f,50.0f), 1, font);

    // Create a clock for measuring the time elapsed
    sf::Clock clock;
    float deltaTime = 0.0f;

    // Start the game loop
    while (window.isOpen())
    {
        deltaTime = clock.restart().asSeconds();
        if(deltaTime > 1.0f / 20.0f)
            deltaTime = 1.0f / 20.0f;

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
                ResizeView(window, view);

                break;

            case sf::Event::TextEntered:

                if (game.text.unicode < 128)
                    std::cout << "ASCII character typed: " << static_cast<char>(game.text.unicode) << std::endl;
                break;
            }
        }

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            player.setPosition((float) mousePos.x, (float) mousePos.y);
        }

        //Update players position first
        tux.Update(deltaTime);

        sf::Vector2f direction;

        for(Platform& platform : platforms)
            if(platform.GetCollision().CheckCollision(tux.GetCollider(), direction, 1.0f))
                tux.OnCollision(direction);

        //platform1.GetCollision().CheckCollision(tux.GetCollider(), 0.9f); //Heavy move
        //platform2.GetCollision().CheckCollision(tux.GetCollider(), 1.0f); //Unmoveable

        view.setCenter(tux.getPosition());

        window.clear(sf::Color(150, 150, 150));
        window.setView(view);

        window.draw(player);
        tux.Draw(window);
        board.draw(window);

        for(Platform& platform : platforms)
            if(platform.GetCollision().CheckCollision(tux.GetCollider(), direction, 1.0f))
                platform.Draw(window);
        
        window.display();
    }

    return EXIT_SUCCESS;
}