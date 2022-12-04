#include "rooms.h"
#include "items.h"
#include <time.h>
#include <stdbool.h>

struct avatar{
    Room currentRoom;
    Item inventory;
    char* name;
};

//these are getters and setters
Item returnInventory(struct avatar* Avatar){
    return Avatar->inventory;
}

char* getCharacterRoomName(Room room, struct avatar* Avatar){
    return getRoomName(Avatar->currentRoom);
}

Room getAvatarRoom(struct avatar* Avatar){
    return Avatar->currentRoom;
}

void setNewAvatarRoom(Room newRoom, struct avatar* Avatar){
    Avatar->currentRoom = newRoom;
}


//prints inventory items
void getInventory(Item item){
    while(item != NULL){
        if (strcmp(getItemName(item), "NULL") == 0){
            item = getNextItem(item);
        }else{
            printf("%s\n", getItemName(item));
            item = getNextItem(item);
        }
    }
}

//returns whether item exists in an avatar inventory
int searchAvatarInventory(Item goalItem, struct avatar* Avatar){
    int i = 0;
    char* itemName = getItemName(goalItem);
    Item item = Avatar->inventory;
    while(item != NULL){
        if (strcmp(getItemName(item), "NULL") == 0){
            item = getNextItem(item);
        }else if(strcmp(getItemName(item), itemName) == 0){
            i = 1;
            item = getNextItem(item);
        }else{
            item = getNextItem(item);
        }
    }
    return i;
}

//returns whether item exists in room list of items
int searchRoomItems(Item goalItem, struct avatar* Avatar){
    int i = 0;
    char* itemName = getItemName(goalItem);
    Item item = getRoomItem(Avatar->currentRoom);
    while(item != NULL){
        if (strcmp(getItemName(item), itemName) == 0){
            i = 1;
            item = getNextItem(item);
        }else{
            item = getNextItem(item);
        }
    }
    return i;
}

//drops items from avatar inventory to the room where
//the avatar is located
void dropItem(Item goalItem, struct avatar* Avatar){
    char* itemName = getItemName(goalItem);
    Item item = Avatar->inventory;
    if(searchAvatarInventory(goalItem, Avatar)==0){
        printf("You do not have that item");
        return;
    }else{
        while(item != NULL){
            if(strcmp(getItemName(item), itemName) != 0){
                item = getNextItem(item);
            }else{
                if((getLastItem(item)==NULL)&&(getNextItem(item)==NULL)){
                    Avatar->inventory = NULL;
                }else if(getLastItem(item) == NULL){
                    setLastItem(getNextItem(item), NULL);
                    Avatar->inventory = getNextItem(item);
                }else if(getNextItem(item) == NULL){
                    setNextItem(getLastItem(item), NULL);
                }else{
                    setLastItem(getNextItem(item), getLastItem(item));
                    setNextItem(getLastItem(item), getNextItem(item));
                }
                printf("Item found\n");
                setRoomItem(getAvatarRoom(Avatar), item);
                printf("Item added to room\n");
                setItemRoom(item, getRoomName(Avatar->currentRoom));
                printf("You just dropped %s in the %s.\n", getItemName(item), getRoomName(Avatar->currentRoom));
                return;
            }
        }
    }
}

//takes item from room list of items and puts it
//in the avatar's inventory
void pickUpItem(Item goalItem, struct avatar* Avatar){
    char* itemName = getItemName(goalItem);
    Item item = getRoomItem(Avatar->currentRoom);
    if(searchRoomItems(goalItem, Avatar)==0){
        printf("That item is not in the room\n");
        return;
    }else{
        while(item != NULL){
            if(strcmp(getItemName(item), itemName) != 0){
                item = getNextItem(item);
            }else{
                printf("Item found\n");
                if((getLastItem(item)==NULL)&&(getNextItem(item)==NULL)){
                    setRoomItem(Avatar->currentRoom, NULL);
                }else if(getLastItem(item) == NULL){
                    setLastItem(getNextItem(item), NULL);
                    setRoomItem(Avatar->currentRoom, getNextItem(item));
                    
                }else if(getNextItem(item) == NULL){
                    setNextItem(getLastItem(item), NULL);
                }else{
                    setLastItem(getNextItem(item), getLastItem(item));
                    setNextItem(getLastItem(item), getNextItem(item));
                }
                if(returnInventory(Avatar) == NULL){
                    printf("Item removed from room\n");
                    setNextItem(item, NULL);
                    setLastItem(item, NULL);
                    Avatar->inventory = item;
                }else{
                    printf("Item removed from room\n");
                    setNextItem(item, returnInventory(Avatar));
                    setLastItem(returnInventory(Avatar), item);
                    setLastItem(item, NULL);
                    Avatar->inventory = item;
                }
                printf("You just picked up %s from the %s.\n", getItemName(item), getRoomName(Avatar->currentRoom));
                return;
            }
        }
    }
}

//move avatar towards rooms in specific directions
void moveNorth(struct avatar* Avatar){
    if(getNorth(Avatar->currentRoom) == NULL){
        printf("You cannot go that way\nPlease re-enter your command\n");
    }else{
        Avatar->currentRoom = getNorth(Avatar->currentRoom);
        printf("You are now in the %s\n", getRoomName(Avatar->currentRoom));
    }
}

void moveSouth(struct avatar* Avatar){
    if(getSouth(Avatar->currentRoom) == NULL){
        printf("You cannot go that way\nPlease re-enter your command\n");
    }else{
        Avatar->currentRoom = getSouth(Avatar->currentRoom);
        printf("You are now in the %s\n", getRoomName(Avatar->currentRoom));
    }
}

void moveEast(struct avatar* Avatar){
    if(getEast(Avatar->currentRoom) == NULL){
        printf("You cannot go that way\nPlease re-enter your command\n");
    }else{
        Avatar->currentRoom = getEast(Avatar->currentRoom);
        printf("You are now in the %s\n", getRoomName(Avatar->currentRoom));
    }
}

void moveWest(struct avatar* Avatar){
    if(getWest(Avatar->currentRoom) == NULL){
        printf("You cannot go that way\nPlease re-enter your command\n");
    }else{
        Avatar->currentRoom = getWest(Avatar->currentRoom);
        printf("You are now in the %s\n", getRoomName(Avatar->currentRoom));
    }
}

//prints the avatar inventory
void printInventory(struct avatar* Avatar){
    Item item = Avatar->inventory;
    if(item == NULL){
        printf("You have no items in your inventory\n");
    }else{
        printf("You have the following items in your inventory:\n");
        while(item != NULL){
            printf("%s\n", getItemName(item));
            item = getNextItem(item);
        }
    }
}

//takes character from where they were and places them
//in the room where the avatar is
void teleportCharacter(Item goalCharacter, Room currentRoom){
    if(strcmp(getItemRoom(goalCharacter), getRoomName(currentRoom)) == 0){
        printf("%s\n", getItemRoom(goalCharacter));
        printf("%s\n", getItemName(goalCharacter));
        printf("That character is already in the room\n");
        return;
    }
    for(int i = 0; i < 9; i++){
        if(strcmp(getItemName(characterArray[i]), getItemName(goalCharacter)) == 0){
            Room varRoom;
            for(int k = 0; k<9; k++){
                if(strcmp(getRoomName(roomArray[k]), getItemRoom(characterArray[i])) == 0){
                    varRoom = roomArray[k];
                }
            }
            if(getLastItem(characterArray[i]) == NULL && getNextItem(characterArray[i]) == NULL){
                setRoomCharacter(varRoom, NULL);
            }else if(getLastItem(characterArray[i]) == NULL){
                setRoomCharacter(varRoom, getNextItem(characterArray[i]));
                setLastItem(getNextItem(characterArray[i]), NULL);
            }else if(getNextItem(characterArray[i]) == NULL){
                setRoomCharacter(varRoom, getLastItem(characterArray[i]));
                setNextItem(getLastItem(characterArray[i]), NULL);
            }else{
                setNextItem(getLastItem(characterArray[i]), getNextItem(characterArray[i]));
                setLastItem(getNextItem(characterArray[i]), getLastItem(characterArray[i]));
            }
            for(int j = 0; j < 9; j++){
                if(strcmp(getRoomName(roomArray[j]), getItemRoom(characterArray[i]))==0){
                    Item person = getRoomCharacter(roomArray[j]);
                    while(person != NULL){
                        if(strcmp(getItemName(person), getItemName(characterArray[i])) == 0){
                            if(getLastItem(person) == NULL && getNextItem(person) == NULL){
                                setRoomCharacter(roomArray[j], NULL);
                            }else if(getLastItem(person) == NULL){
                                setRoomCharacter(roomArray[j], getNextItem(person));
                                setLastItem(getNextItem(person), NULL);
                            }else if(getNextItem(person) == NULL){
                                setNextItem(getLastItem(person), NULL);
                            }else{
                                setNextItem(getLastItem(person), getNextItem(person));
                                setLastItem(getNextItem(person), getLastItem(person));
                            }
                        }
                    }
                }

            }
            setRoomCharacter(currentRoom, characterArray[i]);
            setItemRoom(characterArray[i], getRoomName(currentRoom));
            break;
        }
    }
}

//converts String into an Item reference
Item returnItemFromString(char* string){
    for (int i = 0; i < 9; i++){
        if(strcmp(getItemName(characterArray[i]), string) == 0){
            return characterArray[i];
        }
    }
    
}

//goes through every allocated memory references
//and frees it
void freeAll(){
    for(int i = 0; i < 9; i++){
        free(characterArray[i]);
        free(itemArray[i]);
        free(roomArray[i]);
    }
    printf("Memory Unchained\n");
}

//main
int main(){
    srand(time(NULL));
    struct avatar* Avatar = malloc(sizeof(struct avatar));
    Room board = boardGen();
    int guesses = 0;
    Avatar->currentRoom = board;
    char* charArray[5] = {"Mr.Green", 
                         "Mrs.White", 
                         "Mrs.Peacock",
                         "Professor_Plum", 
                         "Colonel_Mustard"};
    char* charAnswer = charArray[rand()%5];
    char* weaponArray[6] = {"Shrimp",
                  "Comically_Large_Teaspoon",
                 "Banana_Peel",
                 "Giant_Mouse_Trap", 
                 "Lint_Brush", 
                 "Perc40"};
    char* weaponAnswer = weaponArray[rand()%6];
    char* roomsArray[9] = {"Garden", "Entry_Hall", "Garage",
                "Kitchen", "Living_Room", "Bathroom",
                "Playroom", "Pool", "Master_Suite"
                };
    char* roomAnswer = roomsArray[rand()%9];

    printf("Welcome to the game of Clue!\n");
    printf("Please, type your name below:\n");
    char name[20];
    scanf("%s", name);
    Avatar->name = name;
    printf("Hello, %s!\nType your command to begin:\n", Avatar->name);
    printf("Type 'help' for a list of commands\n");
    int exit = 1;
    while(exit!=0){
        int clueGuessCounter = 0;
        char command[20];
        scanf("%s", command);
        if(strcmp(command, "help") == 0){
            printf("The commands are:\n");
            printf("help - displays the commands\n");
            printf("list - displays the characters, weapons, and rooms in the game\n");
            printf("look - displays the room you are in and the characters and items in the room\n");
            printf("go - moves you to a different room\n");
            printf("take - takes an item from the room\n");
            printf("drop - drops an item from your inventory\n");
            printf("inventory - displays the items in your inventory\n");
            printf("clue - guess who was the culprit, what the culprit used, and where the culprit committed the crime\n");
            printf("quit - exits the game\n");
            printf("\n");
        }else if(strcmp(command, "list") == 0){
            printf("These are the characters in the game:\n");
            for(int i = 0; i < 5; i++){
                printf("%s\n", charArray[i]);
            }
            printf("\n");
            printf("These are the weapons in the game:\n");
            for(int i = 0; i < 6; i++){
                printf("%s\n", weaponArray[i]);
            }
            printf("\n");
            printf("These are the rooms in the game:\n");
            for(int i = 0; i < 9; i++){
                printf("%s\n", roomsArray[i]);
            }
            printf("\n");

        }else if(strcmp(command, "look") == 0){
            printf("You are in the %s\n", getRoomName(Avatar->currentRoom));
            printf("\n");
            printf("You see the following characters:\n");
            Item characters = getRoomCharacter(Avatar->currentRoom);
            while(characters != NULL){
                if(strcmp(getItemName(characters), "NULL")!=0){
                    printf("%s\n", getItemName(characters));
                }
                characters = getNextItem(characters);
            }
            printf("\n");
            printf("You see the following items:\n");
            Item items = getRoomItem(Avatar->currentRoom);
            while(items != NULL){
                if(strcmp(getItemName(items), "NULL")!=0){
                    printf("%s\n", getItemName(items));
                }
                items = getNextItem(items);
            }
            printf("\n");
            printf("You can go to the following rooms:\n");
            if(getNorth(Avatar->currentRoom) != NULL){
                printf("You can go north to the %s\n", getRoomName(getNorth(Avatar->currentRoom)));
            }
            if(getSouth(Avatar->currentRoom) != NULL){
                printf("You can go south to the %s\n", getRoomName(getSouth(Avatar->currentRoom)));
            }
            if(getEast(Avatar->currentRoom) != NULL){
                printf("You can go east to the %s\n", getRoomName(getEast(Avatar->currentRoom)));
            }
            if(getWest(Avatar->currentRoom) != NULL){
                printf("You can go west to the %s\n", getRoomName(getWest(Avatar->currentRoom)));
            }
            printf("\n");
        }else if(strcmp(command, "go") == 0){
            printf("Where would you like to go?\n");
            scanf("%s", command);
            if(strcmp(command, "north") == 0){
                if(getNorth(Avatar->currentRoom) != NULL){
                    setNewAvatarRoom(getNorth(Avatar->currentRoom), Avatar);
                    printf("You are now in the %s\n", getRoomName(Avatar->currentRoom));
                }else{
                    printf("You cannot go that way\n");
                }
            }else if(strcmp(command, "south") == 0){
                if(getSouth(Avatar->currentRoom) != NULL){
                    setNewAvatarRoom(getSouth(Avatar->currentRoom), Avatar);
                    printf("You are now in the %s\n", getRoomName(Avatar->currentRoom));
                }else{
                    printf("You cannot go that way\n");
                }
            }else if(strcmp(command, "east") == 0){
                if(getEast(Avatar->currentRoom) != NULL){
                    setNewAvatarRoom(getEast(Avatar->currentRoom), Avatar);
                    printf("You are now in the %s\n", getRoomName(Avatar->currentRoom));
                }else{
                    printf("You cannot go that way\n");
                }
            }else if(strcmp(command, "west") == 0){
                if(getWest(Avatar->currentRoom) != NULL){
                    setNewAvatarRoom(getWest(Avatar->currentRoom), Avatar);
                    printf("You are now in the %s\n", getRoomName(Avatar->currentRoom));
                }else{
                    printf("You cannot go that way\n");
                }
            }else{
                printf("Invalid direction, please try again\n");
                scanf("%s", command);
            }
            printf("\n");
        }else if(strcmp(command, "take") == 0){
            printf("This room has the following items:\n");
            Item items = getRoomItem(Avatar->currentRoom);
            while(items != NULL){
                if(strcmp(getItemName(items), "NULL")!=0){
                    printf("%s\n", getItemName(items));
                }
                items = getNextItem(items);
            }
            printf("\n");
            printf("What would you like to take?\n");
            scanf("%s", command);
            items = getRoomItem(Avatar->currentRoom);
            while(items != NULL){
                if(strcmp(getItemName(items), command) == 0){
                    pickUpItem(items, Avatar);
                    break;
                }
                items = getNextItem(items);
            }
            if(items == NULL){
                printf("That item is not in this room\n");
            }
            printf("\n");

        }else if(strcmp(command, "drop") == 0){
            printf("You have the following items:\n");
            getInventory(returnInventory(Avatar));
            printf("\n");
            printf("What would you like to drop?\n");
            scanf("%s", command);
            Item items = returnInventory(Avatar);
            while(items != NULL){
                if(strcmp(getItemName(items), command) == 0){
                    dropItem(items, Avatar);
                    break;
                }
                items = getNextItem(items);
            }
            if(items == NULL){
                printf("That item is not in your inventory\n");
            }
            printf("\n");

        }else if(strcmp(command, "inventory") == 0){
            //debugging
            printf("You have the following items:\n");
            getInventory(returnInventory(Avatar));
            printf("\n");
        }else if(strcmp(command, "clue") == 0){
            int threeCorrectGuesses = 0;

            if(strcmp(getRoomName(Avatar->currentRoom), roomAnswer)==0){
                printf("Room Match\n");
                printf("You have found the room where the crime was commited\n");
                threeCorrectGuesses++;
            }else{
                printf("Room does not match\n");
            }
            printf("\n");

            printf("What character do you guess commited the crime?\n");
            char answerForChar[100];
            scanf("%s", answerForChar);
            int characterExists = 0;
            while(characterExists == 0){
                for(int i = 0; i < 9; i++){
                    if (strcmp(getItemName(characterArray[i]), answerForChar) == 0){
                        characterExists = 1;
                        break;
                    }                    
                }
                if(characterExists == 1){
                    break;
                }
                printf("That character does not exist\n");
                printf("Please try again\n");
                scanf("%s", answerForChar);

            }
            if(strcmp(charAnswer, answerForChar) == 0){
                printf("Character Match\n");
                printf("You have found the character who commited the crime\n");
                threeCorrectGuesses++;
            }else{
                printf("Character does not match\n");
            }
            
            teleportCharacter(returnItemFromString(answerForChar), Avatar->currentRoom);
            printf("\n");

            printf("What weapon do you guess was used in the crime?\n");
            scanf("%s", command);
            int weaponExists = 0;
            while(weaponExists == 0){
                for(int i = 0; i < 9; i++){
                    if (strcmp(getItemName(itemArray[i]), command) == 0){
                        weaponExists = 1;
                        break;
                    }                    
                }
                if(weaponExists == 1){
                    break;
                }
                printf("That weapon does not exist\n");
                printf("Please try again\n");
                scanf("%s", command);
            }
            int isItemInRoom = 0;
            int isItemInInventory = 0;
            while((isItemInRoom == 0)&&(isItemInInventory == 0)){
                Item weaponCurrent = getRoomItem(Avatar->currentRoom);
                while(weaponCurrent != NULL){
                    if(strcmp(getItemName(weaponCurrent), command) == 0){
                        isItemInRoom = 1;
                        break;
                    }
                    weaponCurrent = getNextItem(weaponCurrent);
                }
                weaponCurrent = returnInventory(Avatar);
                while(weaponCurrent != NULL){
                    if(strcmp(getItemName(weaponCurrent), command) == 0){
                        isItemInInventory = 1;
                        break;
                    }
                    weaponCurrent = getNextItem(weaponCurrent);
                }
                if((isItemInRoom == 0)&&(isItemInInventory == 0)){
                    printf("That item is not in this room or your inventory\n");
                    printf("Please try again\n");
                    scanf("%s", command);
                }
            }
            if(strcmp(weaponAnswer, command) == 0){
                printf("Item Match\n");
                printf("You have found the item used in the crime\n");
                threeCorrectGuesses++;
            }else{
                printf("Item does not match\n");
            }
            printf("\n");
            

            if(threeCorrectGuesses == 3){
                printf("You have solved the crime!\n");
                printf("You win!\n");
                freeAll();
                exit = 0;
            }
            if(guesses > 10){
                printf("You have run out of guesses\n");
                printf("You lose!\n");
                freeAll();
                exit = 0;
            }
        }else if(strcmp(command, "quit") == 0){
            freeAll();
            exit = 0;
        }else{
            printf("Invalid command, please try again\n");
            scanf("%s", command);
        }
    }
    return 0;
}