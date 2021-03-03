#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Collider.h"

class Player
{
public:
    Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
    ~Player();

    void Update(float deltaTime);
    void Draw(sf::RenderWindow& window);

    void setPosition(sf::Vector2f position){ body.setPosition(position);};

    sf::Vector2f getPosition(){ return body.getPosition();}

    Collider GetCollider() { return Collider(body);}

private:

    sf::RectangleShape body;
    Animation animation;
    unsigned int row;
    float speed;
    bool faceRight;
};