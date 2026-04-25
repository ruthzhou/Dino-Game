module;
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <fstream>
#include <filesystem>
#include <ranges>
#include <mutex>
#include <future>
#include <iostream>
#include <string>
module Score;

namespace fs = std::filesystem;

// Static members need to be defined outside the class
std::vector<int> Score::pastScores;
std::mutex Score::scoreMutex;

// Constructor: Initializes fonts, score values, loads previous high score
Score::Score()
    : score(0), highScore(0), increaseInterval(1.0f),
    highScoreFile("highscore.txt"), playerName("Player"),
    highScorePlayerName("None"),
    font(new sf::Font()), scoreText(new sf::Text()), highScoreText(new sf::Text()), clock(new sf::Clock())
{
    if (!font->loadFromFile("C:/Windows/Fonts/BROADW.ttf")) {
        std::cerr << "Failed to load font!\n";
    }

    // Setup appearance and position of score display
    scoreText->setFont(*font);
    scoreText->setCharacterSize(50);
    scoreText->setFillColor(sf::Color::Black);
    scoreText->setPosition(3000.f, 170.f);

    // Setup high score display
    highScoreText->setFont(*font);
    highScoreText->setCharacterSize(50);
    highScoreText->setFillColor(sf::Color::Black);
    highScoreText->setPosition(3000.f, 90.f);

    loadHighScore(); // Load previous high score
    scoreText->setString("Score: 0");
    highScoreText->setString("High Score: " + std::to_string(highScore) + " by " + highScorePlayerName);

    clock->restart(); // Start timing
}

// Set current player's name
void Score::setPlayerName(const std::string& name) {
    playerName = name;
}

// Increase score every `increaseInterval` seconds, and update display
void Score::increase() {
    if (clock->getElapsedTime().asSeconds() >= increaseInterval) {
        score++;
        scoreText->setString("Score: " + std::to_string(score));

        // Update high score if needed
        if (score > highScore) {
            highScore = score;
            highScorePlayerName = playerName;
            highScoreText->setString("High Score: " + std::to_string(highScore) + " by " + highScorePlayerName);
            saveHighScore();
        }

        clock->restart(); // Restart timer
    }
}

// Reset current score and save result to file
void Score::reset() {
    saveScoreAsync(); // Save score in a new thread
    score = 0;
    scoreText->setString("Score: 0");
    clock->restart();
}

// Draw score and high score on screen
void Score::render(sf::RenderWindow& window) {
    window.draw(*scoreText);
    window.draw(*highScoreText);
}

// Read high score and name from file
void Score::loadHighScore() {
    std::ifstream inFile(highScoreFile);
    if (inFile.is_open()) {
        std::string line;
        if (std::getline(inFile, line)) {
            size_t pos = line.find_last_of(' ');
            if (pos != std::string::npos) {
                highScorePlayerName = line.substr(0, pos);
                try {
                    highScore = std::stoi(line.substr(pos + 1));
                }
                catch (...) {
                    highScore = 0;
                    highScorePlayerName = "None";
                }
            }
            else {
                highScorePlayerName = line;
                highScore = 0;
            }
        }
    }
    else {
        highScore = 0;
        highScorePlayerName = "None";
    }
}

// Save high score and name to file
void Score::saveHighScore() {
    std::ofstream outFile(highScoreFile);
    if (outFile.is_open()) {
        outFile << highScorePlayerName << " " << highScore << "\n";
    }
    else {
        std::cerr << "Failed to open high score file for writing\n";
    }
}

// Save current score asynchronously using a background thread, ensuring thread-safe access with a mutex.
void Score::saveScoreAsync() {
    auto name = playerName;
    auto scoreCopy = score;

    std::async(std::launch::async, [name, scoreCopy]() {
        std::lock_guard<std::mutex> lock(scoreMutex);
        fs::create_directory("scores");
        std::ofstream file("scores/scores.txt", std::ios::app);
        if (file) {
            file << name << " " << scoreCopy << "\n";
        }
        });
}
