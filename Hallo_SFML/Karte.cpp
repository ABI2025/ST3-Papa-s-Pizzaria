

#include "Karte.h"
#include "Box.h"
#include "Button.h"
#include "Aufträge.h"
#include "Gericht.h"
#include "littleCheff.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <SFML/Audio.hpp>
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

    //lade littleCheff
    float x = 960;
    float y = 452;
    sf::Texture cheffTexture;
    if (!cheffTexture.loadFromFile("Images/littleCheffFront.png")) {
        std::cout << "Fehler" << std::endl;
        return;
    }
    cheffTexture.setSmooth(true); // Setze die Textur auf glatte Darstellung
    sf::Sprite cheffSprite(cheffTexture);
    cheffSprite.setScale(90.f / cheffSprite.getTexture()->getSize().x, 90.f / cheffSprite.getTexture()->getSize().y); // Ändere die Größe des Sprites
    cheffSprite.setPosition(x, y);

    sf::Texture cheffTextureLeft;
    if (!cheffTextureLeft.loadFromFile("Images/littleCheffLeft.png")) {
        std::cout << "Fehler" << std::endl;
        return;
    }
    cheffTextureLeft.setSmooth(true);

    sf::Texture cheffTextureRight;
    if (!cheffTextureRight.loadFromFile("Images/littleCheffRight.png")) {
        std::cout << "Fehler" << std::endl;
        return;
    }
    cheffTextureRight.setSmooth(true);

    sf::Texture cheffTextureUp;
    if (!cheffTextureUp.loadFromFile("Images/littleCheffBack.png")) {
        std::cout << "Fehler" << std::endl;
        return;
    }
    cheffTextureUp.setSmooth(true);

    sf::Texture cheffTextureDown;
    if (!cheffTextureDown.loadFromFile("Images/littleCheffFront.png")) {
        std::cout << "Fehler" << std::endl;
        return;
    }
    cheffTextureDown.setSmooth(true);

    //litteCheff WorldBorder
    sf::Vector2f boundaryTopLeft(642.0, 85.0); // Top-left corner
    sf::Vector2f boundaryBottomRight(1412.0, 990.0); // Bottom-right corner

    // Erstelle den ersten Button
    Button button1(sf::Vector2f(200, 100), sf::Vector2f(100, 50), sf::Color::Blue);
    button1.setPosition(sf::Vector2f(100, 100));

    // Erstelle den zweiten Button
    Button button2(sf::Vector2f(200, 100), sf::Vector2f(100, 50), sf::Color::Red); // Ändere die Farbe oder Eigenschaften nach Bedarf
    button2.setPosition(sf::Vector2f(100, 300)); // Ändere die Position des zweiten Buttons

    // Erstelle den dritten Button
    Button button3(sf::Vector2f(200, 100), sf::Vector2f(100, 50), sf::Color::Green); // Ändere die Farbe oder Eigenschaften nach Bedarf
    button3.setPosition(sf::Vector2f(100, 500)); // Ändere die Position des dritten Buttons

    bool isRunning = true; // Flag to control the game loop
    bool isPaused = false; // Flag to indicate if the game is paused

    int credits = 0; // Counter für Credits
    Aufträge* auftrag = new Aufträge; 
    
    sf::RectangleShape pauseOverlay(sf::Vector2f(windowSize.x, windowSize.y));
    pauseOverlay.setFillColor(sf::Color::Black);

    sf::Font font;
    if (!font.loadFromFile("Font/Courier New Regular.ttf")) {
        std::cout << "Fehler" << std::endl;
        return;
    }

    while (window.isOpen()) {
        
        // Setze die Größe von pauseOverlay auf 640 x 360
        pauseOverlay.setSize(sf::Vector2f(640.f, 360.f));
        sf::Vector2f pauseOverlayPosition((windowSize.x - pauseOverlay.getSize().x) / 2, (windowSize.y - pauseOverlay.getSize().y) / 2);
        pauseOverlay.setPosition(pauseOverlayPosition);
        sf::Text pauseText;
        pauseText.setString("Wir haben Probleme in der Küche,\nbitte warten Sie");
        pauseText.setFont(font);
        pauseText.setCharacterSize(24);
        pauseText.setFillColor(sf::Color::White);
        sf::FloatRect textBounds = pauseText.getLocalBounds();
        pauseText.setOrigin(textBounds.left + textBounds.width / 2.0f,
            textBounds.top + textBounds.height / 2.0f);
        pauseText.setPosition(pauseOverlay.getPosition() + sf::Vector2f(pauseOverlay.getSize().x / 2.0f, pauseOverlay.getSize().y / 2.0f));

        Gericht* gericht = new Gericht;
        
        window.clear();
        window.draw(sprite);
        Box* tisch = new Box;
        tisch->readCSVAndTrack(window);
        button1.draw(window);
        button2.draw(window);
        button3.draw(window);
        gericht->updateCounter(window);
        window.draw(cheffSprite);
        auftrag->neueAufträge(window); 

        if (isPaused) {
            window.draw(pauseOverlay);
            window.draw(pauseText);
        }

        window.display();


        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    isPaused = !isPaused; // Toggle pause/resume state
                }
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left && !isPaused) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                    if (button1.isClicked(mousePos)) {
                        std::cout << "Button 1 clicked!" << std::endl;
                        Box* arbFläche = new Box;
                        arbFläche->erstelleBox(window);
                    }
                    else if (button2.isClicked(mousePos)) {
                        std::cout << "Button 2 clicked!" << std::endl;
                        Story(window);
                    }
                    else if (button3.isClicked(mousePos)) {
                        std::cout << "Button 3 clicked!" << std::endl;
                        gericht->drawRedCircleOnClick(window, credits); // Übergebe den Counter für Credits
                    }
                }
            }
        }

        // Check boundary limits and adjust position
        if (y < boundaryTopLeft.y) {
            y = boundaryTopLeft.y; // Stay at the top boundary
        }
        else if (y > boundaryBottomRight.y - cheffSprite.getGlobalBounds().height) {
            y = boundaryBottomRight.y - cheffSprite.getGlobalBounds().height; // Stay at the bottom boundary
        }

        if (x < boundaryTopLeft.x) {
            x = boundaryTopLeft.x; // Stay at the left boundary
        }
        else if (x > boundaryBottomRight.x - cheffSprite.getGlobalBounds().width) {
            x = boundaryBottomRight.x - cheffSprite.getGlobalBounds().width; // Stay at the right boundary
        }

        // Update the position of the littleCheff
        cheffSprite.setPosition(x, y);

        // Handle movement when the game is not paused
        if (!isPaused) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                y -= 10.0; // Move up
                cheffSprite.setTexture(cheffTextureUp);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                y += 10.0; // Move down
                cheffSprite.setTexture(cheffTextureDown);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                x -= 10.0; // Move left
                cheffSprite.setTexture(cheffTextureLeft);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                x += 10.0; // Move right
                cheffSprite.setTexture(cheffTextureRight);
            }
        }

    }
}

void Karte::Story(sf::RenderWindow& window) {
    // Berechne die Größe des Fensters
    sf::Vector2u windowSize = window.getSize();

    // Erstelle ein Rechteck-Shape
    sf::RectangleShape box(sf::Vector2f(1100.f, 300.f)); // Größe angepasst

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
    text.setString("Hallo Giovanni! \nIch habe große Neuigkeiten für dich. \nEs ist so weit, mein kleines Restaurant, La Taverna Italiana braucht langsam einen neuen Chef! \nWer könnte es besser machen als du, mein Neffe? Bisher hast du mich noch nie enttäuscht, \negal was ich von dir verlangt habe. \nDu hast Talent, Leidenschaft, und - ganz wichtig - Liebe für Pizza! \n[DRÜCKE SPACE]"); // Textinhalt festlegen
    text.setCharacterSize(24);
    text.setFont(font);// Schriftgröße festlegen
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
                    text.setString("In den nächsten Wochen lernst du alles: Teig, Sauce, Belag und ganz wichtig,\n dass Rezepte von deiner Großmutter Assunta Maresca ... also sehe es als Ehre an. \nDie italienische Küche ist mehr als Essen, es ist Tradition, Familie, Leidenschaft! \nDu wirst das großartig während meines Ausflugs in Sizilien machen, da bin ich mir sicher.\nIch bin sicher, du machst La Taverna Italiana noch erfolgreicher, als ich es mir je ausmalen könnte.\nDein Pate \nP.S.: Bitte vergiss nie: Amore ist die wichtigste Zutat!  E   "); // Textinhalt festlegen

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
