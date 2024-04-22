#pragma once
#include <SFML/Graphics.hpp>
class Box
{

public:
	void erstelleBox(sf::RenderWindow& window);
	sf::Vector2f wartenAufMouse(sf::RenderWindow& window);
	void writeToCSVFromCoordinates(int x, int y); 
	std::vector<std::pair<int, int>> readCSVAndTrack(sf::RenderWindow& window);
	void erstelleBoxMitPosition(sf::RenderWindow& window, float positionX, float positionY);
};
