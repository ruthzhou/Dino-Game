export module Dino;

import <SFML/Graphics.hpp>;

// Represents the dino player character (jumping and ducking)
export class Dino {
private:
    sf::Texture dinoTexture;
    sf::Sprite dinoSprite;

    bool isJumping;
    float jumpSpeed;
    float gravity;
    float dinoYSpeed;
    bool isDucking;

public:
    Dino();                                 // Load texture and set initial state
    void move(sf::Event& event);           // Handle input events
    void update();                         // Apply gravity / jump physics
    void draw(sf::RenderWindow& window);   // Draw dino on screen
    sf::FloatRect getBounds() const;       // Get bounds for collision
    bool getIsDucking() const;             // Access ducking state
};
