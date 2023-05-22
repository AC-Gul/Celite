#include "DataTypes.h"

void SetupCreatures(Creature* creatureArray[]);
void MoveCreature (Creature* creature, int xVel, int yVel, Tile* map, int screenHeight);
void CreatureInit (Creature *c, char* actorName, char actorSymbol, int mHP, int x, int y);
void PutCreatureOnMap(int height, Tile* map, Creature* toPlace);
void RemoveCreatureFromMap(int height, Tile* map, Creature* toPlace);
void MoveCreature (Creature* creature, int xVel, int yVel, Tile* map, int screenHeight);