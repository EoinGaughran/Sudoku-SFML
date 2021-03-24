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
#include <Button.h>

static const float VIEW_HEIGHT = 550.0f;

const int MAIN_MENU = 0;
const int GAME_SCREEN = 1;
const int CHOICE_SCREEN = 2;
const int SETTINGS_SCREEN = 3;
const int HIGH_SCORES = 4;
const int INTERNET_CONNECT = 5;

const sf::Color BACKGROUND_COLOR = sf::Color(179,0,27);
const sf::Color BOARD_COLOR = sf::Color(55,30,48);
const sf::Color SQUARE_COLOR = sf::Color(151,239,223);
const sf::Color SELECTION_COLOR = sf::Color(250,243,62);
const sf::Color MENU_COLOR = sf::Color(246,130,140);
const sf::Color NUMBERS_COLOR = sf::Color(55,30,48);

const int height = 550;
const int width = 550;

float ResizeView(const sf::RenderWindow& window, sf::View& view){

    //float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(float(window.getSize().x), float(window.getSize().y));
    return float(window.getSize().y) / height;
}

int main()
{
    float resizeMultiplier = 1.0f;

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(width, height), "Sudoku SFML", sf::Style::Close | sf::Style::Resize);
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
    sf::Font fontBold;
    if (!font.loadFromFile("../../res/fonts/heebo/Heebo-Medium.ttf"))
    {
        // error...
    }

    if (!fontBold.loadFromFile("../../res/fonts/heebo/Heebo-Black.ttf"))
    {
        // error...
    }

    //Create Board
    //Board board(sf::Vector2u(9,9), sf::Vector2f(50.0f,50.0f), 1, font);

    Board board(9, sf::Vector2f(50.0f, 50.0f), 1, font);

    sf::RectangleShape black;
    black.setPosition(sf::Vector2f(45.0f,45.0f));
    black.setSize(sf::Vector2f(455.0f,455.0f));
    black.setFillColor(BOARD_COLOR);

    sf::RectangleShape shade;
    shade.setPosition(sf::Vector2f(0.0f,0.0f));
    shade.setSize(sf::Vector2f(600.0f,600.0f));
    shade.setFillColor(BOARD_COLOR);

    sf::Text choose;
    choose.setFillColor(sf::Color::White);
    choose.setFont(fontBold);
    choose.setCharacterSize(40);
    choose.setPosition(80,495);
    choose.setString("CHOOSE A NUMBER");

    int selection = 3;
    int numbers = 1;
    bool errorCheck = false;
    int bouncing = 10;
    bool mouseHasBeenPressed = false;
    bool keyHasBeenPressed = false;

    int screen = 0;

    //CHANGE THIS
    sf::Vector2u locator;

    //Selection Board
    std::vector<Square> selectionSquares;
    for(int i = 1 ; i <= selection ; i++ ){

        for(int j = 1 ; j <= selection; j++){

            selectionSquares.push_back(Square(
                sf::Color(255,255,255,150),
                sf::Vector2f(145.0f, 145.0f),
                sf::Vector2f((150.0f * j)-100.0f ,(150.0f * i)-100.0f),
                sf::Vector2u(j,i),
                font,
                100,
                numbers,
                7,
                true
            ));

            numbers++;
        }
    }

    //Main menu
    Button button(font, sf::Vector2f(200,300), sf::Color::White, sf::Vector2f(100, 50), "Start", 30);

    //Square square(nullptr, sf::Vector2f(100.0f,100.0f), sf::Vector2f(50.0f,50.0f), sf::Vector2u(0,0), font, 5, 7, true);

    // Create a clock for measuring the time elapsed
    sf::Clock clock;
    float deltaTime = 0.0f;

    // Start the game loop
    while (window.isOpen())
    {
        /*deltaTime = clock.restart().asSeconds();
        if(deltaTime > 1.0f / 20.0f)
            deltaTime = 1.0f / 20.0f;*/


        sf::Event game;
        while(window.pollEvent(game)){

            switch (game.type)
            {

            case sf::Event::Closed:

                window.close();
                break;

            case sf::Event::Resized:
                //std::cout << "New window width: " << game.size.width << " New window height: " << game.size.height << std::endl;
                printf("New window width: %i New window height %i\n", game.size.width, game.size.height);
                printf("Resize Multiplier: %f\n", resizeMultiplier);
                resizeMultiplier = ResizeView(window, view);
                board.updateSizeMultiplier(resizeMultiplier);

                break;

            /*case sf::Event::TextEntered:

                if (game.text.unicode < 128)
                    std::cout << "ASCII character typed: " << static_cast<char>(game.text.unicode) << std::endl;
                break;*/
            }

        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Y)){

            if(!keyHasBeenPressed){

                if(errorCheck) errorCheck = false;
                else errorCheck = true;

                keyHasBeenPressed = true;
            }
        }
        else keyHasBeenPressed = false;

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            
            //player.setPosition((float) mousePos.x, (float) mousePos.y);

            int i = 0;

            //mouse has been pressed - refuse Input
            if(!mouseHasBeenPressed){

                switch(screen){

                    case MAIN_MENU:

                        if(button.CheckButton(mousePos)){

                            screen = GAME_SCREEN;
                        }
                        
                        break;

                    case GAME_SCREEN:

                        //std::cout << "Locator X: " << locator.x << " Location Y: " << locator.y << "\n";

                        if(board.ClickCheck(mousePos)) screen = CHOICE_SCREEN;
                        
                        break;


                    case CHOICE_SCREEN:

                        for(Square& aSquare : selectionSquares){

                            if(aSquare.CheckButton(mousePos)){

                                std::cout << "Return Value: " << aSquare.getDisplayValue() << "\n";

                                board.getClickedSquare().setDisplayValue(aSquare.getDisplayValue());

                                screen = GAME_SCREEN;
                            }
                        }
                        break;
                }
                mouseHasBeenPressed = true;
            }
        }
        else{
            
            //mouse has been released - accept Input
            mouseHasBeenPressed = false;
        }

        sf::Vector2f direction;

        view.setCenter(player.getPosition());

        window.clear(BACKGROUND_COLOR);
        window.setView(view);

        window.draw(player);
        //tux.Draw(window);

        switch(screen){

            case MAIN_MENU:

                button.Draw(window);

                break;

            case GAME_SCREEN:

                window.draw(black); 
                
                board.CheckPositionOnBoard(mousePos);

                if(errorCheck) board.ErrorCheck();

                board.draw(window);

                break;

            case CHOICE_SCREEN:
            
                window.draw(shade);

                for(Square& aSquare : selectionSquares){

                    if(aSquare.CheckButton(mousePos))

                        aSquare.setColor(SELECTION_COLOR);

                    else aSquare.setColor(MENU_COLOR);

                    aSquare.Draw(window);
                    aSquare.Update(resizeMultiplier);
                }

                window.draw(choose);

                break;
            }

        window.display();
    }

    return EXIT_SUCCESS;
}