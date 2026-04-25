
## Dino Game
A modern C++20 implementation of an endless runner game inspired by the classic offline dinosaur game in Google Chrome. The player controls a dinosaur that must jump and duck to avoid obstacles while the game progressively increases in difficulty.

## Game Overview
In this game, the player controls a dinosaur that runs automatically. The goal is to survive as long as possible by avoiding obstacles such as:

* Cacti
* Flying birds
The game speed increases over time, making it more challenging the longer you survive.

## Features

* Endless runner gameplay
* Jump and duck mechanics
* Dynamic obstacle generation
* Increasing difficulty over time
* Collision detection system
* Score tracking system
* Leaderboard support
* Start screen with username input and validation
* Pause and resume functionality
* Animated obstacles
  
## Technologies Used
* C++20
* SFML (graphics, input, window handling)
* Modular architecture using C++20 modules
* STL (vectors, algorithms, filesystem)
* Regex for input validation
* Multithreading (for game logic optimization)
  
## Project Structure
The project is organized into modular components:
* **GameLoop** – Core game logic and runtime control
* **Dino** – Player character logic (movement, jumping, ducking)
* **Obstacle / Cactus / FlyingBird** – Enemy entities
* **Score** – Score tracking and leaderboard system
* **StartScreen** – Menu and username handling
* **InputValidator** – Ensures valid player input
  
## How to Run
### 1. Clone the repository

```bash
git clone https://github.com/ruthzhou/Dino-Game.git
```
### 2. Open the project in Visual Studio or your preferred IDE
### 3. Build the project (C++20 required)
### 4. Run the executable

##Controls

* **Space / Up Arrow** → Jump
* **Down Arrow** → Duck
* **Esc** → Pause game

---

## Future Improvements

* Sound effects and background music
* Power-ups (shield, speed boost)
* Different environments (night mode, desert, etc.)
* Mobile version
* Improved animations
  
## Author
Developed by **Ruth Zhou**
* add screenshots section
* or simplify it for a school submission (short version)
