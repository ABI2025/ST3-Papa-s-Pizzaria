#include "Gericht.h"
#include "Box.h"
#include "Button.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>

using namespace std;

void Gericht::drawRedCircleOnClick(sf::RenderWindow& window, int& credits, int auswahl) {
    bool mouseClicked = false;

    // Koordinaten der bereits platzierten Module abrufen
    Box box;
    std::vector<std::pair<int, int>> trackedCoordinates = box.readCSVAndTrack(window);

    // Lade das erste Bild (PizzaSchinkenSalami)
    sf::Texture texture1;
    if (!texture1.loadFromFile("Images/PizzaEins.png")) {
        std::cerr << "Fehler beim Laden des ersten Bildes!" << std::endl;
        return;
    }

    // Lade das zweite Bild (PizzaMagaritaFertig)
    sf::Texture texture2;
    if (!texture2.loadFromFile("Images/PizzaFertig.png")) {
        std::cerr << "Fehler beim Laden des zweiten Bildes!" << std::endl;
        return;
    }
    sf::Texture texture3;
    if (!texture3.loadFromFile("Images/PizzaZwei.png")) {
        std::cerr << "Fehler beim Laden des zweiten Bildes!" << std::endl;
        return;
    }
    sf::Texture texture4;
    if (!texture4.loadFromFile("Images/PizzaDrei.png")) {
        std::cerr << "Fehler beim Laden des zweiten Bildes!" << std::endl;
        return;
    }

    // Erstelle den Sprite für das erste Bild
    sf::Sprite image;
    if (auswahl == 1)
    {
        image.setTexture(texture1);
    }
    if (auswahl == 2)
    {
        image.setTexture(texture3);
    }
    if (auswahl == 3)
    {
        image.setTexture(texture4);
        cout << "Hallo" << endl; 
    }

    

    // Raster-Größe und -Startposition
    float rasterStartX = 642.0f;
    float rasterStartY = 157.0f;
    float rasterWidthX = 64.0f;
    float rasterWidthY = 63.0f;
    float imageWidth = 32.0f; // Annahme: Die Breite des Bildes beträgt 32 Pixel
    float imageHeight = 32.0f; // Annahme: Die Höhe des Bildes beträgt 32 Pixel

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

                    // Überprüfen, ob die Mausposition mit den Koordinaten eines Moduls übereinstimmt
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
                        std::this_thread::sleep_for(std::chrono::seconds(2));

                     
                        //updateCounter(window);

                        // Ändere die Textur des Sprites auf die des zweiten Bildes
                        image.setTexture(texture2);

                        // Zeichne das zweite Bild an derselben Position
                        window.draw(image);


                        window.display();

                        // Setze die Flagge, dass die Maus geklickt wurde
                        mouseClicked = true;
                        // Warte 5 Sekunden
                        std::this_thread::sleep_for(std::chrono::seconds(2));

                    }
                    else {
                        std::cout << "Ein Bild kann nur auf einem belegten Modul platziert werden!" << std::endl;
                    }
                }
            }
        }
    }
}


void Gericht::plusMinusMünzen(sf::RenderWindow& window, int operation, int changeValue) {
    Button* button = new Button; 
    // Öffnen der Datei im Lese- und Schreibmodus
    std::fstream file("Images/SpeicherungMünzen.csv", std::ios::in | std::ios::out);

    if (!file.is_open()) {
        std::cerr << "Datei konnte nicht geöffnet werden!" << std::endl;
        return;
    }

    // Lesen des aktuellen Wertes
    int wert;
    file >> wert;

    // Variablen für Textdarstellung
    std::string textString;

    // Überprüfen der Operation (1 für Inkrementieren, 0 für Dekrementieren)
    if (operation == 1) {
        wert += changeValue;
        textString = "+" + std::to_string(changeValue);
    }
    else if (operation == 0) {
        if (wert - changeValue < 0) {
            std::cerr << "Fehler: Wert kann nicht negativ sein!" << std::endl;
            file.close();
            button->Box(window); 
        }
        wert -= changeValue;
        textString = "-" + std::to_string(changeValue);
    }
    else {
        std::cerr << "Ungültige Operation!" << std::endl;
        file.close();
        return;
    }

    // Zurücksetzen des Lesepointers
    file.clear();
    file.seekp(0, std::ios::beg);

    // Speichern des neuen Werts
    file << wert;

    // Schließen der Datei
    file.close();

    // Setzen des Textes und seiner Position
    sf::Font font;
    if (!font.loadFromFile("Font/Crimson-Bold.ttf")) {
        std::cerr << "Font konnte nicht geladen werden!" << std::endl;
        return;
    }
    sf::Text text;
    text.setFont(font);
    text.setString(textString);
    text.setCharacterSize(24); // Beispielhafte Schriftgröße
    text.setFillColor(sf::Color::White); // Beispielhafte Textfarbe
    text.setPosition(1900, 20);

    // Text auf dem Fenster rendern
    window.draw(text);
    window.display();
}

void Gericht::Münzen(sf::RenderWindow& window) {
    // Öffnen der Datei im Lese- und Schreibmodus
    std::fstream file("Images/SpeicherungMünzen.csv", std::ios::in | std::ios::out);

    if (!file.is_open()) {
        std::cerr << "Datei konnte nicht geöffnet werden!" << std::endl;
        return;
    }

    // Lesen des aktuellen Wertes
    int wert;
    file >> wert;

    // Inkrementieren des Werts um eins
    wert = 5; // Hier setzen Sie den Wert immer auf 5, unabhängig vom vorherigen Wert

    // Zurücksetzen des Lesepointers
    file.clear();
    file.seekp(0, std::ios::beg);

    // Speichern des neuen Werts
    file << wert;

    // Schließen der Datei
    file.close();
}

void Gericht::updateCounter(sf::RenderWindow& window) {
    // Öffnen der Datei im Lese-Modus
    std::ifstream file("Images/SpeicherungMünzen.csv");

    if (!file.is_open()) {
        std::cerr << "Datei konnte nicht geöffnet werden!" << std::endl;
        return;
    }

    // Lesen des aktuellen Werts
    int wert;
    file >> wert;

    // Schließen der Datei
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

    // Löschen des Fensters und Neuzeichnen des Texts
    window.draw(text);
}

