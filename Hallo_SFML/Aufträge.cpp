#include "Auftr�ge.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
#include <string>
#include <vector>
#include <sstream> 
using namespace std; 

void Auftr�ge::neueAuftr�ge(sf::RenderWindow& window) {
    // Definition der Struktur Auftrag
    struct Auftrag {
        int auftragsnummer;
        std::string pizza;
        int anzahl;
    };

    // �ffnen der Datei im Lese-Modus
    std::ifstream file("Images/Auftr�ge.csv");

    if (!file.is_open()) {
        std::cerr << "Datei konnte nicht ge�ffnet werden!" << std::endl;
        return;
    }

    std::vector<Auftrag> auftr�ge;
    std::string line;

    // �berspringe die erste Zeile der Datei
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        Auftrag auftrag;

        // Auftragsnummer
        if (!std::getline(ss, token, ','))
            continue; // Ignoriere fehlerhafte Zeile
        try {
            auftrag.auftragsnummer = std::stoi(token);
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Ung�ltige Auftragsnummer: " << token << std::endl;
            continue; // Ignoriere fehlerhafte Zeile
        }

        // Pizza
        if (!std::getline(ss, token, ','))
            continue; // Ignoriere fehlerhafte Zeile
        auftrag.pizza = token;

        // Anzahl
        if (!std::getline(ss, token, ','))
            continue; // Ignoriere fehlerhafte Zeile
        try {
            auftrag.anzahl = std::stoi(token);
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Ung�ltige Anzahl: " << token << std::endl;
            continue; // Ignoriere fehlerhafte Zeile
        }

        auftr�ge.push_back(auftrag);
    }

    // Schlie�e die Datei
    file.close();

    // Erzeuge einen Text zur Anzeige der Auftr�ge
    sf::Font font;
    if (!font.loadFromFile("Font/Crimson-Bold.ttf")) {
        std::cerr << "Schriftart konnte nicht geladen werden!" << std::endl;
        return;
    }

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);
    // Positioniere den Text etwas weiter mittig und weiter unten im Fenster
    text.setPosition(1500, 60);

    // Erzeuge den Text f�r die Auftr�ge
    std::stringstream auftragText;
    for (const Auftrag& auftrag : auftr�ge) {
        auftragText << "Nummer: " << auftrag.auftragsnummer << ", Pizza: " << auftrag.pizza << ", Anzahl: " << auftrag.anzahl << std::endl;
    }
    text.setString(auftragText.str());

    // Zeichne den Text auf das Fenster
    window.draw(text);
}





    // Ausgabe der auftr�ge
    //for (const Auftrag& auftrag : auftr�ge) {
      //  std::cout << "Auftragsnummer: " << auftrag.auftragsnummer << ", Pizza: " << auftrag.pizza << ", Anzahl: " << auftrag.anzahl << std::endl;
    //}


