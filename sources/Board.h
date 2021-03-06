#pragma once
#include <SFML/Graphics.hpp>
#include "Square.h"

class Board
{
private:

    Square square;

public:
    Board(sf::Vector2u size, sf::Vector2f cooards, int difficulty, sf::Font font);
    ~Board();

    void draw(sf::RenderWindow& window);
};

