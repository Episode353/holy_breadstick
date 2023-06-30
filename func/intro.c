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

//Display
//Display
// User Location
int x_loc;
int y_loc;

// Grid size
const int gridXsize = 15;
const int gridYsize = 15;

// Function to clear the screen
void clearScreen() {
#ifdef _WIN32
    system("cls"); // For Windows
#else
    system("clear"); // For Linux/Unix
#endif
}

// Function to display the grid
void displayGrid() {
    clearScreen(); // Clear the screen

    // Print the location, current position, and other information
    locationCheck();
    printf("Current position: x = %d, y = %d\n", x_loc, y_loc);

    // Create a 2D array to represent the grid
    char grid[gridYsize][gridXsize];

    // Initialize the grid with empty spaces
    for (int i = 0; i < gridYsize; i++) {
        for (int j = 0; j < gridXsize; j++) {
            grid[i][j] = '.';
        }
    }

    // Set the player's position in the grid
    grid[y_loc][x_loc] = 'P';

    // Parse item data
    Item items[100]; // Adjust the maximum number of items as needed
    int numItems = 0;
    parseItems(items, &numItems);

    // Set the items' positions and symbols in the grid
    for (int i = 0; i < numItems; i++) {
        grid[items[i].y][items[i].x] = items[i].symbol;
    }

    // Print the grid with colors and symbols
    printf("\n");
    for (int i = 0; i < gridYsize; i++) {
        for (int j = 0; j < gridXsize; j++) {
            // Get the color of the item at the current position (i, j)
            char color[20] = "";
            char symbol = grid[i][j];
            for (int k = 0; k < numItems; k++) {
                if (items[k].x == j && items[k].y == i) {
                    strcpy(color, items[k].color);
                    break;
                }
            }

            // Set the text color
            if (strcmp(color, "red") == 0) {
                printf("\033[0;31m"); // Red
            } else if (strcmp(color, "green") == 0) {
                printf("\033[0;32m"); // Green
            } else if (strcmp(color, "blue") == 0) {
                printf("\033[0;34m"); // Blue
            } else {
                printf("\033[0m"); // Default color
            }

            printf("%c ", symbol);
        }
        printf("\n");
    }
    printf("\033[0m"); // Reset text color
    printf("\n");
}




int main() {
    system("cls");
    printf("\033[0;32m");  // Set text color to green
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

    // Close the file
    fclose(read_name);

    char userInput[100];
    int quit = 0;

    while (!quit) {
        displayGrid();  // Display the grid

        printf("Enter your action: ");
        fgets(userInput, sizeof(userInput), stdin);
        userInput[strcspn(userInput, "\n")] = '\0';  // Remove the newline character

        // Parse the user's input to determine the action and argument
        char* action = strtok(userInput, " ");
        char* argument = strtok(NULL, " ");

        if (action != NULL && argument != NULL) {
            if (strcmp(action, "go") == 0) {
                if (strcmp(argument, "to") == 0) {
                    char* coordinates = strtok(NULL, " ");
                    performGoToAction(coordinates);
                } else {
                    performGoAction(argument);
                }
            } else {
                printf("Invalid action.\n");
            }
        } else if (action != NULL) {
            if (strcmp(action, "look") == 0) {
                performLookAction();
            } else if (strcmp(action, "quit") == 0) {
                performQuitAction();
                quit = 1;
            } else {
                printf("Invalid action.\n");
            }
        } else {
            printf("Invalid input.\n");
        }
    }

    return 0;
}
