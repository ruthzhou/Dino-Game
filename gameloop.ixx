export module GameLoop;

import <string>;
import <vector>;
import <SFML/Graphics.hpp>;
import Dino;
import Cactus;
import FlyingBird;
import Score;

export class GameLoop {
public:
    GameLoop(sf::Font& font);
    void run(sf::RenderWindow& window, const std::string& username);

private:
    Dino dino;
    Score score;

    sf::RectangleShape ground;
    sf::RectangleShape pauseButton;

    sf::Text playerText;//player username
    sf::Text pauseButtonText;//label inside pause button
    sf::Font& font;

    std::vector<Cactus> obstacles;
    std::vector<FlyingBird> birds;

    sf::Clock scoreClock; //Increases the score at regular intervals
    sf::Clock obstacleClock;//Controls when the next obstacle (cactus or bird) should spawn 

    bool paused = false; //True if the game is currently paused
    bool lastObstacleWasBird = false; //Tracks the type of the last spawned obstacle
   

};