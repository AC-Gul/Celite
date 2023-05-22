#include <stdio.h>
#include <windows.h>
#include <conio.h>

#include "ScreenInit.h"
#include "Creature.h"

/*
The creature struct will be the basis for all actors within my game,
I can already tell this is gonna be hell due to a distinct lack in OOP,

--Alex, Jan, 13, 2023


TODO
Flesh out map system (not doing it now)
Add in creatures
Add in way to detect other creatures if hit

git test
*/


void MovePlayer (Creature* player, Tile* map, int screenHeight);
void initMap (Tile* map, int screenWidth, int screenHeight);





int main () {
    
    // Screen value declarations
    int screenWidth = 25;
    int screenHeight = 25;

    // Creature declarations
    Creature creatures[25];


    // Setup the screen
    char* screen = malloc( sizeof(char) * (screenWidth * screenHeight) );
    HANDLE hConsole;

    if (screen == NULL) 
    {
        return 1;
    }

     // Create screen buffer
    initScreen (&hConsole, screenWidth, screenHeight);

    // Screen print variables
    DWORD dwBytesWritten = 0; // Useless mandatory
    COORD a = {0,0}; // Cordinates to begin drawing at

    // Map setup
    Tile* map = malloc( sizeof(Tile) * (screenWidth * screenHeight) );
    if (map == NULL) 
    {
        return 1;
    }
    
    initMap(map, screenWidth, screenHeight);


    Creature c;
    CreatureInit(&c, "WHYME", 'F', 2, 2, 5);
    PutCreatureOnMap(screenHeight, map, &c);


    // Main game loop
    while(1) {
        
     // Allow player to move
    RemoveCreatureFromMap(screenHeight, map, &c);
    MovePlayer(&c, map, screenHeight);
    PutCreatureOnMap(screenHeight, map, &c);

    // Render
    for (int y = 0; y < screenHeight; y++) 
    {
        for (int x = 0; x < screenWidth; x++) 
        {
            // If there is no creature present
            if (map[y * screenHeight + x].creaturePresent == NULL) 
            {
                screen[y * screenHeight + x] = map[y * screenHeight + x].symbol;
            }

            // If there is a creature present
            else 
            {
                screen[y * screenHeight + x] = map[y * screenHeight + x].creaturePresent->symbol;
            }
        }
    }

    WriteConsoleOutputCharacter(hConsole, screen, screenWidth * screenHeight, a, &dwBytesWritten);
    } 

    free(screen);
    free(map);
    return 0;
}





void MovePlayer (Creature* player, Tile* map, int screenHeight) 
{
    // Get user input && variable declarations
    char uIn = getch();
    int xVel = 0;
    int yVel = 0;

    // assign velocity
    if (uIn == 'd') xVel = 1;
    else if (uIn == 'a') xVel = -1;
    else if (uIn == 'w') yVel = -1;
    else if (uIn == 's') yVel = 1;

    MoveCreature(player, xVel, yVel, map, screenHeight);
}














// Initialize a box
void initMap (Tile* map, int screenWidth, int screenHeight) 
{
    for (int y = 0; y < screenHeight; y++)
    {
        for (int x = 0; x < screenWidth; x++) 
        {

            // walls
            if (y == 0 || y == screenHeight - 1 || x == 0 || x == screenWidth - 1) 
            {
                map[y * screenHeight + x].symbol = '#';
            }
            
            // floor
            else 
            {
                map[y * screenHeight + x].symbol = ' ';
            }

            // set creature present to null
            map[y * screenHeight + x].creaturePresent = NULL;
        }
    }
}