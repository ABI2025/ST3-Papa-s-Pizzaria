#include "Karte.h"
#include "Box.h"
#include "Button.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std; 

void Karte::erstelleKarte() {
    sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(videoMode, "Papas-Pizzeria");

    sf::Texture texture;
    if (!texture.loadFromFile("Images/KarteUpdate.png")) {
        std::cout << "Fehler" << std::endl;
        return;
    }

    sf::Sprite sprite(texture);
    float skalierungsfaktor = 1.0f;
    sprite.setScale(skalierungsfaktor, skalierungsfaktor);
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2f spriteSize = sf::Vector2f(sprite.getLocalBounds().width, sprite.getLocalBounds().height) * skalierungsfaktor;
    sf::Vector2f spritePosition((windowSize.x - spriteSize.x) / 2, (windowSize.y - spriteSize.y) / 2);
    sprite.setPosition(spritePosition);

    // Erstelle den ersten Button
    Button button1(sf::Vector2f(200, 100), sf::Vector2f(100, 50), sf::Color::Blue);
    button1.setPosition(sf::Vector2f(100, 100));

    // Erstelle den zweiten Button
    Button button2(sf::Vector2f(200, 100), sf::Vector2f(100, 50), sf::Color::Red); // �ndere die Farbe oder Eigenschaften nach Bedarf
    button2.setPosition(sf::Vector2f(100, 300)); // �ndere die Position des zweiten Buttons

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                    if (button1.isClicked(mousePos)) {
                        std::cout << "Button 1 clicked!" << std::endl;
                        erstellenArbeitsfl�che(window);
                    }
                    else if (button2.isClicked(mousePos)) {
                        std::cout << "Button 2 clicked!" << std::endl;
                        Story(window); 
                    }
                }
            }
        }

        window.clear();
        window.draw(sprite);
        button1.draw(window);
        button2.draw(window);
        window.display();
    }
}

void Karte::erstellenArbeitsfl�che(sf::RenderWindow& window) {
    Box* arbFl�che = new Box;
    arbFl�che->erstelleBox(window);
}


void Karte::Story(sf::RenderWindow& window)
{
    // Berechne die Gr��e des Fensters
    sf::Vector2u windowSize = window.getSize();

    // Erstelle ein Rechteck-Shape
    sf::RectangleShape box(sf::Vector2f(1100.f, 300.f)); // Gr��e angepasst

    // Berechne die Position der Box, damit sie mittig unten im Fenster liegt
    sf::Vector2f position((windowSize.x - box.getSize().x) / 2.f, windowSize.y - box.getSize().y);

    // Setze die Position des Balkens
    box.setPosition(position);
    box.setFillColor(sf::Color(245, 245, 220));

    // Laden der Schriftart
    sf::Font font;
    if (!font.loadFromFile("Font/Crimson-Bold.ttf")) {
        // Fehlerbehandlung, falls die Schriftart nicht geladen werden kann
        cout << "Fehler" << endl;
    }

    // Konfiguration des ersten Textes
    sf::Text text;
    text.setString("Hallo Giovanni! \nIch habe gro�e Neuigkeiten f�r dich. \nEs ist so weit, mein kleines Restaurant, La Taverna Italiana braucht langsam einen neuen Chef! \nWer k�nnte es besser machen als du, mein Neffe? Bisher hast du mich noch nie entt�uscht, \negal was ich von dir verlangt habe. \nDu hast Talent, Leidenschaft, und - ganz wichtig - Liebe f�r Pizza! \n[DR�CKE SPACE]"); // Textinhalt festlegen
    text.setCharacterSize(24);
    text.setFont(font);// Schriftgr��e festlegen
    text.setFillColor(sf::Color::Black); // Farbe festlegen

    // Position des Textes festlegen (zum Beispiel zentriert in der Box)
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.left + textBounds.width / 2.0f,
        textBounds.top + textBounds.height / 2.0f);
    text.setPosition(box.getPosition() + sf::Vector2f(box.getSize().x / 2.0f, box.getSize().y / 2.0f));

    //Abtasten nach der Leertaste
    // Behandle Ereignisse
    sf::Event event2;
    window.draw(box);

    // Zeichne den Text auf die Karte
    window.draw(text);
    window.display();

    cout << "Hier wurde die Geschichte ausgegeben" << endl;

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
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == ' ') {
                    cout << "F" << endl;
                    text.setString("In den n�chsten Wochen lernst du alles: Teig, Sauce, Belag und ganz wichtig,\n dass Rezepte von deiner Gro�mutter Assunta Maresca ... also sehe es als Ehre an. \nDie italienische K�che ist mehr als Essen, es ist Tradition, Familie, Leidenschaft! \nDu wirst das gro�artig w�hrend meines Ausflugs in Sizilien machen, da bin ich mir sicher.\nIch bin sicher, du machst La Taverna Italiana noch erfolgreicher, als ich es mir je ausmalen k�nnte.\nDein Pate \nP.S.: Bitte vergiss nie: Amore ist die wichtigste Zutat!  E   "); // Textinhalt festlegen

                    // Zeichne die Box auf die Karte
                    window.draw(box);

                    // Zeichne den Text auf die Karte
                    window.draw(text);
                    window.display();
                }
            }
        }
    }

    window.clear();
    // Zeichne die Box auf die Karte
    window.draw(box);

    // Zeichne den Text auf die Karte
    window.draw(text);
    window.display();
}