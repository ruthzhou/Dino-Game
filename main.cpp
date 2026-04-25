#include <SFML/Graphics.hpp>
#include <thread>
#include <chrono>
#include <vector>
#include <string>
#include <algorithm> 
#include <iostream>
#include <filesystem>
import StartScreen;
import GameLoop;

int main() {
   
    // Create game window with 4K-like resolution
    sf::RenderWindow window(sf::VideoMode(3825,2200), "Dino Game");

    // Load font
    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/BROADW.ttf");

    std::string username;

    // Display start screen and get username input
    StartScreen startScreen(font);
    startScreen.run(window, username);

    if (!window.isOpen()) return 0;

    // Run main game loop
    GameLoop gameLoop(font);
    gameLoop.run(window, username);

    return 0;
}
