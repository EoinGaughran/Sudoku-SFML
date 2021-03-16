#include <SFML/Graphics.hpp>
#include "Button.h"

Button::Button(
        sf::Font& font,
        sf::Vector2f cooard,
        sf::Color color,
        sf::Vector2f size,
        std::string wordValue,
        int wordSize
){

    background.setFillColor(color);
    background.setPosition(cooard);
    background.setSize(size);

    word.setFont(font);
    word.setPosition(cooard);
    word.setCharacterSize(wordSize);
    word.setString(wordValue);
    word.setFillColor(sf::Color::Black);
}

Button::~Button(){

}

bool Button::CheckButton(sf::Vector2i mousePos){

    if(mousePos.x > background.getPosition().x &&
        mousePos.x < (background.getPosition().x + background.getSize().x) &&
        mousePos.y > background.getPosition().y &&
        mousePos.y < (background.getPosition().y + background.getSize().y)
    ){

        background.setFillColor(sf::Color::Red);

        return 1;
    }
    return 0;
}

void Button::Draw(sf::RenderWindow& window){

    window.draw(background);
    window.draw(word);
}