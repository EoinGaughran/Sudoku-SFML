#include <SFML/Graphics.hpp>
#include "Square.h"

Square::Square(
    sf::Texture* texture,
    sf::Vector2f size,
    sf::Vector2f position,
    sf::Vector2u boardLocation,
    sf::Font font,
    int displayValue,
    int trueValue,
    bool visable
) : background(background)
{

    background.setTexture(texture);
    background.setSize(size);
    background.setPosition(position);

    displayNumber.setFont(font);
    displayNumber.setString(std::to_string(displayValue));
    displayNumber.setCharacterSize(24);
    displayNumber.setFillColor(sf::Color::Black);
    displayNumber.setPosition(position);
    //displayNumber.setStyle(sf::Text::Bold | sf::Text::Underlined);

    this->boardLocation = boardLocation;
    this->displayValue = displayValue;
    this->trueValue = trueValue;
}

Square::~Square()
{
}

bool Square::isTheValueCorrect(){

    return displayValue == trueValue;
}

void Square::changeDisplayValue(int guess){

    displayValue = guess;
}

void Square::Update(sf::RenderWindow& window){

    window.draw(displayNumber);
    window.draw(background);
}