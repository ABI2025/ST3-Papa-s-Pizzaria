#include "Aufträge.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>
#include <string>
#include <vector>
#include <sstream> 
using namespace std; 

void Aufträge::neueAufträge(sf::RenderWindow& window) {
    // Definition der Struktur Auftrag
    struct Auftrag {
        int auftragsnummer;
        std::string pizza;
        int erledigt;
        int gesamt;
    };

    // Öffnen der Datei im Lese-Modus
    std::ifstream file("Images/Aufträge.csv");

    if (!file.is_open()) {
        std::cerr << "Datei konnte nicht geöffnet werden!" << std::endl;
        return;
    }

    std::vector<Auftrag> aufträge;
    std::string line;

    // Überspringe die erste Zeile der Datei
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
            std::cerr << "Ungültige Auftragsnummer: " << token << std::endl;
            continue; // Ignoriere fehlerhafte Zeile
        }

        // Pizza
        if (!std::getline(ss, token, ','))
            continue; // Ignoriere fehlerhafte Zeile
        auftrag.pizza = token;

        // Erledigte Pizzen
        if (!std::getline(ss, token, ','))
            continue; // Ignoriere fehlerhafte Zeile
        try {
            auftrag.erledigt = std::stoi(token);
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Ungültige Anzahl erledigter Pizzen: " << token << std::endl;
            continue; // Ignoriere fehlerhafte Zeile
        }

        // Zu erledigende Pizzen
        if (!std::getline(ss, token, ','))
            continue; // Ignoriere fehlerhafte Zeile
        try {
            auftrag.gesamt = std::stoi(token);
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Ungültige Anzahl zu erledigender Pizzen: " << token << std::endl;
            continue; // Ignoriere fehlerhafte Zeile
        }

        aufträge.push_back(auftrag);
    }

    // Schließe die Datei
    file.close();

    // Erzeuge einen Text zur Anzeige der Aufträge
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

    // Erzeuge den Text für die Aufträge
    std::stringstream auftragText;
    for (const Auftrag& auftrag : aufträge) {
        auftragText << "Nummer: " << auftrag.auftragsnummer << ", Pizza: " << auftrag.pizza
            << ", Anzahl: " << auftrag.erledigt << "/" << auftrag.gesamt << std::endl;
    }
    text.setString(auftragText.str());

    // Zeichne den Text auf das Fenster
    window.draw(text);
}

void Aufträge::aktualisiereAufträge() {
    // Definition der Struktur Auftrag
    struct Auftrag {
        int auftragsnummer;
        std::string pizza;
        int erledigt;
        int gesamt;
    };

    // Öffnen der Datei im Lese-Modus
    std::ifstream file("Images/Aufträge.csv");

    if (!file.is_open()) {
        std::cerr << "Datei konnte nicht geöffnet werden!" << std::endl;
        return;
    }

    std::vector<Auftrag> aufträge;
    std::string line;

    // Überspringe die erste Zeile der Datei
    std::getline(file, line);
    std::string header = line;

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
            std::cerr << "Ungültige Auftragsnummer: " << token << std::endl;
            continue; // Ignoriere fehlerhafte Zeile
        }

        // Pizza
        if (!std::getline(ss, token, ','))
            continue; // Ignoriere fehlerhafte Zeile
        auftrag.pizza = token;

        // Erledigte Pizzen
        if (!std::getline(ss, token, ','))
            continue; // Ignoriere fehlerhafte Zeile
        try {
            auftrag.erledigt = std::stoi(token);
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Ungültige Anzahl erledigter Pizzen: " << token << std::endl;
            continue; // Ignoriere fehlerhafte Zeile
        }

        // Zu erledigende Pizzen
        if (!std::getline(ss, token, ','))
            continue; // Ignoriere fehlerhafte Zeile
        try {
            auftrag.gesamt = std::stoi(token);
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Ungültige Anzahl zu erledigender Pizzen: " << token << std::endl;
            continue; // Ignoriere fehlerhafte Zeile
        }

        aufträge.push_back(auftrag);
    }

    // Schließe die Datei
    file.close();

    // Aktualisiere die Anzahl der erledigten Pizzen für den ersten passenden Auftrag
    bool found = false;
    for (Auftrag& auftrag : aufträge) {
        if (auftrag.erledigt < auftrag.gesamt) {
            auftrag.erledigt += 1;
            found = true;
            break; // Beende die Schleife, sobald der erste passende Auftrag gefunden und aktualisiert wurde
        }
    }

    // Schreibe die aktualisierten Aufträge in die Datei
    std::ofstream outFile("Images/Aufträge.csv");

    if (!outFile.is_open()) {
        std::cerr << "Datei konnte nicht zum Schreiben geöffnet werden!" << std::endl;
        return;
    }

    // Schreibe den Header zurück
    outFile << header << std::endl;

    // Schreibe die aktualisierten Aufträge
    for (const Auftrag& auftrag : aufträge) {
        outFile << auftrag.auftragsnummer << ","
            << auftrag.pizza << ","
            << auftrag.erledigt << ","
            << auftrag.gesamt << std::endl;
    }

    // Schließe die Datei
    outFile.close();

    // Falls kein passender Auftrag gefunden wurde, gib eine Meldung aus
    if (!found) {
        std::cerr << "Kein passender Auftrag zum Aktualisieren gefunden!" << std::endl;
    }
}




   

