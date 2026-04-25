module;
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
module FlyingBird;

import Obstacle;

FlyingBird::FlyingBird(float x, float y, float speed)
    : Obstacle(x, y, speed), baseY(y), elapsedTime(0.f)
{
    if (!texture.loadFromFile("assets/bird1.png")) {
        std::cerr << "Failed to load bird1.png\n";
    }
    sprite.setTexture(texture);
    sprite.setScale(0.7f, 0.7f);
    sprite.setPosition(x, y);
}

void FlyingBird::update() {
    elapsedTime += 0.05f; // control oscillation speed
    float offsetY = std::sin(elapsedTime) * 10.f; // oscillate +-10 pixels vertically

    // Update Y position to oscillate around baseY
    float newY = baseY + offsetY;

    // Move left by speed and set Y to newY
    sprite.move(-speed, 0);
    sprite.setPosition(sprite.getPosition().x, newY);
}

bool FlyingBird::isOffScreen() const {
    return sprite.getPosition().x + sprite.getGlobalBounds().width < 0;
}
