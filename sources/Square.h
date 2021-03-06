#pragma once
#include <SFML/Graphics.hpp>

class Square
{
private:
    
    sf::Texture* texture;
    sf::Vector2f size;
    sf::Vector2f cooards;
    sf::Vector2u boardLocation;
    int displayValue;
    int trueValue;
    bool visable;
    sf::Text displayNumber;

    sf::RectangleShape background;

public:
    Square(
        sf::Texture* texture,
        sf::Vector2f size,
        sf::Vector2f position,
        sf::Vector2u boardLocation,
        sf::Font font,
        int displayValue,
        int trueValue,
        bool visable
    );

    ~Square();

    bool isTheValueCorrect();
    void changeDisplayValue(int guess);
    void Update(sf::RenderWindow& window);
};