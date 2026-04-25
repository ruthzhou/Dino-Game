export module TextBox;

import <SFML/Graphics.hpp>;
import <string>;


export class TextBox {
public:
    TextBox(float x, float y, float width, float height, sf::Font& font, unsigned int fontSize);
    void handleEvent(sf::Event event);
    void draw(sf::RenderWindow& window);
    std::string getInput() const;
    void setFocus(bool focus);
    void clear();
    void setTextColor(sf::Color color);         
    void setBoxColor(sf::Color fill, sf::Color outline); 
    sf::FloatRect getGlobalBounds() const;      
    void setPosition(float x, float y);

private:
    void updateCursor();

    sf::RectangleShape box;
    sf::Text text;
    sf::Text cursor;
    std::string input;
    bool isFocused = false;
    sf::Clock cursorTimer;
};

// Constructor: Creates a rectangle input box with font, size, and position
TextBox::TextBox(float x, float y, float width, float height, sf::Font& font, unsigned int fontSize) {
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
    cursor.setFillColor(sf::Color::Red);
    updateCursor();
}

// Handles key input (typing/deleting)
void TextBox::handleEvent(sf::Event event) {
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

// Renders box, text, and blinking cursor
void TextBox::draw(sf::RenderWindow& window) {
    window.draw(box);
    window.draw(text);
    if (cursorTimer.getElapsedTime().asMilliseconds() % 1000 < 500 && isFocused)
        window.draw(cursor);
}

// Updates position of the blinking cursor based on current text width
void TextBox::updateCursor() {
    sf::FloatRect textBounds = text.getGlobalBounds();
    cursor.setPosition(textBounds.left + textBounds.width + 5, text.getPosition().y);
}

// Returns current input string
std::string TextBox::getInput() const {
    return input;
}

// Enables or disables typing focus
void TextBox::setFocus(bool focus) {
    isFocused = focus;
}

// Changes text and cursor color
void TextBox::setTextColor(sf::Color color) {
    text.setFillColor(color);
    cursor.setFillColor(color);
}
// Changes box background and outline color
void TextBox::setBoxColor(sf::Color fill, sf::Color outline) {
    box.setFillColor(fill);
    box.setOutlineColor(outline);
}

// Moves the textbox and repositions its contents
void TextBox::setPosition(float x, float y) {
    box.setPosition(x, y);
    text.setPosition(x + 10.f, y + (box.getSize().y - text.getCharacterSize()) / 2.f);
    updateCursor();
}

// Returns box boundary for collision or click detection
sf::FloatRect TextBox::getGlobalBounds() const {
    return box.getGlobalBounds();
}
// Returns box boundary for collision or click detection
void TextBox::clear() {
    input.clear();
    text.setString("");
    updateCursor();
}
