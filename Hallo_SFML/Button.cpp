#include "Button.h"
#include <iostream>

Button::Button(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color)
    : position(position), size(size), color(color) {}

void Button::draw(sf::RenderWindow& window) const {
    sf::RectangleShape rect(size);
    rect.setPosition(position);
    rect.setFillColor(color);
    window.draw(rect);
}

bool Button::isClicked(const sf::Vector2f& mousePos) const {
    return (mousePos.x >= position.x && mousePos.x <= position.x + size.x &&
        mousePos.y >= position.y && mousePos.y <= position.y + size.y);
}
  void Button::setPosition(const sf::Vector2f& newPosition) {
    position = newPosition;
}
