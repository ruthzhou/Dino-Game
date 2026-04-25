export module StartScreen;

import <SFML/Graphics.hpp>;
import <thread>;
import <chrono>;
import <fstream>;
import <sstream>;
import <algorithm>;

import Input; // Ensure this exports TextBox and InputValidator
import TextBox;
import Score;

export class StartScreen {
public:
    StartScreen(sf::Font& font);
    void run(sf::RenderWindow& window, std::string& username);

private:
    void centerText(sf::Text& text, float windowWidth, float y);
    void tryStartGame(sf::RenderWindow& window, bool& nameAccepted, std::string& username);
    void loadLeaderboardFromFile(const std::string& filename, const sf::Font& font);
    void drawScreen(sf::RenderWindow& window);

    // UI components
    TextBox textBox;
    sf::Text prompt;
    sf::Text feedback;
    sf::Text startText;
    sf::RectangleShape startButton;

    // Title and Dino graphic
    sf::Text titleText;
    sf::Texture dinoTexture;
    sf::Sprite dinoSprite;

    // High score display
    sf::Text highScoreText;

    // Leaderboard
    sf::RectangleShape leaderboardBox;
    sf::Text leaderboardLabel;
    std::vector<sf::Text> leaderboardEntries;

    // Score management
    Score score;
};
