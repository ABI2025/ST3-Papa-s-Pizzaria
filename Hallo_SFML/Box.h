#pragma once
#include <SFML/Graphics.hpp>
class Box
{
public:
	void erstelleBox(sf::RenderWindow& window);
	sf::Vector2f wartenAufMouse(sf::RenderWindow& window);
};
