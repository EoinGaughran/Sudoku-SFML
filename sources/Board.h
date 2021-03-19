#pragma once
#include <SFML/Graphics.hpp>
#include "Square.h"

class Board
{
private:

    Square *square;
    sf::Texture* texture;
    sf::Vector2f position;
    sf::Vector2u boardLocation;
    sf::Font font;
    int displayValue;
    int trueValue;
    int size;
    bool visable;

    int boardSize;

    std::vector<Square> squares;

    int sudokuNumbers [9][9] =
        {{ 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //1
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //2
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //3
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //4
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //5
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //6
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //7
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 }, //8
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 }}; //9
 

public:
    Board(int boardSize, sf::Vector2f cooards, int difficulty, sf::Font& font);
    ~Board();

    void draw(sf::RenderWindow& window);

    void CheckPositionOnBoard(sf::Vector2i mousePos);

    void ErrorCheck();

    sf::Vector2u ClickCheck(sf::Vector2i mousePos);

    std::vector<Square> getBoardSquares() { return squares; }

    bool isNumberValid(int col, int row, int potential);

    const sf::Color BACKGROUND_COLOR = sf::Color(179,0,27);
    const sf::Color BOARD_COLOR = sf::Color(55,30,48);
    const sf::Color SQUARE_COLOR = sf::Color(151,239,223);
    const sf::Color SELECTION_COLOR = sf::Color(250,243,62);
    const sf::Color MENU_COLOR = sf::Color(246,130,140);
    const sf::Color NUMBERS_COLOR = sf::Color(55,30,48);

};

