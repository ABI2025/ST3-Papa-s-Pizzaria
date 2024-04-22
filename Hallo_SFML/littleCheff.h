#pragma once
#include <SFML/Graphics.hpp>
class littleCheff
{
public:
	// Konstruktor
	littleCheff(float x, float y, float breite, float hoehe);

	// Getter-Methoden
	float getX() const;
	float getY() const;
	float getBreite() const;
	float getHoehe() const;

	// Setter-Methoden
	void setX(float x);
	void setY(float y);
	void setBreite(float breite);
	void setHoehe(float hoehe);

	// Steuerungsmethoden
	void bewegenLinks();
	void bewegenRechts();
	void bewegenHoch();
	void bewegenRunter();

	// Zeichenmethode
	void zeichnen(sf::RenderWindow& window);

private:
	float x;
	float y;
	float breite;
	float hoehe;
};

