export module Score;

import <SFML/Graphics.hpp>;
import <string>;
import <vector>;
import <mutex>;
import <fstream>;


// Score class manages the current score, high score, rendering, and persistence
export class Score {
private:
    int score;                           // Current player score
    int highScore;                       // Highest score ever achieved
    float increaseInterval;             // Time (in seconds) before score increases

    std::string highScoreFile;         // Path to store high score file
    std::string playerName;            // Name of current player
    std::string highScorePlayerName;   // Name of player with high score

    // Pointers to SFML objects used for rendering
    sf::Font* font;
    sf::Text* scoreText;
    sf::Text* highScoreText;
    sf::Clock* clock;                  // Timer used to increase score periodically

    static std::vector<int> pastScores;  // Stores old scores (if needed)
    static std::mutex scoreMutex;        // Mutex to prevent concurrent file access

public:
    Score();

    void loadHighScore();               // Read high score from file
    void saveHighScore();              // Save high score to file
    
    void saveScoreAsync();             // Save score in background

    void setPlayerName(const std::string& name); // Set current player's name
    void increase();                   // Increment score over time
    void reset();                      // Reset score after game ends
    void render(sf::RenderWindow& window); // Draw score on screen
    
    int getHighScore() const { return highScore; }
    std::string getHighScorePlayer() const { return highScorePlayerName; }


};
