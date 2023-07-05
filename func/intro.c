#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "actions.c"
#include "textcolors.c"

// Hold Program until user input
void press_any_key_to_continue() {
    printf("\nPress a key to continue...");
#ifdef _WIN32
    _getch();
#else
    __fpurge(stdin);
    getchar();
#endif
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
    while (count < 100 && // Avoid reading more biomes than the array can hold
           fscanf(file, "%d,%d,%d,%d,%[^,],%[^,],%c,%[^\n]\n",
                  &biomes[count].start_x, &biomes[count].start_y,
                  &biomes[count].end_x, &biomes[count].end_y,
                  biomes[count].name, biomes[count].color,
                  &biomes[count].symbol, biomes[count].description) == 8) {
        count++;
    }

    fclose(file);
    *numBiomes = count;
}

// Function to parse item data from items.txt
void parseItems(Item* items, int* numItems) {
    FILE* file = fopen("items.txt", "r");
    if (file == NULL) {
        printf("Failed to open items.txt.\n");
        return;
    }

    int count = 0;
    while (!feof(file)) {
        Item item;
        if (fscanf(file, "%d,%d,%[^,],%[^,],%c\n", &item.x, &item.y, item.color, item.name, &item.symbol) == 5) {
            items[count] = item;
            count++;
        }
    }

    fclose(file);
    *numItems = count;
}

// Display
// User Location
int x_loc;
int y_loc;

// Structure to store the viewable area dimensions
typedef struct {
    int width;
    int height;
} ViewableArea;

void readPlayerPosition() {
    FILE* playerPosFile = fopen("player_pos.txt", "r");
    if (playerPosFile != NULL) {
        fscanf(playerPosFile, "%d,%d", &x_loc, &y_loc);
        fclose(playerPosFile);
    }
}


void readViewableArea(ViewableArea* area) {
    FILE* gridSizeFile = fopen("render_distance.txt", "r");
    if (gridSizeFile == NULL) {
        printf("Failed to open render_distance.txt.\n");
        return;
    }

    if (fscanf(gridSizeFile, "%d,%d", &area->width, &area->height) != 2) {
        printf("Invalid grid size in render_distance.txt.\n");
        fclose(gridSizeFile);
        return;
    }

    fclose(gridSizeFile);
}



void displayGrid(ViewableArea area) {
    // Create a 2D array to represent the grid
    char grid[area.height][area.width];

    // Initialize the grid with empty spaces
    for (int i = 0; i < area.height; i++) {
        for (int j = 0; j < area.width; j++) {
            grid[i][j] = '.';
        }
    }

    // Parse item data
    Item items[100]; // Adjust the maximum number of items as needed
    int numItems = 0;
    parseItems(items, &numItems);

    // Set the items' positions and symbols in the grid
    for (int i = 0; i < numItems; i++) {
        int x = items[i].x - x_loc + area.width / 2;
        int y = items[i].y - y_loc + area.height / 2;
        if (x >= 0 && x < area.width && y >= 0 && y < area.height) {
            grid[y][x] = items[i].symbol;
        }
    }

    // Create an array to store biome data
    Biome biomes[100]; // Adjust the maximum number of biomes as needed
    int numBiomes = 0;
    parseBiomes(biomes, &numBiomes);

    // Calculate the player's position in the grid
    int playerX = area.width / 2;
    int playerY = area.height / 2;

    // Print the grid with colors and symbols
    for (int i = area.height - 1; i >= 0; i--) {
        printf("|"); // Print the left border

        for (int j = 0; j < area.width; j++) {
            // Get the color and symbol of the item at the current position (j, i)
            char color[20] = "";
            char symbol = grid[i][j];
            int foundItem = 0; // Flag to indicate if an item is found at the current position

            // Check if the current position matches the player's position
            if (j == playerX && i == playerY) {
                printf(" \033[1;33mP"); // Print player symbol with yellow color
            } else {
                // Check if there is an item at the current position
                for (int k = 0; k < numItems; k++) {
                    int x = items[k].x - x_loc + area.width / 2;
                    int y = items[k].y - y_loc + area.height / 2;
                    if (x == j && y == i) {
                        strcpy(color, items[k].color); // Set item color
                        symbol = items[k].symbol; // Set item symbol
                        foundItem = 1;
                        break;
                    }
                }

                // If no item is found, check if there is a biome at the current position
                if (!foundItem) {
                    for (int k = 0; k < numBiomes; k++) {
                        if (j + x_loc - area.width / 2 >= biomes[k].start_x && j + x_loc - area.width / 2 <= biomes[k].end_x &&
                            i + y_loc - area.height / 2 >= biomes[k].start_y && i + y_loc - area.height / 2 <= biomes[k].end_y) {
                            strcpy(color,biomes[k].color); // Set biome color
                            symbol = biomes[k].symbol; // Set biome symbol
                            break;
                        }
                    }
                }

                // Set the text color
                if (strcmp(color, "red") == 0) {
                    printf("\033[0;31m"); // Red
                } else if (strcmp(color, "green") == 0) {
                    printf("\033[0;32m"); // Green
                } else if (strcmp(color, "yellow") == 0) {
                    printf("\033[0;33m"); // Yellow
                } else if (strcmp(color, "blue") == 0) {
                    printf("\033[0;34m"); // Blue
                } else {
                    printf("\033[0m"); // Default color
                }

                printf(" %c", symbol); // Add space before character
            }
        }
        printf("\033[0m"); // Reset text color
        printf(" |"); // Print the right border
        printf("\n");
    }

    // Print the location, current position, and other information
    locationCheck();

    // Check if there is a biome at the current position and print its name and description
    for (int k = 0; k < numBiomes; k++) {
        if (x_loc >= biomes[k].start_x && x_loc <= biomes[k].end_x &&
            y_loc >= biomes[k].start_y && y_loc <= biomes[k].end_y) {
            printf("Biome Name: %s\n", biomes[k].name);
            printf("Description: %s\n", biomes[k].description);
            break;
        }
    }

    printf("\n\n"); // Add newlines for spacing

    printf("\033[0m"); // Reset text color
}



int main() {
    printf("\033[0m"); // Reset text color
    system("cls");

    // Read the player's position and viewable area from files
    readPlayerPosition();
    ViewableArea viewableArea;
    readViewableArea(&viewableArea);

    FILE* read_name;

    // Open a file in read mode
    read_name = fopen("char_data/name.txt", "r");

    // Store Name
    char name[100];

    // Read the content and store it inside myString
    fgets(name, 100, read_name);

    // Print the file content
    printf("Welcome, %s", name);
    printf("\n");

    char userInput[100];
    int quit = 0;


   while (!quit) {
        displayGrid(viewableArea);  // Display the grid

        printf("Enter your action: ");
        fgets(userInput, sizeof(userInput), stdin);
        userInput[strcspn(userInput, "\n")] = '\0';  // Remove the newline character

        // Parse the user's input to determine the action and argument
        char* action = strtok(userInput, " ");
        char* argument = strtok(NULL, " ");

        if (action != NULL) {
            switch (action[0]) {
                case 'g':
                    if (strcmp(action, "go") == 0) {
                        performGoAction(argument);
                    } else if (strcmp(action, "goto") == 0) {
                        performGoToAction(argument);
                    } else {
                        printf("Invalid action.\n");
                    }
                    break;
                case 'l':
                    if (strcmp(action, "look") == 0) {
                        performLookAction();
                    } else {
                        printf("Invalid action.\n");
                    }
                    break;
                case 'q':
                    performQuitAction();
                    break;
                case 'h':
                    performHelpAction();
                    break;
                default:
                clearScreen();
                    printf("Invalid action.\n");
                    break;
            }
        } else {
            clearScreen();
            printf("Invalid input.\n");
            
        }
    }

    return 0;
}