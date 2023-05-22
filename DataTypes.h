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