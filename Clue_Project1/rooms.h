#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include "items.h"

typedef struct room *Room;

extern void shuffle(char** array, int n);
extern Room boardGen();
extern char* getRoomName(Room r);
extern char* getCharacterName(Room r);
extern Room getSouth(Room r);
extern Room getNorth(Room r);
extern Room getEast(Room r);
extern Room getWest(Room r);
extern Item getRoomItem(Room r);
extern Item getRoomCharacter(Room r);
extern void setRoomItem(Room r, Item i);
extern void setRoomCharacter(Room r, Item c);
extern Room* getRoomArray();
extern void setRoomArray(Room* rooms);
extern Room roomArray[9];



extern char* roomNames[9];
extern char* characterNames[9];
extern char* itemNames[9];