#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
//#include "rooms.h"

typedef struct item *Item;

extern Item itemArray[9];
extern Item characterArray[9];
extern Item* getItemArray();
extern void setItemArray(Item* items);
extern Item* getCharacterArray();
extern void setCharacterArray(Item* characters);
extern Item newItem(char* name, Item next);
extern void setItemName(Item item, char* name);
extern char* getItemName(Item item);
extern Item getNextItem(Item item);
extern Item getLastItem(Item item);
extern void setNextItem(Item item, Item next);
extern void setLastItem(Item item, Item last);
extern char* getItemRoom(Item item);
extern void setItemRoom(Item item, char* room);