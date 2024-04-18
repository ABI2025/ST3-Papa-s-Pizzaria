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
        sf::Sprite sprite(texture);
        sprite.setRotation(-90);
        float skalierungsfaktor = 0.5f;
        sprite.setScale(skalierungsfaktor, skalierungsfaktor);

        // Hier wird die Position des Sprites so angepasst, dass der Mittelpunkt des Sprites an der Mausklickposition liegt
        sf::Vector2f spriteSize = sf::Vector2f(sprite.getLocalBounds().width, sprite.getLocalBounds().height);
        sprite.setOrigin(spriteSize.x / 2, spriteSize.y / 2);

        sf::Vector2u windowSize = window.getSize();

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2f clickPosition = wartenAufMouse(window);
            sprite.setPosition(clickPosition);
        }

        window.draw(sprite);
    }
}




sf::Vector2f Box::wartenAufMouse(sf::RenderWindow& window)
{
    sf::Vector2f position;
    bool mouseClicked = false;

    while (!mouseClicked)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return position; // Rückgabe der aktuellen Position, falls das Fenster geschlossen wird
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    // Umrechnen der Mausposition ins Fensterkoordinatensystem
                    position = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                    std::cout << "Mausklick bei X: " << position.x << ", Y: " << position.y << std::endl;
                    mouseClicked = true;
                }
            }
        }
    }

    return position;
}


