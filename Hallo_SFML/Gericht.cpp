#include "Gericht.h"
#include "Box.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>
using namespace std; 

void Gericht::drawRedCircleOnClick(sf::RenderWindow& window, int& credits) {
    bool mouseClicked = false; // Flagge, um zu überprüfen, ob die Maus bereits geklickt wurde

    // Koordinaten der bereits platzierten Module abrufen
    Box box;
    std::vector<std::pair<int, int>> trackedCoordinates = box.readCSVAndTrack(window);

    while (window.isOpen() && !mouseClicked) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Holen der Mausposition in Bezug auf das Fenster
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                    // Überprüfen, ob die Mausposition mit den Koordinaten eines Moduls übereinstimmt
                    bool validPlacement = false;
                    for (const auto& coord : trackedCoordinates) {
                        if (mousePos.x > coord.first - 32 && mousePos.x < coord.first + 32 &&
                            mousePos.y > coord.second - 32 && mousePos.y < coord.second + 32) {
                            validPlacement = true;
                            break;
                        }
                    }

                    if (validPlacement) {
                        // Berechne die Mittelpunktposition des Rasters
                        float rasterStartX = 642.0f;
                        float rasterStartY = 157.0f;
                        float rasterWidthX = 64.0f;
                        float rasterWidthY = 63.75f;

                        int gridX = static_cast<int>((mousePos.x - rasterStartX) / rasterWidthX);
                        int gridY = static_cast<int>((mousePos.y - rasterStartY) / rasterWidthY);

                        float newX = rasterStartX + gridX * rasterWidthX + rasterWidthX / 2;
                        float newY = rasterStartY + gridY * rasterWidthY + rasterWidthY / 2;

                        // Erstellen eines roten Kreises (oder Punktes)
                        sf::CircleShape dot(15); // Radius von 15 (großer Punkt)
                        dot.setFillColor(sf::Color::Red);
                        dot.setPosition(newX, newY);

                        // Zeichnen des Punktes auf das Fenster
                        window.draw(dot);
                        window.display();

                        // Setze die Flagge, dass die Maus geklickt wurde
                        mouseClicked = true;

                        // Warte 5 Sekunden
                        std::this_thread::sleep_for(std::chrono::seconds(5));

                        // Ändere die Farbe des Punktes in Grün
                        dot.setFillColor(sf::Color::Green);

                        // Zeichne den Punkt erneut, um die Farbänderung anzuzeigen
                        window.draw(dot);
                        window.display();

                        // Erhöhe den Counter für Credits
                        credits++;
                        std::cout << "Creditis " << credits << std::endl;
                        
                        // Warte auf die Eingabe 'e'
                        bool waitForE = false;
                        while (!waitForE) {
                            sf::Event e;
                            while (window.pollEvent(e)) {
                                if (e.type == sf::Event::Closed) {
                                    window.close();
                                    return; // Beende die Funktion, wenn das Fenster geschlossen wird
                                }
                                if (e.type == sf::Event::TextEntered) {
                                    if (e.text.unicode == 'e') {
                                        std::cout << "E" << std::endl;
                                        waitForE = true; // Setze die Flagge, um die Schleife zu verlassen
                                        break; // Verlasse die innere Schleife, wenn 'e' eingegeben wird
                                    }
                                }
                            }
                        }
                    }
                    else {
                        std::cout << "Ein Kreis kann nur auf einem Modul platziert werden!" << std::endl;
                    }
                }
            }
        }
    }
}




