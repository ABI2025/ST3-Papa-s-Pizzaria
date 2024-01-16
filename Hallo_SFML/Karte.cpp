#include "Karte.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

void Karte::erstelleKarte()
{
	VideoMode videoMode = VideoMode::getDesktopMode();
	RenderWindow window(videoMode, "Papas-Pizzeria");

	// Hintergrund weiﬂ f‰rben
	window.clear(Color::White);

	// Fenster anzeigen
	window.display();

	// Hauptschleife
	while (window.isOpen()) {
		// Behandle Ereignisse
		sf::Event event;
		while (window.pollEvent(event)) {
			// Schlieﬂe das Fenster
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		// Erstelle Kacheln
		for (int i = 0; i < window.getSize().x; i += 100) {
			for (int j = 0; j < window.getSize().y; j += 100) {
				// Erstelle Rechteck
				RectangleShape rect(Vector2f(100, 100));

				// Setze Farbe
				if ((i + j) % 2 == 0) {
					rect.setFillColor(Color::White);
				}
				else {
					rect.setFillColor(Color::Black);
				}

				// Zeichne Rechteck
				window.draw(rect);
			}
		}

		// Fenster anzeigen
		window.display();
	}
}



