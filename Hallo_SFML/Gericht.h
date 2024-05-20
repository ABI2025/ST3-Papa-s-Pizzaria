#pragma once
#include <SFML/Graphics.hpp>
class Gericht
{
public: 
	void drawRedCircleOnClick(sf::RenderWindow& window, int& credits, int auswahl); 
	void Münzen(sf::RenderWindow& window);
    void plusMinusMünzen(sf::RenderWindow& window, int operation, int changeValue); 
	void updateCounter( sf::RenderWindow& window);

private:
    // Deklariere die Variablen hier
    bool mouseClicked;
    std::vector<std::pair<int, int>> trackedCoordinates;
    sf::Texture texture1;
    sf::Texture texture2;
    sf::Sprite image;
};

