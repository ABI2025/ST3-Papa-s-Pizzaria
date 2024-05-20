#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

class Button {
public:
    Button(const sf::Vector2f& position, const sf::Vector2f& size, const std::string& imagePath);
    Button();
    void draw(sf::RenderWindow& window) const;
    bool isClicked(const sf::Vector2f& mousePos) const;
    void setPosition(const sf::Vector2f& newPosition);
    void Box(sf::RenderWindow& window); 

private:
    sf::Vector2f position;
    sf::Vector2f size;
    sf::Texture texture;
    sf::Sprite sprite;
};

#endif // BUTTON_H


