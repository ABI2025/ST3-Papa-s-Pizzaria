#include "menueFunktionen.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
void menueFunktionen::einstellungen(Font *font)
{
    menueFunktionen* funktionen = new menueFunktionen; //für die Einstllungen

    // Erstelle ein Fenster mit der Größe des Bildschirms
    VideoMode videoMode = VideoMode::getDesktopMode();
    RenderWindow window(videoMode, "Papas-Pizzeria");

    // Zeige das Fenster an
    window.display();

    // Hauptschleife
    while (window.isOpen()) {
        // Behandle Ereignisse
        Event event;
        while (window.pollEvent(event)) {
            // Schließe das Fenster
            if (event.type == sf::Event::Closed) {
                window.close();
            }

        }
        window.clear();
  

        //Platz für draw()


        window.display();

    }
}