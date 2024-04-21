#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

class Button {
public:
    Button(const sf::Vector2f& position, const sf::Vector2f& size, const sf::Color& color);

    void draw(sf::RenderWindow& window) const;
    bool isClicked(const sf::Vector2f& mousePos) const;
    void setPosition(const sf::Vector2f& position);
private:
    sf::Vector2f position;
    sf::Vector2f size;
    sf::Color color;
};

#endif // BUTTON_H


