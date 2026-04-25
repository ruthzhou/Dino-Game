export module Cactus;
import Obstacle;

// Cactus is a type of ground obstacle derived from the base Obstacle class
export class Cactus : public Obstacle {
public:
    // Constructor sets position, speed, and loads cactus-specific texture
    Cactus(float startX, float startY, float speed);

    // Checks if the cactus has moved entirely off the left side of the screen
    bool isOffScreen() const;
};
