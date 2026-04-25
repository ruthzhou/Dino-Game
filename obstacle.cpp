module Obstacle;

// Constructor sets the initial position of the obstacle sprite
Obstacle::Obstacle(float startX, float startY, float speed) : speed(speed) {
   sprite.setPosition(startX, startY);
}

// Moves the obstacle left by `speed` units
// If it moves off the left edge of the screen, wraps around to the right
void Obstacle::update() {
    sprite.move(-speed, 0);
}

// Draws the sprite to the given window
void Obstacle::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

// Returns the global bounding rectangle of the sprite for collision checks
sf::FloatRect Obstacle::getBounds() const {
    return sprite.getGlobalBounds();
}
