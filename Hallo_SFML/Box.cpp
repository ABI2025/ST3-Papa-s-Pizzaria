#include "Box.h"
#include <SFML/Graphics.hpp>
#include <fstream>
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
            writeToCSVFromCoordinates(newX, newY); 
            readCSVAndTrack(window); 
        }
        
        

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

void Box::erstelleBoxMitPosition(sf::RenderWindow& window, float positionX, float positionY) {
    sf::Texture texture;
    if (!texture.loadFromFile("Images/Tisch.png")) {
        std::cout << "Fehler" << std::endl;
    }
    else {
        sf::Sprite sprite(texture);
        sprite.setRotation(-90);
        float skalierungsfaktor = 0.5f;
        sprite.setScale(skalierungsfaktor, skalierungsfaktor);

        // Hier wird die Position des Sprites so angepasst, dass der Mittelpunkt des Sprites an der übergebenen Position liegt
        sf::Vector2f spriteSize = sf::Vector2f(sprite.getLocalBounds().width, sprite.getLocalBounds().height);
        sprite.setOrigin((spriteSize.x / 2), (spriteSize.y / 2));
        sprite.setPosition(positionX-15, positionY+10);

        //cout << "Box plaziert: " << positionX  << " " << positionY << endl;

        window.draw(sprite);
        
        

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
// Geht noch nicht 100 % 
void Box::writeToCSVFromCoordinates(int x, int y) {
    // Definiere die Abmessungen des Rasters und die Startposition
    const float rasterStartX = 642.0f;
    const float rasterStartY = 157.0f;
    const float rasterWidthX = 64.0f;
    const float rasterWidthY = 63.75f;

    // Berechne den Rasterindex basierend auf den übergebenen Koordinaten
    int gridX = static_cast<int>((x - rasterStartX) / rasterWidthX);
    int gridY = static_cast<int>((y - rasterStartY) / rasterWidthY);

    // Definiere die maximalen Indizes des Rasters (0-basiert)
    const int maxX = 12; // Maximaler Index auf der x-Achse
    const int maxY = 11; // Maximaler Index auf der y-Achse

    // Stelle sicher, dass die Rasterindizes innerhalb der Grenzen bleiben
    gridX = std::max(0, std::min(gridX, maxX));
    gridY = std::max(0, std::min(gridY, maxY));

    // Initialisiere den Vektor zur Speicherung des Rasterstatus
    std::vector<std::vector<bool>> occupied(12, std::vector<bool>(13, false));

    // Lese vorhandene Werte aus der CSV-Datei
    char value;
    std::ifstream infile("Images/SpeicherStandort.csv");
    if (infile.is_open()) {
        for (int i = 0; i < 12; ++i) {
            for (int j = 0; j < 13; ++j) {
                if (infile.get(value)) {
                    if (value == '1') {
                        occupied[i][j] = true;
                    }
                }
                // Ignoriere Komma-Trennzeichen
                if (j < 12) {
                    infile.ignore(std::numeric_limits<std::streamsize>::max(), ',');
                }
            }
            // Ignoriere den Zeilenumbruch am Ende jeder Zeile
            infile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        infile.close();
    }

    // Markiere das Feld als besetzt
    occupied[gridY][gridX] = true;

    // Schreibe den Rasterstatus in die CSV-Datei
    std::ofstream outfile("Images/SpeicherStandort.csv", std::ios::trunc); // Öffne die Datei und lösche den Inhalt
    if (outfile.is_open()) {
        for (int i = 0; i < 12; ++i) {
            for (int j = 0; j < 13; ++j) {
                // Schreibe "1", wenn das Feld besetzt ist, sonst "0"
                outfile << (occupied[i][j] ? "1" : "0");
                // Füge ein Komma hinzu, außer am Ende jeder Zeile
                if (j < 12) {
                    outfile << ",";
                }
            }
            // Füge einen Zeilenumbruch am Ende jeder Zeile hinzu
            outfile << "\n";
        }
        outfile.close();
    }
    else {
        std::cerr << "Unable to open file: Images/SpeicherStandort.csv" << std::endl;
    }
}



// Geht 
std::vector<std::pair<int, int>> Box::readCSVAndTrack(sf::RenderWindow& window) {
    // Raster-Größe und -Startposition
    float rasterStartX = 642.0f;
    float rasterStartY = 157.0f;
    float rasterWidthX = 64.0f;
    float rasterWidthY = 63.75f;

    // Vektor, um Koordinaten zu speichern
    std::vector<std::pair<int, int>> trackedCoordinates;

    // Öffnen der CSV-Datei
    std::ifstream infile("Images/SpeicherStandort.csv");
    if (!infile.is_open()) {
        std::cerr << "Unable to open file: grid_status.csv" << std::endl;
        return trackedCoordinates;
    }

    // Durchlaufen der CSV-Datei und Rückverfolgen der Koordinaten
    char value;
    int x = 0, y = 0;
    while (infile.get(value)) {
        if (value == '1') {
            // Berechnung der Koordinaten basierend auf Raster-Größe und -Startposition
            int coordX = static_cast<int>(rasterStartX + x * rasterWidthX + rasterWidthX / 2);
            int coordY = static_cast<int>(rasterStartY + y * rasterWidthY + rasterWidthY / 2);
            //cout << "X " << coordX << " Y " << coordY << endl;
            //cout << "Neue Ausgabe " << endl;
            erstelleBoxMitPosition(window, coordX, coordY);
            trackedCoordinates.push_back(std::make_pair(coordX, coordY));
        }

        // Bewege den Zeiger zur nächsten Spalte
        if (value == ',' || value == '\n') {
            x++;
            if (value == '\n') {
                x = 0;
                y++;
            }
        }
    }

    infile.close();

    return trackedCoordinates;
} 
