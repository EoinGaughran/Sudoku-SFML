#include <SFML/Graphics.hpp>
#include <iostream>
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
) {
    background.setTexture(texture);
    background.setSize(size);
    background.setPosition(position);
    //background.setOrigin(background.getSize() / 2.0f);

    displayNumber.setFont(font);
    displayNumber.setString(std::to_string(displayValue));
    displayNumber.setCharacterSize(fontSize);
    displayNumber.setFillColor(sf::Color::Black);
    //displayNumber.setOrigin(sf::Vector2f(fontSize/2, fontSize/2));
    displayNumber.setPosition((background.getPosition() + sf::Vector2f(12.0f, 2.0f)));

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

void Square::CheckButton(sf::Vector2i mousePos){

    /*std::cout << "mousePos.x: " << mousePos.x << "\n";
    std::cout << "mousePos.y: " << mousePos.y << "\n";
    std::cout << "background.x: " << background.getPosition().x << "\n";
    std::cout << "size.x: " << background.getPosition().x - background.getSize().x << "\n";
    std::cout << "background.y: " << background.getPosition().y << "\n";
    std::cout << "size.y: " << background.getPosition().y - background.getSize().y << "\n";*/

    if(mousePos.x > background.getPosition().x &&
        mousePos.x < (background.getPosition().x + background.getSize().x) &&
        mousePos.y > background.getPosition().y &&
        mousePos.y < (background.getPosition().y + background.getSize().y)
    ){
        std::cout << displayValue << "\n";
        background.setFillColor(sf::Color::Red);
    }
}

void Square::Update(){

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

    displayNumber.move(velocity);
    background.move(velocity);

}

void Square::changeDisplayValue( int guess ){ displayValue = guess; }

bool Square::isTheValueCorrect(){ return displayValue == trueValue; }