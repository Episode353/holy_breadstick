#include <stdio.h>
#include <string.h>
#include <math.h>

// User Location
extern int x_loc;
extern int y_loc;

typedef struct {
    char name[100];
    char dialogue[1000];
    int x;
    int y;
    char color[20];
    char display_char;
    // Add other attributes as needed
} NPC;

NPC npcs[100]; // Adjust the maximum number of NPCs as needed
int numNPCs = 0; // Keep track of the number of NPCs in the array



// Structure to store location data
typedef struct {
    int x;
    int y;
    char color[20];
    char name[100];
    char description[1000];
} Location;

// Structure to store item data
typedef struct {
    int x;
    int y;
    char color[20];
    char name[100];
    char symbol;
} Item;

typedef struct {
    int start_x;
    int start_y;
    int end_x;
    int end_y;
    char name[100];
    char color[20];
    char symbol;
    char description[10000];  // Increase the size of the description array
} Biome;

typedef struct {
    int start_x;
    int start_y;
    int end_x;
    int end_y;
    char color[20];
    char symbol;
} Wall;

Wall walls[100]; // Adjust the maximum number of walls as needed
int numWalls = 0;



void parseLocations(Location* locations, int* numLocations) {
    FILE* file = fopen("locations.txt", "r");
    if (file == NULL) {
        printf("Failed to open locations.txt.\n");
        return;
    }

    int count = 0;
    char line[1000];
    while (fgets(line, sizeof(line), file)) {
        if (line[0] != '#') { // Ignore lines starting with '#'
            sscanf(line, "%d,%d,%[^,],%[^,],%[^\n]\n",
                   &locations[count].x, &locations[count].y, locations[count].name, locations[count].description);
            count++;
        }
    }

    fclose(file);
    *numLocations = count;
}

// Function for handling action: Help
void performHelpAction() {
    clearScreen();
    FILE* file = fopen("../actions.txt", "r");
    if (file == NULL) {
        printf("Failed to open help file.\n");
        return;
    }

    printf("\n");
    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }

    fclose(file);
    printf("\n");
}


void parseBiomes(Biome* biomes, int* numBiomes) {
    FILE* file = fopen("biomes.txt", "r");
    if (file == NULL) {
        printf("Failed to open biomes.txt.\n");
        return;
    }

    int count = 0;
    char line[10000];
    while (count < 100 && fgets(line, sizeof(line), file)) {
        if (line[0] != '#') { // Ignore lines starting with '#'
            sscanf(line, "%d,%d,%d,%d,%[^,],%[^,],%c,%[^\n]\n",
                  &biomes[count].start_x, &biomes[count].start_y,
                  &biomes[count].end_x, &biomes[count].end_y,
                  biomes[count].name, biomes[count].color,
                  &biomes[count].symbol, biomes[count].description);
            count++;
        }
    }

    fclose(file);
    *numBiomes = count;
}

void parseItems(Item* items, int* numItems) {
    FILE* file = fopen("items.txt", "r");
    if (file == NULL) {
        printf("Failed to open items.txt.\n");
        return;
    }

    int count = 0;
    char line[1000];
    while (fgets(line, sizeof(line), file)) {
        if (line[0] != '#') { // Ignore lines starting with '#'
            sscanf(line, "%d,%d,%[^,],%[^,],%c\n",
                   &items[count].x, &items[count].y, items[count].color, items[count].name, &items[count].symbol);
            count++;
        }
    }

    fclose(file);
    *numItems = count;
}

// Function to get the description of a location at the current coordinates
void locationCheck() {
    Location locations[100]; // Adjust the maximum number of locations as needed
    int numLocations = 0;
    parseLocations(locations, &numLocations);

    for (int i = 0; i < numLocations; i++) {
        if (locations[i].x == x_loc && locations[i].y == y_loc) {
            printf("\n");
            printf("Location: %s\n", locations[i].name);
            printf("Description: %s\n", locations[i].description);
            break;
        }
    }

    printf("\n");
}

//Define name
char name[100];

//Read Name and Store it 
void readName() {
        FILE* read_name;

    // Open a file in read mode
    read_name = fopen("char_data/name.txt", "r");



    // Read the content and store it inside myString
    fgets(name, 100, read_name);

    fclose(read_name);
}

void loadNPCData() {
    FILE* file = fopen("npc_data.txt", "r");
    if (file == NULL) {
        printf("Failed to open npc_data.txt.\n");
        return;
    }

    char line[1000];
    while (fgets(line, sizeof(line), file)) {
        if (line[0] != '#') { // Ignore lines starting with '#'
            sscanf(line, "%[^,],%[^,],%d,%d,%[^,],%c\n", npcs[numNPCs].name, npcs[numNPCs].dialogue,
                   &npcs[numNPCs].x, &npcs[numNPCs].y, npcs[numNPCs].color, &npcs[numNPCs].display_char);
            numNPCs++;
        }
    }

    fclose(file);
}

void displayNPCs() {
    for (int i = 0; i < numNPCs; i++) {
        if (npcs[i].x == x_loc && npcs[i].y == y_loc) {
            fadeTextIn(npcs[i].dialogue, 50); // Display NPC dialogue with fade-in effect
            break;
        }
    }
}


void parseWalls(Wall* walls, int* numWalls) {
    FILE* file = fopen("walls.txt", "r");
    if (file == NULL) {
        printf("Failed to open walls.txt.\n");
        return;
    }

    int count = 0;
    char line[1000];
    while (count < 100 && fgets(line, sizeof(line), file)) {
        if (line[0] != '#') { // Ignore lines starting with '#'
            sscanf(line, "%d,%d,%d,%d,%[^,],%c\n",
                  &walls[count].start_x, &walls[count].start_y,
                  &walls[count].end_x, &walls[count].end_y,
                  walls[count].color, &walls[count].symbol);
            count++;
        }
    }

    fclose(file);
    *numWalls = count;
}
