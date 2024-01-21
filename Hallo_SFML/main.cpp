#include <SFML/Graphics.hpp>
#include "menue.h"
#include "Karte.h"
int main()
{
    //menue* home = new menue;
    //home->startMenue();
   Karte* map = new Karte; 
    map->erstelleKarte(); 
    return 0;
}