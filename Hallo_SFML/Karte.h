#pragma once
#include <SFML/Graphics.hpp>
class Karte
{

public: 
	
	void erstelleKarte(); 
	void erstelleBox(); 
	void handleInput();
	void erstellenArbeitsfl�che(sf::RenderWindow& window);
	void waitForKeyPress(sf::RenderWindow& window, sf::Keyboard::Key key); 
	void Story(sf::RenderWindow& window); 

};

