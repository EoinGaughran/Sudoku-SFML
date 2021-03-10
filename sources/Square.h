#pragma once
#include <SFML/Graphics.hpp>

class Square
{
private:

    sf::Vector2f position;
    sf::Vector2u boardLocation;
    int displayValue;
    int trueValue;
    bool visable;
    sf::Text displayNumber;

    sf::RectangleShape background;

public:
    Square(
        sf::Color color,
        sf::Vector2f size,
        sf::Vector2f position,
        sf::Vector2u boardLocation,
        sf::Font& font,
        int fontSize,
        int displayValue,
        int trueValue,
        bool visable
    );

    ~Square();

    bool isTheValueCorrect();
    void changeDisplayValue(int guess);
    void Draw(sf::RenderWindow& window);
    void Update();

    sf::Vector2f getPosition() { return position; }

    void CheckButton(sf::Vector2i mousePos);
};

