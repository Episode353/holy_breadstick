#include <stdio.h>
#include <string.h>
#include <math.h>

// User Location
extern int x_loc;
extern int y_loc;

// Function to clear the screen
void clearScreen() {
#ifdef _WIN32
    system("cls"); // For Windows
#else
    system("clear"); // For Linux/Unix
#endif
}

void storePlayerPosition(int x, int y) {
    FILE* file = fopen("player_pos.txt", "w");
    if (file == NULL) {
        printf("Failed to open player_pos.txt for writing.\n");
        return;
    }

    fprintf(file, "%d,%d\n", x, y);

    fclose(file);
}


// Function for handling action: Go
void performGoAction(const char* action) {
    clearScreen();
    if (strcmp(action, "north") == 0) {
        y_loc = y_loc + 1;  // Increase Y coordinate when moving north
    } else if (strcmp(action, "south") == 0) {
        y_loc = y_loc - 1;  // Decrease Y coordinate when moving south
    } else if (strcmp(action, "east") == 0) {
        x_loc = x_loc + 1;
    } else if (strcmp(action, "west") == 0) {
        x_loc = x_loc - 1;
    } else {
        printf("Invalid action.\n");
        return;
    }

    printf("You go %s.\n", action);
    printf("New position: x = %d, y = %d.\n", x_loc, y_loc);
    storePlayerPosition(x_loc, y_loc); // Store the player's position
}

// Function for handling action: Go To
void performGoToAction(const char* coordinates) {
    clearScreen();

    // Split the coordinates string into x and y substrings
    char* x_str = strtok(coordinates, ",");
    char* y_str = strtok(NULL, ",");

    if (x_str == NULL || y_str == NULL) {
        printf("Invalid coordinates.\n");
        return;
    }

    // Convert the x and y substrings to integers
    int x_dest = atoi(x_str);
    int y_dest = atoi(y_str);

    int x_diff = x_dest - x_loc;
    int y_diff = y_dest - y_loc;

    double distance = sqrt(x_diff * x_diff + y_diff * y_diff);
    int duration = distance * distance;  // Adjust the duration calculation as desired

    printf("You go to %s.\n", coordinates);
    printf("Estimated travel time: %d seconds.\n", duration);

    x_loc = x_dest;
    y_loc = y_dest;

    printf("New position: x = %d, y = %d.\n", x_loc, y_loc);
    storePlayerPosition(x_loc, y_loc); // Store the player's position
}




// Function for handling action: Look
void performLookAction() {
    clearScreen();
    // Implement the logic for the "Look" action here
    printf("You look around.\n");
}

// Function for handling action: Quit
void performQuitAction() {
    clearScreen();
    // Implement the logic for the "Quit" action here
    printf("Goodbye!\n");
    exit(0);
}


/*
---------------------------------------------
Places
---------------------------------------------
*/

// Structure to store location data
typedef struct {
    int x;
    int y;
    char color[20];
    char name[100];
    char description[1000];
} Location;

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
                   &locations[count].x, &locations[count].y, locations[count].color, locations[count].name, locations[count].description);
            count++;
        }
    }

    fclose(file);
    *numLocations = count;
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