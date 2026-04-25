module;

#include <iostream> 
module Cactus;

// Constructor loads the cactus texture and configures the sprite
Cactus::Cactus(float startX, float startY, float speed)
    : Obstacle(startX, startY, speed)
{
    if (!texture.loadFromFile("assets/cactus.png")) {
        std::cerr << "Failed to load cactus texture\n"; // Report if loading fails
    }

    sprite.setTexture(texture);           // Apply texture to sprite
    sprite.setScale(0.4f, 0.4f);          // Scale down the sprite for better fit
    sprite.setPosition(startX, startY);   // Set starting position
}


// Returns true if the cactus has fully moved off the screen to the left
bool Cactus::isOffScreen() const {
    return sprite.getPosition().x + sprite.getGlobalBounds().width < 0;
}
