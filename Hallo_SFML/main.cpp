#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Mein Spiel");

    sf::RectangleShape spaceship(sf::Vector2f(50, 50));
    spaceship.setFillColor(sf::Color::Green);
    spaceship.setPosition(375, 500);

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            spaceship.move(-100 * deltaTime, 0);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            spaceship.move(100 * deltaTime, 0);
        }

        window.clear();
        window.draw(spaceship);
        window.display();
    }

    return 0;
}