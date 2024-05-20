#include "Button.h"
#include <iostream>

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
