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
    sf::Text displayNumberSFText;

    sf::RectangleShape background;

    float resizeMultiplier = 1.0f;

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
    void setDisplayValue(int guess);
    void Draw(sf::RenderWindow& window);
    
    void Update( float resizeChange );

    sf::Vector2f getPosition() { return position; }
    int getDisplayValue() { return displayValue; }
    int getTrueValue() { return trueValue; }
    sf::Vector2u getMatrixPoint() { return boardLocation; }

    bool CheckButton(sf::Vector2i mousePos);

    void setColor( sf::Color color ) { background.setFillColor(color); }
};

