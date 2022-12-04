#include "items.h"
#include "rooms.h"

//struct definition for item
struct item {
    char* name;
    Item next;
    Item last;
    char* currentRoom;
};

//initializes items
Item newItem(char* name, Item next){
    Item item = malloc(sizeof(struct item));
    item->name = name;
    item->next = next;
    return item;
}

//item and character arrays
Item itemArray[9];

Item characterArray[9];

//getters and setters
void setItemName(Item item, char* name){
    item->name = name;
}

char* getItemName(Item item){
    return item->name;
}

Item getNextItem(Item item){
    if(item->next == NULL){
        return NULL;
    }
    return item->next;
}

Item getLastItem(Item item){
    return item->last;
}

void setNextItem(Item item, Item next){
    item->next = next;
}

void setLastItem(Item item, Item last){
    item->last = last;
}

Item* getItemArray(){
    return itemArray;
}

Item* getCharacterArray(){
    return characterArray;
}

void setItemArray(Item items[9]){
    for(int i=0; i<9; i++){
        itemArray[i] = items[i];
    }
}

void setCharacterArray(Item characters[9]){
    for(int i=0; i<9; i++){
        characterArray[i] = characters[i];
    }
}

void setItemRoom(Item item, char* room){
    item->currentRoom = room;
}

char* getItemRoom(Item item){
    return item->currentRoom;
}