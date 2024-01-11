#include "menue.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
void menue::startMenue()
{   
    // Erstelle ein Fenster mit der Größe des Bildschirms
    VideoMode videoMode = VideoMode::getDesktopMode();
    RenderWindow window(videoMode, "Papas-Pizzeria");


    // Zeige das Fenster an
    window.display();

    // Lade die Schriftart
    Font font;
    if (!font.loadFromFile("Font/Courier New Regular.ttf"))
    {
        std::cout << "Font wurde nicht geladen\n";
    }



    // Zeige das Fenster an
    window.display();

    // Erstelle das Logo zu Papas-Pizzeria (klappt noch nicht !!!)
    Text text0(" ________  ________  ________  ________  ________                 ________  ___  ________  ________  _______   ________  ___  ________ \n", font, 24);
    Text text1("|\   __  \|\   __  \|\   __  \|\   __  \|\   ____\               |\   __  \|\  \|\_____  \|\_____  \|\  ___ \ |\   __  \|\  \|\   __  \ \n", font, 24);
    Text text2("\ \  \|\  \ \  \|\  \ \  \|\  \ \  \|\  \ \  \___|_  ____________\ \  \|\  \ \  \\|___/  /|\|___/  /\ \   __/|\ \  \|\  \ \  \ \  \|\  \ \n", font, 24);
    Text text3(" \ \   ____\ \   __  \ \   ____\ \   __  \ \_____  \|\____________\ \   ____\ \  \   /  / /    /  / /\ \  \_|/_\ \   _  _\ \  \ \   __  \ \n", font, 24);
    Text text4("  \ \  \___|\ \  \ \  \ \  \___|\ \  \ \  \|____|\  \|____________|\ \  \___|\ \  \ /  /_/__  /  /_/__\ \  \_|\ \ \  \\  \\ \  \ \  \ \  \ \n", font, 24);
    Text text5("   \ \__\    \ \__\ \__\ \__\    \ \__\ \__\____\_\  \              \ \__\    \ \__\\________\\________\ \_______\ \__\\ _\\ \__\ \__\ \__\ \n", font, 24);
    Text text6("    \|__|     \|__|\|__|\|__|     \|__|\|__|\_________\              \|__|     \|__|\|_______|\|_______|\|_______|\|__|\|__|\|__|\|__|\|__| \n", font, 24);
    Text text7("                                           \|_________| \n", font, 24);
    
    // Setze die Position und Farbe des Text 
    text0.setFillColor(Color::White);
    text1.setFillColor(Color::White);
    text0.setPosition(100,100);

    // Zeichne den text
    window.draw(text0);
                                                                                                                                               
    // Erstelle ein Rechteck für den Knopf
    RectangleShape button(Vector2f(200, 50));

    // Setze die Farbe des Knopfes
    button.setFillColor(Color::White);

    // Setze die Position des Knopfes
    button.setPosition(Vector2f(100, 100));

    // Zeichne den Knopf
    window.draw(button);




    // Warte, bis der Benutzer das Fenster schließt
    while (window.isOpen())
    {
        // Prüfe, ob ein Ereignis vorliegt
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Schließe das Fenster, wenn der Benutzer es schließt
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }
}