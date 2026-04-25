export module Obstacle;
import <SFML/Graphics.hpp>;

// Abstract base class representing a generic moving obstacle (e.g., cactus, bird)
export class Obstacle {
protected:
    sf::Sprite sprite;     // Sprite used for rendering the obstacle
    sf::Texture texture;   // Texture applied to the sprite
    float speed;           // Movement speed of the obstacle

public:
    // Constructor initializes position and speed
    Obstacle(float startX, float startY, float speed);

    virtual ~Obstacle() = default;

    // Virtual update method to move the obstacle (can be overridden)
    virtual void update();

    // Draws the obstacle on the window
    virtual void draw(sf::RenderWindow& window);

    // Returns the bounding box used for collision detection
    sf::FloatRect getBounds() const;
};
