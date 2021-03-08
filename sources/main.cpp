////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include <SFML/Graphics.hpp>
#include <iostream>
#include <Player.h>
#include <Platform.h>
#include <vector>
#include <Board.h>
#include <Square.h>

static const float VIEW_HEIGHT = 640.0f;

void ResizeView(const sf::RenderWindow& window, sf::View& view){

    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main()
{
    int height = 640;
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

    /*sf::Texture tuxTexture;
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

    tux.setPosition(sf::Vector2f(width/2, height/2));*/

    sf::Font font;
    if (!font.loadFromFile("../../res/fonts/heebo/Heebo-Medium.ttf"))
    {
        // error...
    }

    //Create Board
    //Board board(sf::Vector2u(9,9), sf::Vector2f(50.0f,50.0f), 1, font);

    sf::RectangleShape black;
    black.setPosition(sf::Vector2f(45.0f,45.0f));
    black.setSize(sf::Vector2f(455.0f,455.0f));
    black.setFillColor(sf::Color::Black);

    int boardSize = 9;
    //int squareSize = 3;

    std::vector<Square> squares;

    /* initialize random seed: */
    srand (time(NULL));

    for(int i = 1 ; i <= boardSize ; i++ ){

        for(int j = 1 ; j <= boardSize ; j++){

            squares.push_back(Square(
                nullptr,
                sf::Vector2f(45.0f, 45.0f),
                sf::Vector2f(50.0f * i ,50.0f * j),
                sf::Vector2u(j,i),
                font,
                rand() % 9 + 1,
                7,
                true
            ));
        }
    }

    //Square square(nullptr, sf::Vector2f(100.0f,100.0f), sf::Vector2f(50.0f,50.0f), sf::Vector2u(0,0), font, 5, 7, true);

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
            //player.setPosition((float) mousePos.x, (float) mousePos.y);

            int i = 0;

            for(Square& aSquare : squares){
                aSquare.CheckButton(mousePos);
            }
        }

        sf::Vector2f direction;

        view.setCenter(player.getPosition());

        window.clear(sf::Color(150, 150, 150));
        window.setView(view);

        window.draw(player);
        //tux.Draw(window);
        window.draw(black);

        for(Square& aSquare : squares){
            aSquare.Draw(window);
            aSquare.Update();
        }
        
        window.display();
    }

    return EXIT_SUCCESS;
}