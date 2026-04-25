module;

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

module GameLoop;

// Constructor: Sets up the ground,pause button
GameLoop::GameLoop(sf::Font& font)
    : font(font),
    ground(sf::Vector2f(4000, 200)),
    playerText("", font, 50)

{
    ground.setFillColor(sf::Color(139, 69, 19));
    ground.setPosition(0, 1950);
    
    playerText.setFillColor(sf::Color::Black);
    playerText.setPosition(3000.f, 10.f);

    pauseButton.setSize(sf::Vector2f(120.f, 50.f));
    pauseButton.setPosition(20.f, 20.f);
    pauseButton.setFillColor(sf::Color(100, 100, 100));

    pauseButtonText.setFont(font);
    pauseButtonText.setCharacterSize(24);
    pauseButtonText.setFillColor(sf::Color::White);
    pauseButtonText.setPosition(35.f, 28.f);
}

// Runs the main game loop: handles input, updates entities, checks for collisions
void GameLoop::run(sf::RenderWindow& window, const std::string& username) {
    
    // Game Window and Player Setup
    window.create(sf::VideoMode(3825, 2200), "Dino Game");
    score.setPlayerName(username);
    score.loadHighScore();
    playerText.setString("Player: " + username);
    bool isGameRunning = true;

    //Main Game Loop
    while (window.isOpen()) {
        sf::Event event;
        // Event Handling (Keyboard, Mouse)
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::P)
                paused = !paused;
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (pauseButton.getGlobalBounds().contains(mousePos))
                    paused = !paused;
            }
            if (!paused)
                dino.move(event);
        }
        // Game Logic Updates
        if (isGameRunning && !paused) {
            dino.update();
            for (auto& obs : obstacles) obs.update();
            for (auto& bird : birds) bird.update();

            for (auto& obs : obstacles)
                if (dino.getBounds().intersects(obs.getBounds())) {
                    isGameRunning = false;
                    score.reset();
                    window.close();
                }

            for (auto& bird : birds)
                if (!dino.getIsDucking() && dino.getBounds().intersects(bird.getBounds())) {
                    isGameRunning = false;
                    score.reset();
                    window.close();
                }

            // Obstacle spawn every 2seconds, alternating
            if (obstacleClock.getElapsedTime().asSeconds() > 2.f) {
                float spawnX = 3825.f;

                if (lastObstacleWasBird) {
                    // Spawn cactus
                    obstacles.emplace_back(spawnX, 1750.f, 7.f);
                    lastObstacleWasBird = false;
                }
                else {
                    // Spawn bird
                    float randomY = 1300.f + rand() % 200;
                    birds.emplace_back(spawnX, randomY, 7.f);
                    lastObstacleWasBird = true;
                }

                obstacleClock.restart();
            }

            // Remove old obstacles
            obstacles.erase(std::remove_if(obstacles.begin(), obstacles.end(),
                [](const Cactus& obs) { return obs.isOffScreen(); }), obstacles.end());

            birds.erase(std::remove_if(birds.begin(), birds.end(),
                [](const FlyingBird& bird) { return bird.isOffScreen(); }), birds.end());

            //Increments the player's score every second if the game is running.
            if (scoreClock.getElapsedTime().asSeconds() >= 1.0f) {
                score.increase();
                scoreClock.restart();
            }
        }
        //Increments the player's score every second if the game is running.
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        pauseButton.setFillColor(
            pauseButton.getGlobalBounds().contains(mousePos) ? sf::Color(150, 150, 150) : sf::Color(100, 100, 100)
        );

        pauseButtonText.setString(paused ? "Resume" : "Pause");
        pauseButtonText.setPosition(pauseButton.getPosition().x + 15.f, pauseButton.getPosition().y + 10.f);

        //Draws the game background, all obstacles, the player, score, pause button,
        window.clear(sf::Color::Cyan);
        window.draw(ground);
        dino.draw(window);
        for (auto& obs : obstacles) obs.draw(window);
        for (auto& bird : birds) bird.draw(window);
        score.render(window);
        window.draw(playerText);
        window.draw(pauseButton);
        window.draw(pauseButtonText);
        window.display();
    }
}
