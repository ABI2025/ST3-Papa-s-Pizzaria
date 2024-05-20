#include "Button.h"
#include "Gericht.h"
#include "menue.h"
#include <iostream>
using namespace std; 


Button::Button() {
}

Button::Button(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& imagePath)
    : position(position), size(size) {
    if (!texture.loadFromFile(imagePath)) {
        std::cerr << "Error loading texture from file: " << imagePath << std::endl;
    }
    else {
        sprite.setTexture(texture);
        sprite.setPosition(position);
        // Skalieren der Textur, um die gewünschte Größe des Buttons anzupassen
        sprite.setScale(size.x / texture.getSize().x, size.y / texture.getSize().y);
    }
}

void Button::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

bool Button::isClicked(const sf::Vector2f& mousePos) const {
    return (mousePos.x >= position.x && mousePos.x <= position.x + size.x &&
        mousePos.y >= position.y && mousePos.y <= position.y + size.y);
}

void Button::setPosition(const sf::Vector2f& newPosition) {
    position = newPosition;
    sprite.setPosition(newPosition);
}

void Button::Box(sf::RenderWindow& window) {
    menue* home = new menue;
    Gericht* gericht = new Gericht; 
    // Größe des Fensters ermitteln
    sf::Vector2u windowSize = window.getSize();

    // Größe des schwarzen Felds festlegen
    sf::Vector2f boxSize(600, 400);

    // Position des schwarzen Felds berechnen, damit es mittig ist
    sf::Vector2f boxPosition((windowSize.x - boxSize.x) / 2, (windowSize.y - boxSize.y) / 2);

    // Schwarzes Feld erstellen
    sf::RectangleShape blackBox(boxSize);
    blackBox.setFillColor(sf::Color::Black);
    blackBox.setPosition(boxPosition);

    // Font laden
    sf::Font font;
    if (!font.loadFromFile("Font/Crimson-Bold.ttf")) {
        std::cerr << "Font konnte nicht geladen werden!" << std::endl;
        return;
    }

    // Text erstellen
    sf::Text text;
    text.setFont(font);
    text.setString("Leider bist du nun Pleite, \naber nicht schlimm, du kannst neu anfangen");
    text.setCharacterSize(24); // Beispielhafte Schriftgröße
    text.setFillColor(sf::Color::White); // Textfarbe weiß

    // Position des Textes berechnen, damit er mittig im schwarzen Feld ist
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    text.setPosition(boxPosition.x + boxSize.x / 2.0f, boxPosition.y + boxSize.y / 2.0f - 50);

    // Erstelle den Menü-Knopf mit Bild
    Button menuButton(sf::Vector2f(boxPosition.x + boxSize.x / 2.0f - 50, boxPosition.y + boxSize.y / 2.0f + 50), sf::Vector2f(100, 50), "Images/pauseButton.png");

    // Erstelle den Text für den Menü-Knopf
    sf::Text menuButtonText;
    menuButtonText.setFont(font);
    menuButtonText.setCharacterSize(16);
    menuButtonText.setFillColor(sf::Color::White);
    menuButtonText.setString("Menü");
    menuButtonText.setPosition(boxPosition.x + boxSize.x / 2.0f - 20, boxPosition.y + boxSize.y / 2.0f + 60);

    // Schwarzes Feld, Text und Menü-Knopf auf dem Fenster rendern
    window.draw(blackBox);
    window.draw(text);
    menuButton.draw(window);
    gericht->Münzen(window); 
    window.draw(menuButtonText);
    window.display();

    bool waitForClick = true;
    while (waitForClick) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return; // Beende die Funktion, wenn das Fenster geschlossen wird
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                    if (menuButton.isClicked(mousePos)) {
                        std::cout << "Menü-Button clicked!" << std::endl;
                        window.close();
                        home->startMenue();
                        waitForClick = false; // Verlasse die Schleife
                    }
                }
            }
        }
    }
}

