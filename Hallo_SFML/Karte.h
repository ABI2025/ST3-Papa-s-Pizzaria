#pragma once
#include <SFML/Graphics.hpp>
class Karte
{

public: 
	
	void erstelleKarte(); 
	
	void Story(sf::RenderWindow& window); 
	
	void drawRedCircleOnClick(sf::RenderWindow& window, int& credits); 
};

