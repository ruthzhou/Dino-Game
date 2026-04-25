module;
#include <thread>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <ranges>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

module StartScreen;
import Input;
import TextBox;
import Score;

// Constructor: Initializes UI elements and loads leaderboard data
StartScreen::StartScreen(sf::Font& font)
    : textBox(0, 0, 400, 60, font, 40),
    prompt("Enter Username:", font, 60),
    feedback("", font, 35),
    startText("Start", font, 42),
    startButton(sf::Vector2f(200, 60)),
    highScoreText("", font, 60),
    titleText("DINO GAME", font, 100),
    leaderboardLabel("LEADERBOARD", font, 60)
{
    // Load dino image
    if (!dinoTexture.loadFromFile("dino1.png")) {
        std::cerr << "Failed to load dino texture\n";
    }
    else {
        dinoSprite.setTexture(dinoTexture);
        dinoSprite.setScale(1.5f, 1.5f);
        dinoSprite.setPosition(1600.f, 250.f); // above the text area
    }

    // Title
    titleText.setFillColor(sf::Color::Black);
    centerText(titleText, 3825, 100);

    // High Score (top left)
    highScoreText.setFillColor(sf::Color::Black);
    highScoreText.setPosition(30.f, 110.f); // top-left corner

    // Leaderboard label box
    leaderboardLabel.setFillColor(sf::Color::Black);
    leaderboardLabel.setStyle(sf::Text::Bold);
    leaderboardBox.setSize(sf::Vector2f(600.f, 100.f));
    leaderboardBox.setFillColor(sf::Color(200, 200, 200));
    leaderboardBox.setOutlineColor(sf::Color::Black);
    leaderboardBox.setOutlineThickness(3.f);
    leaderboardBox.setPosition(3285.f, 110.f);
    leaderboardLabel.setPosition(3290.f, 115.f); // inside box

    // Prompt and feedback
    prompt.setFillColor(sf::Color::Black);
    feedback.setFillColor(sf::Color::Red);

    // Button styles
    startText.setFillColor(sf::Color::White);
    startButton.setFillColor(sf::Color(100, 200, 100));

    // Center interactive elements
    centerText(prompt, 3825, 800);
    textBox.setPosition((3825 - 400) / 2.f, 880.f);
    centerText(feedback, 3825, 960);
    startButton.setPosition((3825 - 200) / 2.f, 1040.f);
    centerText(startText, 3825, 1070.f);

    // Load leaderboard
    loadLeaderboardFromFile("scores/scores.txt", font);
}

// Reads and displays top 5 scores from a file
void StartScreen::loadLeaderboardFromFile(const std::string& filename, const sf::Font& font) {
    std::ifstream file(filename);
    if (!file.is_open()) return;

    std::vector<std::pair<std::string, int>> entries;
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name;
        int score;
        if (iss >> name >> score) {
            entries.emplace_back(name, score);
        }
    }

    std::ranges::sort(entries, [](const auto& a, const auto& b) {
        return a.second > b.second;
        });

    entries.resize(std::min<size_t>(5, entries.size()));

    float y = 250.f;
    for (const auto& [name, score] : entries) {
        sf::Text entry;
        entry.setFont(font);
        entry.setCharacterSize(40);
        entry.setFillColor(sf::Color::Black);
        entry.setString(name + " - " + std::to_string(score));
        entry.setPosition(3330.f, y);
        y += 40.f;
        leaderboardEntries.push_back(entry);
    }
}

// Centers any given sf::Text horizontally at the specified Y-coordinate
void StartScreen::centerText(sf::Text& text, float windowWidth, float y) {
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    text.setPosition(windowWidth / 2.f, y);
}

// Validates input and transitions to gameplay after displaying a short animation
void StartScreen::tryStartGame(sf::RenderWindow& window, bool& nameAccepted, std::string& username) {
    username = textBox.getInput();
    if (InputValidator::isValidUsername(username)) {
        feedback.setString("Starting game...");
        feedback.setFillColor(sf::Color::Black);
        centerText(feedback, 3825, 960);

        for (int i = 0; i < 3; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(400));
            feedback.setString("Starting game" + std::string(i + 1, '.'));
            centerText(feedback, 3825, 960);
            drawScreen(window);
        }

        nameAccepted = true;
    }
    else {
        feedback.setString("Invalid username. Must be 3–12 letters/digits.");
        feedback.setFillColor(sf::Color::Red);
        centerText(feedback, 3825, 960);
    }
}

// Draws all elements on the screen
void StartScreen::drawScreen(sf::RenderWindow& window) {
    window.clear(sf::Color::Cyan);

    window.draw(dinoSprite);
    window.draw(titleText);
    window.draw(prompt);
    textBox.draw(window);
    window.draw(startButton);
    window.draw(startText);
    window.draw(feedback);
    window.draw(highScoreText);
    window.draw(leaderboardBox);
    window.draw(leaderboardLabel);
    for (const auto& entry : leaderboardEntries)
        window.draw(entry);

    window.display();
}

// Runs the start screen loop until a valid username is entered
void StartScreen::run(sf::RenderWindow& window, std::string& username) {
    bool nameAccepted = false;
    textBox.setFocus(true);

    score.loadHighScore();
    highScoreText.setString("High Score: " + std::to_string(score.getHighScore()));

    while (window.isOpen() && !nameAccepted) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            textBox.handleEvent(event);

            if (event.type == sf::Event::MouseButtonPressed) {
                auto mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (startButton.getGlobalBounds().contains(mousePos)) {
                    tryStartGame(window, nameAccepted, username);
                }
            }

            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                tryStartGame(window, nameAccepted, username);
            }
        }

        drawScreen(window);
    }
}
