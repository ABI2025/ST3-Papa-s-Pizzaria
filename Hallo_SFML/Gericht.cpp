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

    // Lade das erste Bild
    sf::Texture texture1;
    if (!texture1.loadFromFile("Images/PizzaSchinkenSalami.png")) {
        std::cerr << "Fehler beim Laden des ersten Bildes!" << std::endl;
        return;
    }

    // Lade das zweite Bild
    sf::Texture texture2;
    if (!texture2.loadFromFile("Images/PizzaMagaritaFertig.png")) {
        std::cerr << "Fehler beim Laden des zweiten Bildes!" << std::endl;
        return;
    }

    // Erstelle den Sprite für das erste Bild
    sf::Sprite image;
    image.setTexture(texture1);

    // Raster-Größe und -Startposition basierend auf der Anzahl der Module
    float rasterStartX = 642.0f;
    float rasterStartY = 157.0f;
    float rasterWidthX = 64.0f; // Breite des Rasters
    float rasterWidthY = 63.75f; // Höhe des Rasters

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
                        if (mousePos.x > coord.first - (rasterWidthX / 2) && mousePos.x < coord.first + (rasterWidthX / 2) &&
                            mousePos.y > coord.second - (rasterWidthY / 2) && mousePos.y < coord.second + (rasterWidthY / 2)) {
                        
                            validPlacement = true;
                            break;
                        }
                    }

                    if (validPlacement) {
                        // Setze die Position des Sprites auf die Mausposition
                        image.setPosition(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

                        // Zeichne das erste Bild auf das Fenster
                        window.draw(image);
                        window.display();

                        // Warte 5 Sekunden
                        std::this_thread::sleep_for(std::chrono::seconds(1));

                        // Ändere die Textur des Sprites auf die des zweiten Bildes
                        image.setTexture(texture2);

                        // Zeichne das zweite Bild an derselben Position
                        window.draw(image);
                        window.display();

                        // Setze die Flagge, dass die Maus geklickt wurde
                        mouseClicked = true;

                        // Erhöhe den Counter für Credits
                        Münzen(); 

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
                        std::cout << "Ein Bild kann nur auf einem Modul platziert werden!" << std::endl;
                    }
                }
            }
        }
    }
}



#include <fstream> // Für std::ifstream und std::ofstream

#include <fstream> // Für std::ifstream und std::ofstream

#include <iostream>
#include <fstream>

void Gericht::Münzen() {
    // Öffnen der Datei zum Lesen und Schreiben
    std::fstream file("Images/SpeicherungMünzen.csv", std::ios::in | std::ios::out);
    if (!file.is_open()) {
        std::cerr << "Fehler beim Öffnen der Datei: SpeicherungMünzen.csv" << std::endl;
        return;
    }

    int coins;
    // Lesen der aktuellen Münzen aus der Datei
    if (!(file >> coins)) {
        std::cerr << "Fehler beim Lesen der Münzen aus der Datei." << std::endl;
        file.close();
        return;
    }

    // Erhöhen der Münzen um eins
    coins++;

    // Zurücksetzen des Dateizeigers, um den Wert zu überschreiben
    file.seekp(0);

    // Schreiben der aktualisierten Münzen in die Datei
    if (!(file << coins)) {
        std::cerr << "Fehler beim Schreiben der Münzen in die Datei." << std::endl;
    }

    // Schließen der Datei
    file.close();
}













