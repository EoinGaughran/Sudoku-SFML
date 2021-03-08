#include <SFML/Graphics.hpp>
#include "Board.h"
#include <iostream>

Board::Board(sf::Vector2u size, sf::Vector2f cooards, int difficulty, sf::Font font) {

    std::cout << "Difficulty Set: " << difficulty << "\n";
    std::cout << "Board Size: (" << size.x << ", " << size.y << ")\n";

}

Board::~Board()
{
}

void Board::draw(sf::RenderWindow& window){

    //square.Update(window);
}