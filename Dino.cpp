module;
#include <iostream>
module Dino;

Dino::Dino() {
    if (!dinoTexture.loadFromFile("dino1.png")) {
        std::cerr << "Failed to load dino texture\n";
    }

    dinoSprite.setTexture(dinoTexture);
    dinoSprite.setScale(1.f, 1.f);             // Default scale
    dinoSprite.setPosition(100.f, 1650.f);     // Ground position

    isJumping = false;
    isDucking = false;
    jumpSpeed = -23.f;                         // Upward speed
    gravity = 0.15f;                           // Downward acceleration
    dinoYSpeed = 0.f;
}

// Handle space (jump) and down (duck) input
void Dino::move(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && !isJumping) {
        isJumping = true;
        dinoYSpeed = jumpSpeed;
    }
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) {
        isDucking = true;
        dinoSprite.setScale(1.f, 0.6f); // Shrink height
    }
    if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Down) {
        isDucking = false;
        dinoSprite.setScale(1.f, 1.f); // Return to normal height
    }
}

// Simulate gravity and landing
void Dino::update() {
    if (isJumping) {
        dinoSprite.move(0.f, dinoYSpeed);
        dinoYSpeed += gravity;

        // If landed, stop jumping
        if (dinoSprite.getPosition().y >= 1650.f) {
            dinoSprite.setPosition(dinoSprite.getPosition().x, 1650.f);
            isJumping = false;
            dinoYSpeed = 0.f;
        }
    }
}

// Render the dino
void Dino::draw(sf::RenderWindow& window) {
    window.draw(dinoSprite);
}

// Get collision bounds
sf::FloatRect Dino::getBounds() const {
    return dinoSprite.getGlobalBounds();
}

// Return ducking state for collision logic
bool Dino::getIsDucking() const {
    return isDucking;
}
