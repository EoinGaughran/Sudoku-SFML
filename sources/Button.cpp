#include <SFML/Graphics.hpp>
#include "Button.h"

Button::Button(
        sf::Font font,
        sf::Vector2f cooard,
        sf::Color color,
        sf::Vector2f size,
        std::string wordValue,
        int wordSize
){

    background.setFillColor(color);
    background.setPosition(cooard);
    background.setSize(size);

    word.setPosition(cooard);
    word.setCharacterSize(wordSize);
    word.setString(wordValue);
    word.setColor(sf::Color::Black);
}

Button::~Button(){

}

void Button::Draw(sf::RenderWindow& window){

    window.draw(background);
    window.draw(word);
}