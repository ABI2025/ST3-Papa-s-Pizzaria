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
        int erledigt;
        int gesamt;
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

        // Erledigte Pizzen
        if (!std::getline(ss, token, ','))
            continue; // Ignoriere fehlerhafte Zeile
        try {
            auftrag.erledigt = std::stoi(token);
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Ung�ltige Anzahl erledigter Pizzen: " << token << std::endl;
            continue; // Ignoriere fehlerhafte Zeile
        }

        // Zu erledigende Pizzen
        if (!std::getline(ss, token, ','))
            continue; // Ignoriere fehlerhafte Zeile
        try {
            auftrag.gesamt = std::stoi(token);
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Ung�ltige Anzahl zu erledigender Pizzen: " << token << std::endl;
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
        auftragText << "Nummer: " << auftrag.auftragsnummer << ", Pizza: " << auftrag.pizza
            << ", Anzahl: " << auftrag.erledigt << "/" << auftrag.gesamt << std::endl;
    }
    text.setString(auftragText.str());

    // Zeichne den Text auf das Fenster
    window.draw(text);
}

void Auftr�ge::aktualisiereAuftr�ge() {
    // Definition der Struktur Auftrag
    struct Auftrag {
        int auftragsnummer;
        std::string pizza;
        int erledigt;
        int gesamt;
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
            std::cerr << "Ung�ltige Auftragsnummer: " << token << std::endl;
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
            std::cerr << "Ung�ltige Anzahl erledigter Pizzen: " << token << std::endl;
            continue; // Ignoriere fehlerhafte Zeile
        }

        // Zu erledigende Pizzen
        if (!std::getline(ss, token, ','))
            continue; // Ignoriere fehlerhafte Zeile
        try {
            auftrag.gesamt = std::stoi(token);
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Ung�ltige Anzahl zu erledigender Pizzen: " << token << std::endl;
            continue; // Ignoriere fehlerhafte Zeile
        }

        auftr�ge.push_back(auftrag);
    }

    // Schlie�e die Datei
    file.close();

    // Aktualisiere die Anzahl der erledigten Pizzen f�r den ersten passenden Auftrag
    bool found = false;
    for (Auftrag& auftrag : auftr�ge) {
        if (auftrag.erledigt < auftrag.gesamt) {
            auftrag.erledigt += 1;
            found = true;
            break; // Beende die Schleife, sobald der erste passende Auftrag gefunden und aktualisiert wurde
        }
    }

    // Schreibe die aktualisierten Auftr�ge in die Datei
    std::ofstream outFile("Images/Auftr�ge.csv");

    if (!outFile.is_open()) {
        std::cerr << "Datei konnte nicht zum Schreiben ge�ffnet werden!" << std::endl;
        return;
    }

    // Schreibe den Header zur�ck
    outFile << header << std::endl;

    // Schreibe die aktualisierten Auftr�ge
    for (const Auftrag& auftrag : auftr�ge) {
        outFile << auftrag.auftragsnummer << ","
            << auftrag.pizza << ","
            << auftrag.erledigt << ","
            << auftrag.gesamt << std::endl;
    }

    // Schlie�e die Datei
    outFile.close();

    // Falls kein passender Auftrag gefunden wurde, gib eine Meldung aus
    if (!found) {
        std::cerr << "Kein passender Auftrag zum Aktualisieren gefunden!" << std::endl;
    }
}




   

