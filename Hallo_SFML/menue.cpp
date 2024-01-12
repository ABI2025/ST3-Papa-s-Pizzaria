#include "menue.h"
#include "menueFunktionen.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
void menue::startMenue()
{
    //menueFunktionen* funktionen = new menueFunktionen; //für die Einstllungen

    // Erstelle ein Fenster mit der Größe des Bildschirms
    VideoMode videoMode = VideoMode::getDesktopMode();
    RenderWindow window(videoMode, "Papas-Pizzeria");

    // Lade die Schriftart
    Font font;
    if (!font.loadFromFile("Font/Courier New Regular.ttf"))
    {
        std::cout << "Font wurde nicht geladen\n";
    }

    // Erstelle das Logo zu Papas-Pizzeria (klappt noch nicht !!!)
    Text text0(" ________  ________  ________  ________  ________                 ________  ___  ________  ________  _______   ________  ___  ________ \n", font, 24);
    Text text1("|\\   __  \\|\\   __  \\|\\   __  \\|\\   __  \\|\\   ____\\               |\\   __  \\|\\  \\|\\_____  \\|\\_____  \\|\\  ___ \\ |\\   __  \\|\\  \\|\\   __  \\ \n", font, 24);
    Text text2("\\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\|\\  \\ \\  \\___|_  ____________\\ \\  \\|\\  \\ \\  \\\\|___/  /|\\|___/  /\\ \\   __/|\\ \\  \\|\\  \\ \\  \\ \\  \\|\\  \\\n", font, 24);
    Text text3(" \\ \\   ____\\ \\   __  \\ \\   ____\\ \\   __  \\ \\_____  \\|\\____________\\ \\   ____\\ \\  \\   /  / /    /  / /\\ \\  \\_|/_\\ \\   _  _\\ \\  \\ \\   __  \\ \n", font, 24);
    Text text4("  \\ \\  \\___|\\ \\  \\ \\  \\ \\  \\___|\\ \\  \\ \\  \\|____|\\  \\|____________|\\ \\  \\___|\\ \\  \\ /  /_/__  /  /_/__\\ \\  \\_|\\ \\ \\  \\\\  \\\\ \\  \\ \\  \\ \\  \\\n", font, 24);
    Text text5("   \\ \\__\\    \\ \\__\\ \\__\\ \\__\\    \\ \\__\\ \\__\\____\\_\\  \\              \\ \\__\\    \\ \\__\\\\________\\\\________\\ \\_______\\ \\__\\\\ _\\\\ \\__\\ \\__\\ \\__\\ \n", font, 24);
    Text text6("    \\|__|     \\|__|\\|__|\\|__|     \\|__|\\|__|\\_________\\              \\|__|     \\|__|\\|_______|\\|_______|\\|_______|\\|__|\\|__|\\|__|\\|__|\\|__| \n", font, 24);
    Text text7("                                           \\|_________| \n", font, 24);

    // Setze die Position des Texts (Vektor2f ist ein 2 Demensioaler Vektor er enthält einen Punkt auf der X- und Y-Achse)
    Vector2f position0(100, 100);
    Vector2f position1(100, 135);
    Vector2f position2(100, 170);
    Vector2f position3(100, 205);
    Vector2f position4(100, 240);
    Vector2f position5(100, 275);
    Vector2f position6(100, 310);
    Vector2f position7(100, 345);

    text0.setPosition(position0);
    text1.setPosition(position1);
    text2.setPosition(position2);
    text3.setPosition(position3);
    text4.setPosition(position4);
    text5.setPosition(position5);
    text6.setPosition(position6);
    text7.setPosition(position7);

    // Zeichne den text
    window.draw(text0);
    window.draw(text1);
    window.draw(text2);
    window.draw(text3);
    window.draw(text4);
    window.draw(text5);
    window.draw(text6);
    window.draw(text7);

    //Einstllungen

    // Erstelle einen Text
    Text text8("Start", font, 24);
    Text text9("Einstellungen", font, 24);

    // Erstelle ein Rechteck für den Knopf
    RectangleShape shape0;
    shape0.setFillColor(sf::Color::Transparent);
    shape0.setPosition(window.getSize().x / 2 - 150, 400);
    shape0.setSize(sf::Vector2f(200, 100));

    // Erstelle ein Rechteck für den Knopf
    RectangleShape shape1;
    shape1.setFillColor(sf::Color::Transparent);
    shape1.setPosition(window.getSize().x / 2 - 150, 535);
    shape1.setSize(sf::Vector2f(200, 100));

    // Setze die Position des Textes über dem Rechteck
    text8.setPosition(shape0.getPosition().x + 60, shape0.getPosition().y + 30);
    text9.setPosition(shape1.getPosition().x + 9, shape1.getPosition().y + 30);


    // Zeichne das Rechteck und den Text
    window.draw(shape0);
    window.draw(shape1);
    window.draw(text8);
    window.draw(text9);


    // Zeige das Fenster an
    window.display();

    // Hauptschleife
    while (window.isOpen()) {
        // Behandle Ereignisse
        sf::Event event;
        while (window.pollEvent(event)) {
            // Schließe das Fenster
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Überprüfe, ob die Maustaste gedrückt wird (noch in Arbeit)
            if (event.type == Event::MouseButtonPressed) {
                // Wenn die Maustaste gedrückt wird, ändere die Farbe der Schrift
                if (event.mouseButton.button == Mouse::Left) {
                    text8.setFillColor(sf::Color::Blue);
                }
            }
        }

    }
}