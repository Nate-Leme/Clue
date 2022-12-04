#include "rooms.h"
#include "items.h"

#define NUM_CHARACTERS 9

//struct definition for room
struct room {
   char* name;
   Room North;
   Room South;
   Room East;
   Room West;
   Item itemList;
   Item characterList;
};

//arrays of items, rooms and characters
Room roomArray[9];

Item itemArray[9];

Item characterArray[9];

//string values of rooms, characters and items
char* roomNames[9]={"Garden", "Entry_Hall", "Garage",
                "Kitchen", "Living_Room", "Bathroom",
                "Playroom", "Pool", "Master_Suite"
                };

char* characterNames[9]={ 
                "Mr.Green", 
                "Mrs.White", 
                "Mrs.Peacock",
                "Professor_Plum", 
                "Colonel_Mustard", 
                "NULL",
                "NULL", 
                "NULL", 
                "NULL"
                 };
            
char* itemNames[9] = {"Shrimp",
                  "Comically_Large_Teaspoon",
                 "Banana_Peel",
                 "Giant_Mouse_Trap", 
                 "Lint_Brush", 
                 "Perc40",
                 "NULL", 
                 "NULL", 
                 "NULL"
                 };

//fisher-yates shuffle
void shuffle(char** array, int n) {
    int i;
    for (i = n-1; i > 0; i--) {
        int j = rand() % (i + 1);
        char* temp = array[i];
        array[i] = array[j];
        array[j] = temp;
    }
    }

//initializes items, characters and rooms.
//assigns random values to them and
//sets up board structure
Room boardGen(){
    shuffle(roomNames, 9);
    shuffle(characterNames, 9);
    shuffle(itemNames, 9);

    Room rooms[9];
    Item items[9];
    Item names[9];
    for(int i=0; i<9; i++){
        rooms[i] = malloc(sizeof(struct room));
        items[i] = newItem(itemNames[i], NULL);
        names[i] = newItem(characterNames[i], NULL);
    }

    for(int i = 0; i < 9; i++){

        rooms[i]->name = roomNames[i];

        setItemName(names[i], characterNames[i]);
        rooms[i]->characterList = names[i];
        setItemRoom(names[i], rooms[i]->name);

        setItemName(items[i], itemNames[i]);
        rooms[i]->itemList = items[i];
        setItemRoom(items[i], rooms[i]->name);
        
        if((i==0)||(i==1)||(i==2)){
            rooms[i]->North = NULL;
            rooms[i]->South = rooms[i+3];
            if(i==0){
                rooms[i]->East = rooms[i+1];
                rooms[i]->West = NULL;
            }else if(i==1){
                rooms[i]->East = rooms[i+1];
                rooms[i]->West = rooms[i-1];
            }else{
                rooms[i]->East = NULL;
                rooms[i]->West = rooms[i-1];
            }
        }else if((i==3)||(i==4)||(i==5)){
            rooms[i]->North = rooms[i-3];
            rooms[i]->South = rooms[i+3];
            if(i==3){
                rooms[i]->East = rooms[i+1];
                rooms[i]->West = NULL;
            }else if(i==4){
                rooms[i]->East = rooms[i+1];
                rooms[i]->West = rooms[i-1];
            }else{
                rooms[i]->East = NULL;
                rooms[i]->West = rooms[i-1];
            }
        }else if((i==6)||(i==7)||(i==8)){
            rooms[i]->North = rooms[i-3];
            rooms[i]->South = NULL;
            if(i==6){
                rooms[i]->East = rooms[i+1];
                rooms[i]->West = NULL;
            }else if(i==7){
                rooms[i]->East = rooms[i+1];
                rooms[i]->West = rooms[i-1];
            }else{
                rooms[i]->East = NULL;
                rooms[i]->West = rooms[i-1];
            }
        }
    setItemArray(items);
    setCharacterArray(names);
    for (int i = 0; i < 9; i++){
        roomArray[i] = rooms[i];
    }    
    }
    return rooms[0];
}

//getters and setters
char* getRoomName(Room room){
    return room->name;
}

char* getCharacterName(Room room){
    return getItemName(room->characterList);
}

Room getSouth(Room room){
    return room->South;
}

Room getNorth(Room room){
    return room->North;
}

Room getEast(Room room){
    return room->East;
}

Room getWest(Room room){
    return room->West;
}

Item getRoomItem(Room room){
    return room->itemList;
}

Item getRoomCharacter(Room room){
    return room->characterList;
}

void setRoomItem(Room room, Item item){
    if(item == NULL){
        room->itemList = NULL;
        return;
    }
    if(room->itemList != NULL){
        setLastItem(room->itemList, item);
    }
    setNextItem(item, room->itemList);
    setLastItem(item, NULL);
    room->itemList = item;
}

void setRoomCharacter(Room room, Item character){
    if(character == NULL){
        room->characterList = NULL;
        return;
    }
    setLastItem(room->characterList, character);
    setNextItem(character, room->characterList);
    setLastItem(character, NULL);
    room->characterList = character;
}

Room* getRoomArray(){
    return roomArray;  
}

void setRoomArray(Room* rooms){
    for(int i=0; i<9; i++){
        roomArray[i] = rooms[i];
    }
}