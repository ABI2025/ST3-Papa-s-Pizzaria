#include "Box.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

void Box::erstelleBox(sf::RenderWindow& window)
{
    sf::Texture texture;
    if (!texture.loadFromFile("Images/Tisch.png"))
    {
        cout << "Fehler" << endl;

    }
    else
    {
        // Ereignisse verarbeiten
        sf::Sprite sprite(texture);
        sprite.setOrigin(sprite.getGlobalBounds().getSize().x / 2, sprite.getGlobalBounds().getSize().y / 2);
        sprite.setRotation(-90);
        // Skaliere das Sprite um 20%
        float skalierungsfaktor = 0.5f; // 80% der Originalgröße
        sprite.setScale(skalierungsfaktor, skalierungsfaktor);
        // Berechne die zentrierte Position unter Berücksichtigung der Skalierung
        sf::Vector2u windowSize = window.getSize();
        //sf::Vector2f spriteSize = sf::Vector2f(sprite.getLocalBounds().width, sprite.getLocalBounds().height) * skalierungsfaktor;
        sf::Vector2f spritePosition(windowSize.x / 2 - 109, windowSize.y / 2 - 85);
        sprite.setPosition(spritePosition);

        // Sprite zeichnen
        window.draw(sprite);
    }
}

