#include "Karte.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std; 

void Karte::erstelleKarte()
{
	VideoMode videoMode = VideoMode::getDesktopMode();
	RenderWindow window(videoMode, "Papas-Pizzeria");

	sf::Texture texture; 
	if(!texture.loadFromFile("C:/Users/Louis/Desktop/Neuer Ordner/KarteUpdate.png"))
		{
			cout << "Fehler" << endl; 
			
		}
    else 
    {
        // Erstelle ein Sprite mit der geladenen Textur
        sf::Sprite sprite(texture);
        
        // Skaliere das Sprite um 20%
        float skalierungsfaktor = 0.8f; // 80% der Originalgröße
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

            // Fenster anzeigen
            window.display();
        }
    }
}



