#include <SFML/Graphics.hpp>
#include "Square.h"

Square::Square(
    sf::Texture* texture,
    sf::Vector2f size,
    sf::Vector2f position,
    sf::Vector2u boardLocation,
    sf::Font& font,
    int displayValue,
    int trueValue,
    bool visable
) 
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

void Square::Draw(sf::RenderWindow& window){

    window.draw(background);
    window.draw(displayNumber);
}

void Square::Update(){

    sf::Vector2f velocity(0.0f, 0.0f); 

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        velocity.x -= 0.5f;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        velocity.x += 0.5f;

    displayNumber.move(velocity);
}

void Square::changeDisplayValue( int guess ){ displayValue = guess; }

bool Square::isTheValueCorrect(){ return displayValue == trueValue; }