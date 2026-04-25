export module FlyingBird;

import <SFML/Graphics.hpp>;
import Obstacle;

export class FlyingBird : public Obstacle {
public:
    FlyingBird(float x, float y, float speed);
    void update() override;
    bool isOffScreen() const;
private:
    float baseY;       // base vertical position to oscillate around
    float elapsedTime; // track time for sine wave movement

};