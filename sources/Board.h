#pragma once
#include <SFML/Graphics.hpp>
#include "Square.h"

class Board
{
private:

    Square *square;
    sf::Texture* texture;
    sf::Vector2f size;
    sf::Vector2f position;
    sf::Vector2u boardLocation;
    sf::Font font;
    int displayValue;
    int trueValue;
    bool visable;

public:
    Board(sf::Vector2u size, sf::Vector2f cooards, int difficulty, sf::Font font);
    ~Board();

    void draw(sf::RenderWindow& window);
};

