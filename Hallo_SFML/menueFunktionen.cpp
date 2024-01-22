#include "menueFunktionen.h"
#include <SFML/Graphics.hpp>
#include "menue.h"
#include <iostream>
#include <SFML/Audio.hpp>
using namespace sf;
void menueFunktionen::einstellungen(Font* font)
{
    menue* home = new menue;
    int i = 50;

    // Erstelle einen Listener
    Listener listener;
    listener.setGlobalVolume(i);

    // Erstelle einen Sound-Buffer
    SoundBuffer buffer;

    // Lade die Audiodatei
    if (!buffer.loadFromFile("SoundData/ping-82822.mp3"))
    {
        // Fehlerausgabe
        std::cout << "Konnte die Audiodatei nicht laden." << std::endl;
    }

    // Erstelle einen Sound
    Sound sound;

    // Setze den Sound-Buffer
    sound.setBuffer(buffer);

    // Erstelle ein Fenster mit der Größe des Bildschirms
    VideoMode videoMode = VideoMode::getDesktopMode();
    RenderWindow window(videoMode, "Papas-Pizzeria");

    // Erstelle einen Text
    Text text0("Home", *font, 24);
    Text text1("Lauter(+)", *font, 24);
    Text text2("Leiser(-)", *font, 24);

    // Erstelle ein Rechteck für den Knopf
    RectangleShape shape0;
    shape0.setFillColor(sf::Color::Transparent);
    shape0.setPosition(window.getSize().x / 2 - 150, 400);
    shape0.setSize(sf::Vector2f(200, 100));

    // Erstelle ein Rechteck für den Knopf
    RectangleShape shape1;
    shape1.setFillColor(sf::Color::Transparent);
    shape1.setPosition(window.getSize().x / 2 - 245, 535);
    shape1.setSize(sf::Vector2f(200, 100));

    // Erstelle ein Rechteck für den Knopf
    RectangleShape shape2;
    shape2.setFillColor(sf::Color::Transparent);
    shape2.setPosition(window.getSize().x / 2 - 0, 535);
    shape2.setSize(sf::Vector2f(200, 100));

    // Setze die Position des Textes über dem Rechteck
    text0.setPosition(shape0.getPosition().x + 70, shape0.getPosition().y + 30);
    text1.setPosition(shape1.getPosition().x + 9, shape1.getPosition().y + 30);
    text2.setPosition(shape2.getPosition().x + 9, shape2.getPosition().y + 30);

    // Zeige das Fenster an
    window.display();

    // Hauptschleife
    while (window.isOpen())
    {
        // Behandle Ereignisse
        Event event;
        while (window.pollEvent(event))
        {
            // Schließe das Fenster
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            // Überprüfe, ob die Maustaste gedrückt wird
            if (event.type == Event::MouseButtonPressed)
            {
                // Überprüfe, ob der Mauszeiger über dem Text8 liegt
                if (text1.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    // Wenn der Mauszeiger über dem Text8 liegt, ändere die Farbe der Schrift
                    if (event.mouseButton.button == Mouse::Left)
                    {
                        listener.setGlobalVolume(i + 10);
                        i += 10;
                        sound.play();
                    }
                }
                else if (text2.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    // Wenn der Mauszeiger über dem Text8 liegt, ändere die Farbe der Schrift
                    if (event.mouseButton.button == Mouse::Left)
                    {
                        listener.setGlobalVolume(i - 10);
                        i -= 10;
                        sound.play();
                    }
                }
                else if (text0.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y))
                {
                    // Wenn der Mauszeiger über dem Text8 liegt, ändere die Farbe der Schrift
                    if (event.mouseButton.button == Mouse::Left)
                    {
                        window.close();
                        home->startMenue();
                    }
                }
            }
        }
        window.clear();

        // Zeichne das Rechteck und den Text
        window.draw(shape0);
        window.draw(shape1);
        window.draw(shape2);
        window.draw(text0);
        window.draw(text1);
        window.draw(text2);

        window.display();

    }
}
