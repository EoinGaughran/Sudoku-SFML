#include <SFML/Graphics.hpp>
#include <iostream>
#include "Square.h"

Square::Square(
    sf::Color color,
    sf::Vector2f size,
    sf::Vector2f position,
    sf::Vector2u boardLocation,
    sf::Font& font,
    int fontSize,
    int displayValue,
    int trueValue,
    bool visable
) {
    background.setFillColor(color);
    background.setSize(size);
    background.setPosition(position);
    //background.setOrigin(background.getSize() / 2.0f);

    displayNumberSFText.setFont(font);
    displayNumberSFText.setString(std::to_string(displayValue));
    displayNumberSFText.setCharacterSize(fontSize);
    
    if(visable) displayNumberSFText.setFillColor(sf::Color(55,30,48));
    else displayNumberSFText.setFillColor(sf::Color::White);

    //displayNumber.setOrigin(sf::Vector2f(fontSize/2, fontSize/2));
    displayNumberSFText.setPosition((background.getPosition() + sf::Vector2f(12.0f, 2.0f)));

    //displayNumber.setStyle(sf::Text::Bold | sf::Text::Underlined);

    this->position = position;
    this->boardLocation = boardLocation;
    this->displayValue = displayValue;
    this->trueValue = trueValue;
}

Square::~Square()
{
}

void Square::Draw(sf::RenderWindow& window){

    window.draw(background);
    window.draw(displayNumberSFText);
}

bool Square::CheckButton(sf::Vector2i mousePos){

    /*std::cout << "mousePos.x: " << mousePos.x << "\n";
    std::cout << "mousePos.y: " << mousePos.y << "\n";
    std::cout << "background.x: " << background.getPosition().x << "\n";
    std::cout << "size.x: " << background.getPosition().x - background.getSize().x << "\n";
    std::cout << "background.y: " << background.getPosition().y << "\n";
    std::cout << "size.y: " << background.getPosition().y - background.getSize().y << "\n";*/

    if(mousePos.x > background.getPosition().x &&
        mousePos.x < (background.getPosition().x + background.getSize().x ) &&
        mousePos.y > background.getPosition().y &&
        mousePos.y < (background.getPosition().y + background.getSize().y )
    ){
        /*std::cout << "Position(" << boardLocation.x << "," << boardLocation.y << "): ";
        std::cout << displayValue;
        std::cout << " mousePos.x: " << mousePos.x;
        std::cout << " mousePos.y: " << mousePos.y << "\n";*/

        return 1;
    }
    return 0;
}

void Square::Update( float resizeChange ){

    sf::Vector2f velocity(0.0f, 0.0f);
    float speed = 0.4f;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        velocity.x -= speed;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        velocity.x += speed;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        velocity.y -= speed;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        velocity.y += speed;

    displayNumberSFText.move(velocity);
    background.move(velocity);

    if ( resizeChange != resizeMultiplier ) resizeMultiplier = resizeChange;
}

void Square::setDisplayValue( int guess ){

    displayValue = guess;
    displayNumberSFText.setString(std::to_string(guess));
}

bool Square::isTheValueCorrect(){ return displayValue == trueValue; }