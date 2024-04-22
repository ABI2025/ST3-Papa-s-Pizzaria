#include "littleCheff.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
using namespace std;
using namespace sf;

littleCheff::littleCheff(float x, float y, float breite, float hoehe) {
	this->x = x;
	this->y = y;
	this->breite = breite;
	this->hoehe = hoehe;
}

float littleCheff::getX() const {
	return this->x;
}

float littleCheff::getY() const {
	return this->y;
}

float littleCheff::getBreite() const {
	return this->breite;
}

float littleCheff::getHoehe() const {
	return this->hoehe;
}

void littleCheff::setX(float x) {
	this->x = x;
}

void littleCheff::setY(float y) {
	this->y = y;
}

void littleCheff::setBreite(float breite) {
	this->breite = breite;
}

void littleCheff::setHoehe(float hoehe) {
	this->hoehe = hoehe;
}

void littleCheff::bewegenLinks() {
	this->x -= 1.0f;
}

void littleCheff::bewegenRechts() {
	this->x += 1.0f;
}

void littleCheff::bewegenHoch() {
	this->y -= 1.0f;
}

void littleCheff::bewegenRunter() {
	this->y += 1.0f;
}

void littleCheff::zeichnen(RenderWindow& window) {
	
	//variablen übergeben
	float breite = this->breite;
	float hoehe = this->hoehe;
	float x = this->x;
	float y = this->y;

	// Create a rectangle shape
	RectangleShape cheffRect(Vector2f(breite, hoehe));

	// Set the rectangle's fill color (e.g., blue)
	cheffRect.setFillColor(Color::Blue);

	// Set the rectangle's position (x, y)
	cheffRect.setPosition(x, y);

	// Draw the rectangle on the window
	window.draw(cheffRect);
}

