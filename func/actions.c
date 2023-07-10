#include <stdio.h>
#include <string.h>
#include <math.h>
#include "commands.c"
#include "load_dat.c"



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
void performGoToAction(char* coordinates) {
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


void displayNPCs() {
    for (int i = 0; i < numNPCs; i++) {
        if (npcs[i].x == x_loc && npcs[i].y == y_loc) {
            fadeTextIn(npcs[i].dialogue, 50); // Display NPC dialogue with fade-in effect
            break;
        }
    }
}




