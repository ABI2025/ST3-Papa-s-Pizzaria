#include "Gericht.h"
#include "Box.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>

using namespace std;

void Gericht::drawRedCircleOnClick(sf::RenderWindow& window, int& credits) {
    bool mouseClicked = false;

    // Koordinaten der bereits platzierten Module abrufen
    Box box;
    std::vector<std::pair<int, int>> trackedCoordinates = box.readCSVAndTrack(window);

    // Lade das erste Bild (PizzaSchinkenSalami)
    sf::Texture texture1;
    if (!texture1.loadFromFile("Images/PizzaSchinkenSalami.png")) {
        std::cerr << "Fehler beim Laden des ersten Bildes!" << std::endl;
        return;
    }

    // Lade das zweite Bild (PizzaMagaritaFertig)
    sf::Texture texture2;
    if (!texture2.loadFromFile("Images/PizzaMagaritaFertig.png")) {
        std::cerr << "Fehler beim Laden des zweiten Bildes!" << std::endl;
        return;
    }

    // Erstelle den Sprite f�r das erste Bild
    sf::Sprite image;
    image.setTexture(texture1);

    // Raster-Gr��e und -Startposition
    float rasterStartX = 642.0f;
    float rasterStartY = 157.0f;
    float rasterWidthX = 64.0f;
    float rasterWidthY = 63.0f;
    float imageWidth = 32.0f; // Annahme: Die Breite des Bildes betr�gt 32 Pixel
    float imageHeight = 32.0f; // Annahme: Die H�he des Bildes betr�gt 32 Pixel

    while (window.isOpen() && !mouseClicked) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Holen der Mausposition in Bezug auf das Fenster
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                    // �berpr�fen, ob die Mausposition mit den Koordinaten eines Moduls �bereinstimmt
                    bool validPlacement = false;
                    for (const auto& coord : trackedCoordinates) {
                        if (mousePos.x > coord.first - (rasterWidthX / 2) && mousePos.x < coord.first + (rasterWidthX / 2) &&
                            mousePos.y > coord.second - (rasterWidthY / 2) && mousePos.y < coord.second + (rasterWidthY / 2)) {

                            validPlacement = true;
                            // Berechne die mittlere Position des Rasters
                            float centerX = coord.first;
                            float centerY = coord.second;

                            // Berechne die Position des Bildes, damit es mittig im Raster liegt
                            float imagePosX = centerX - (imageWidth / 2);
                            float imagePosY = centerY - (imageHeight / 2);

                            // Setze die Position des Sprites auf die berechnete Position
                            image.setPosition(imagePosX-26, imagePosY-24);
                            break;
                        }
                    }

                    if (validPlacement) {
                        // Zeichne das erste Bild auf das Fenster
                        window.draw(image);
                        window.display();

                        // Warte 5 Sekunden
                        std::this_thread::sleep_for(std::chrono::seconds(1));

                        // Erh�he den Counter f�r Credits
                        M�nzen(window);
                        //updateCounter(window);

                        // �ndere die Textur des Sprites auf die des zweiten Bildes
                        image.setTexture(texture2);

                        // Zeichne das zweite Bild an derselben Position
                        window.draw(image);
                        window.display();

                        // Setze die Flagge, dass die Maus geklickt wurde
                        mouseClicked = true;

                        // Warte auf die Eingabe 'e'
                        bool waitForE = false;
                        while (!waitForE) {
                            sf::Event e;
                            while (window.pollEvent(e)) {
                                if (e.type == sf::Event::Closed) {
                                    window.close();
                                    return;
                                }
                                if (e.type == sf::Event::TextEntered) {
                                    if (e.text.unicode == 'e') {
                                        std::cout << "E" << std::endl;
                                        waitForE = true;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    else {
                        std::cout << "Ein Bild kann nur auf einem belegten Modul platziert werden!" << std::endl;
                    }
                }
            }
        }
    }
}







void Gericht::M�nzen(sf::RenderWindow& window) {
    // �ffnen der Datei im Lese- und Schreibmodus
    std::fstream file("Images/SpeicherungM�nzen.csv", std::ios::in | std::ios::out);

    if (!file.is_open()) {
        std::cerr << "Datei konnte nicht ge�ffnet werden!" << std::endl;
        return;
    }

    // Lesen des aktuellen Wertes
    int wert;
    file >> wert;

    // Inkrementieren des Werts um eins
    wert++;

    // Zur�cksetzen des Lesepointers
    file.clear();
    file.seekp(0, std::ios::beg);

    // Speichern des neuen Werts
    file << wert;

    // Schlie�en der Datei
    file.close();

    
}

void Gericht::updateCounter(sf::RenderWindow& window) {
    // �ffnen der Datei im Lese-Modus
    std::ifstream file("Images/SpeicherungM�nzen.csv");

    if (!file.is_open()) {
        std::cerr << "Datei konnte nicht ge�ffnet werden!" << std::endl;
        return;
    }

    // Lesen des aktuellen Werts
    int wert;
    file >> wert;

    // Schlie�en der Datei
    file.close();

    // Erstellen einer Schriftart
    sf::Font font;
    if (!font.loadFromFile("Font/Crimson-Bold.ttf")) {
        std::cerr << "Schriftart konnte nicht geladen werden!" << std::endl;
        return;
    }

    // Erstellen eines Textobjekts
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(24);
    text.setString("Coins: " + std::to_string(wert));
    text.setPosition(1800, 20);
    text.setFillColor(sf::Color::White);

    // L�schen des Fensters und Neuzeichnen des Texts
    window.draw(text);
}

