#include "Karte.h"
#include "Box.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;


void Karte::erstelleKarte()
{
    VideoMode videoMode = VideoMode::getDesktopMode();
    RenderWindow window(videoMode, "Papas-Pizzeria");


    sf::Texture texture;
    if (!texture.loadFromFile("Images/KarteUpdate.png"))
    {
        cout << "Fehler" << endl;
    }
    else
    {
        // Erstelle ein Sprite mit der geladenen Textur
        sf::Sprite sprite(texture);
        // Skaliere das Sprite um 20%
        float skalierungsfaktor = 1.0f; // 80% der Originalgröße
        sprite.setScale(skalierungsfaktor, skalierungsfaktor);
        // Berechne die zentrierte Position unter Berücksichtigung der Skalierung
        sf::Vector2u windowSize = window.getSize();
        sf::Vector2f spriteSize = sf::Vector2f(sprite.getLocalBounds().width, sprite.getLocalBounds().height) * skalierungsfaktor;
        sf::Vector2f spritePosition((windowSize.x - spriteSize.x) / 2, (windowSize.y - spriteSize.y) / 2);
        sprite.setPosition(spritePosition);
        // Hauptprogrammschleife
        while (window.isOpen()) {
            // Ereignisse verarbeiten
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }
            // Fenster löschen
            window.clear();
            // Sprite zeichnen
            window.draw(sprite);

            //Fenster für Anfangsstory 
            /*/////////////////////////////////////////////////////////

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
                        while (window.pollEvent(event2))
                        {
                            if (event2.type == sf::Event::Closed)
                            {
                                window.close();
                            }
                        }
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) // Wenn Leertaste gedrückt wird, soll ein neuer text erscheinen
                        {
                            // Lösche den Text
                            text.setString("In den nächsten Wochen lernst du alles: Teig, Sauce, Belag und ganz wichtig,\n dass Rezepte von deiner Großmutter Assunta Maresca ... also sehe es als Ehre an. \nDie italienische Küche ist mehr als Essen, es ist Tradition, Familie, Leidenschaft! \nDu wirst das großartig während meines Ausflugs in Sizilien machen, da bin ich mir sicher.\nIch bin sicher, du machst La Taverna Italiana noch erfolgreicher, als ich es mir je ausmalen könnte.\nDein Pate \nP.S.: Bitte vergiss nie: Amore ist die wichtigste Zutat!     "); // Textinhalt festlegen
                        }

                        // Zeichne die Box auf die Karte
                        window.draw(box);


                        // Zeichne den Text auf die Karte
                        window.draw(text);


            /////////////////////////////////////////////////////////////*/

            Box* arbFläche = new Box;
            arbFläche->erstelleBox(window);

            // Fenster anzeigen
            window.display();
        }
    }
}