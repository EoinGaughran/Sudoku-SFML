#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"

class Player
{
public:
    Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f size);
    ~Player();

    void Update(float deltaTime);
    void Draw(sf::RenderWindow& window);

    void setPosition(sf::Vector2f position){ body.setPosition(position);};

    sf::Vector2f getPosition(){ return body.getPosition();}

private:

    sf::RectangleShape body;
    Animation animation;
    unsigned int row;
    float speed;
    bool faceRight;
};