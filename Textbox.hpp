#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class TextBox {
private:
    sf::RectangleShape box;
    sf::Text text;
    sf::Text cursor;
    sf::Clock cursorTimer;
    bool isFocused = true;
    std::string input;

public:
    TextBox(float x, float y, float width, float height, sf::Font& font, unsigned int fontSize = 36) {
        box.setSize({ width, height });
        box.setPosition(x, y);
        box.setFillColor(sf::Color::White);
        box.setOutlineColor(sf::Color::Black);
        box.setOutlineThickness(3);

        text.setFont(font);
        text.setCharacterSize(fontSize);
        text.setFillColor(sf::Color::Black);
        text.setPosition(x + 10, y + (height - fontSize) / 2);

        cursor.setFont(font);
        cursor.setCharacterSize(fontSize);
        cursor.setString("|");
        cursor.setFillColor(sf::Color::Black);
        updateCursor();
    }

    void handleEvent(sf::Event event) {
        if (event.type == sf::Event::TextEntered && isFocused) {
            if (event.text.unicode == '\b') {
                if (!input.empty()) {
                    input.pop_back();
                    text.setString(input);
                }
            }
            else if (event.text.unicode < 128 && std::isprint(static_cast<char>(event.text.unicode))) {
                input += static_cast<char>(event.text.unicode);
                text.setString(input);
            }
            updateCursor();
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(box);
        window.draw(text);

        // Blink cursor
        if (cursorTimer.getElapsedTime().asMilliseconds() % 1000 < 500 && isFocused)
            window.draw(cursor);
    }

    void updateCursor() {
        sf::FloatRect textBounds = text.getGlobalBounds();
        cursor.setPosition(textBounds.left + textBounds.width + 5, text.getPosition().y);
    }

    std::string getInput() const {
        return input;
    }

    void setFocus(bool focus) {
        isFocused = focus;
    }

    void setTextColor(sf::Color color) {
        text.setFillColor(color);
        cursor.setFillColor(color);
    }

    void setBoxColor(sf::Color fill, sf::Color outline) {
        box.setFillColor(fill);
        box.setOutlineColor(outline);
    }

    sf::FloatRect getGlobalBounds() const {
        return box.getGlobalBounds();
    }
};
