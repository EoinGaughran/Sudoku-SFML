#pragma once 
#include <SFML/Graphics.hpp>
#include <string.h>

class Button
{
private:
    
    sf::Font font;
    sf::RectangleShape background;
    sf::Vector2f cooard;
    sf::Color color;
    sf::Vector2f size;
    std::string wordValue;
    sf::Text word;

public:

    Button(
        sf::Font& font,
        sf::Vector2f cooard,
        sf::Color color,
        sf::Vector2f size,
        std::string word,
        int wordSize
    );

    ~Button();

    bool CheckButton(sf::Vector2i mousePos);

    void Draw(sf::RenderWindow& window);
};