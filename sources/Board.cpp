#include <SFML/Graphics.hpp>
#include "Board.h"
#include <iostream>

Board::Board(sf::Vector2u size, sf::Vector2f cooards, int difficulty, sf::Font font) :
square(nullptr, sf::Vector2f(100.0f,100.0f), cooards, sf::Vector2u(0,0), font, 5, 7, true)
{

    std::cout << "Difficulty Set: " << difficulty << "\n";
    std::cout << "Board Size: (" << size.x << ", " << size.y << ")\n";

    square = Square(nullptr, sf::Vector2f(100.0f,100.0f), cooards, sf::Vector2u(0,0), font, 5, 7, true);
}

Board::~Board()
{
}

void Board::draw(sf::RenderWindow& window){

    square.Update(window);
}