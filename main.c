#include <stdio.h>
#include <windows.h>
#include <conio.h>

/*
The creature struct will be the basis for all actors within my game,
I can already tell this is gonna be hell due to a distinct lack in OOP,

--Alex, Jan, 13, 2023


TODO
Flesh out map system (not doing it now)
Add in creatures
Add in way to detect other creatures if hit
*/


typedef struct
{
    // Characteristic Attributes
    char* name;
    char symbol;
    int x;
    int y;

    // Functional Attributes
    int maxHealth;
    

} Creature;


typedef struct 
{
    char symbol;
    Creature* creaturePresent;
} Tile;

void MovePlayer (Creature* player, Tile* map, int screenHeight);
void initMap (Tile* map, int screenWidth, int screenHeight);
void initScreen (HANDLE *hConsole, int sw, int sh);


void CreatureInit (Creature *c, char* actorName, char actorSymbol, int mHP, int x, int y) 
{
    c->name = actorName;
    c->symbol = actorSymbol;
    c->maxHealth = mHP;
    c->x = x;
    c->y = y;
}


void PutCreatureOnMap(int height, Tile* map, Creature* toPlace) 
{
    map[toPlace -> y * height + toPlace -> x].creaturePresent = toPlace;
}

void RemoveCreatureFromMap(int height, Tile* map, Creature* toPlace) 
{
    map[toPlace -> y * height + toPlace -> x].creaturePresent = NULL;
}


int main () {
    
    // Screen value declarations
    int screenWidth = 25;
    int screenHeight = 25;

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

    // Map
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
        
    printf("PRESS ANY KEY TO CONTINUE");

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
    char uIn = getch();
    int xVel = 0;
    int yVel = 0;

    if (uIn == 'd') xVel = 1;
    else if (uIn == 'a') xVel = -1;
    else if (uIn == 'w') yVel = -1;
    else if (uIn == 's') yVel = 1;

    // Check if player is hitting wall
    if (map[(player -> y + yVel) * screenHeight + (player -> x + xVel)].symbol == '#') 
    {
        return;
    }

    player -> x += xVel;
    player -> y += yVel;
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


// Initialize the CMD buffer
void initScreen (HANDLE *hConsole, int sw, int sh) 
{
     // Create screen buffer
    *hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(*hConsole);
}