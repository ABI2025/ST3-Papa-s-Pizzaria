
#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;

int main()
{
    // 
    int score = 0;
    int mx = 0; // m_move x_x-Achse
    int my = 0;
    int speed = 5;

    // Schriftart
    Font font;
    font.loadFromFile("fonts/arial.ttf");

    // Label 
    Text text("", font);
    text.setCharacterSize(30);
    text.setString(std::to_string(score));

    // Spielefenster erstellen
    RenderWindow meinSpieleFenster(VideoMode(300, 500), "Pong"); 
    meinSpieleFenster.setFramerateLimit(30);

    // Ball
    CircleShape ball(5);
    ball.setPosition(145, 100);
    ball.setFillColor(Color::Green);

    // Player
    RectangleShape player(Vector2f(40, 10));
    player.setPosition(130, 400);
    player.setFillColor(Color::Red);

    
    while (meinSpieleFenster.isOpen()) {
     
        Vector2f ballPos = ball.getPosition();
        Vector2f playerPos = player.getPosition();

        if (ballPos.x <= 0)
        {
            mx = speed;
        }
        else if (ballPos.x >= 300 - 10)
        {
            mx = -speed;
        }

        if(ballPos.y <= 0)
        {
            my = speed;
        }
        else if (ballPos.y >= 500 - 10) {
            mx = 0;
            my = 0;
            score = 0;
        }
    // Ballkollision
        if(ballPos.x >= playerPos.x && ballPos.x <= playerPos.x + 40)
            if (ballPos.y >= playerPos.y - 10) {
                score++;
                text.setString(std::to_string(score));
                my = -speed;
            }

     // Tastatur auslesen
        if (Keyboard::isKeyPressed(Keyboard::Space)) {
            my = speed;
            mx = speed;
        }

        if(Keyboard::isKeyPressed(Keyboard::Left)) 
            if (playerPos.x > 0) // Bildbegrenzung nach links
            {
                player.move(-speed, 0); // y-Achse == 0
            }

        if (Keyboard::isKeyPressed(Keyboard::Right))
            if (playerPos.x < 300 - 40) // Bildbegrenzung nach rechts
            {
                player.move(speed, 0); // y-Achse == 0
            }
        
        ball.move(mx, my);

        meinSpieleFenster.clear();
        meinSpieleFenster.draw(ball);
        meinSpieleFenster.draw(text);
        meinSpieleFenster.draw(player);
        meinSpieleFenster.display();
    }

    return 0;
}