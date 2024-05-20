#pragma once
#include <SFML/Graphics.hpp>

class Aufträge
{
public: 
    void neueAufträge(sf::RenderWindow& window);
    void aktualisiereAufträge(const std::string& id);

};


