#include "Box.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

void Box::erstelleBox(sf::RenderWindow& window) {
    sf::Texture texture;
    if (!texture.loadFromFile("Images/Tisch.png")) {
        std::cout << "Fehler" << std::endl;
    }
    else {
        sf::Sprite sprite(texture);
        sprite.setRotation(-90);
        float skalierungsfaktor = 0.5f;
        sprite.setScale(skalierungsfaktor, skalierungsfaktor);

        // Hier wird die Position des Sprites so angepasst, dass der Mittelpunkt des Sprites an der Mausklickposition liegt
        sf::Vector2f spriteSize = sf::Vector2f(sprite.getLocalBounds().width, sprite.getLocalBounds().height);
        sprite.setOrigin(spriteSize.x / 2, spriteSize.y / 2);

        sf::Vector2u windowSize = window.getSize();

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2f clickPosition = wartenAufMouse(window);

            // Raster-Größe und -Startposition
            float rasterStartX = 642.0f;
            float rasterStartY = 157.0f;
            float rasterWidthX = 64.0f;
            float rasterWidthY = 63.75f;

            // Begrenzung des Rasters
            int maxX = 11; // Maximaler Index auf der x-Achse (0-basiert)
            int maxY = 12; // Maximaler Index auf der y-Achse (0-basiert)

            // Berechnung der nächsten Rasterposition
            int gridX = static_cast<int>((clickPosition.x - rasterStartX) / rasterWidthX);
            int gridY = static_cast<int>((clickPosition.y - rasterStartY) / rasterWidthY);

            // Begrenzung auf das Raster
            gridX = std::max(0, std::min(gridX, maxX));
            gridY = std::max(0, std::min(gridY, maxY));

            // Setzen der Position auf das nächste Rasterkästchen
            float newX = (rasterStartX + gridX * rasterWidthX + rasterWidthX / 2) - 15; // Verschiebung um 18 Pixel in X
            float newY = (rasterStartY + gridY * rasterWidthY + rasterWidthY / 2) + 10; // Verschiebung um 41 Pixel in Y
            sprite.setPosition(newX, newY);
        }

        window.draw(sprite);
        window.display(); 

        bool waitForE = false;
        while (!waitForE) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return; // Beende die Funktion, wenn das Fenster geschlossen wird
                }
                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode == 'e') {
                        cout << "E" << endl;
                        waitForE = true; // Setze die Flagge, um die Schleife zu verlassen
                        break; // Verlasse die innere Schleife, wenn 'e' eingegeben wird
                    }
                }
            }
        }
    }
}





sf::Vector2f Box::wartenAufMouse(sf::RenderWindow& window) {
    sf::Vector2f position;
    bool mouseClicked = false;

    while (!mouseClicked) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return position; // Rückgabe der aktuellen Position, falls das Fenster geschlossen wird
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
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


