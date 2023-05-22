#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "DataTypes.h"


// Initialize creatures data types
void CreatureInit (Creature *c, char* actorName, char actorSymbol, int mHP, int x, int y) 
{
    c->name = actorName;
    c->symbol = actorSymbol;
    c->maxHealth = mHP;
    c->x = x;
    c->y = y;
}


void SetupCreatures(Creature* creatureArray[]) 
{
    for (int x = 0; x < sizeof (&creatureArray) / sizeof(Creature); x++ ) 
    {
        CreatureInit(creatureArray[x], "E", 'E', 5, 1, 1);
    }
}


// Place the creature somewhere on the map
void PutCreatureOnMap(int height, Tile* map, Creature* toPlace) 
{
    map[toPlace -> y * height + toPlace -> x].creaturePresent = toPlace;
}


// Remove the creature from the map
void RemoveCreatureFromMap(int height, Tile* map, Creature* toPlace) 
{
    map[toPlace -> y * height + toPlace -> x].creaturePresent = NULL;
}


void MoveCreature (Creature* creature, int xVel, int yVel, Tile* map, int screenHeight)
{
    // Check if player is hitting wall
    if (map[(creature -> y + yVel) * screenHeight + (creature -> x + xVel)].symbol == '#') 
    {
        return;
    }

    creature -> x += xVel;
    creature -> y += yVel;
}