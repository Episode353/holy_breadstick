#include <stdio.h>
#include <string.h>
#include <math.h>

// User Location
extern int x_loc;
extern int y_loc;

// Function for handling action: Go
void performGoAction(const char* action) {
    if (strcmp(action, "north") == 0) {
        y_loc = y_loc + 1;
    } else if (strcmp(action, "south") == 0) {
        y_loc = y_loc - 1;
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
    locationCheck();
}

// Function for handling action: Go To
void performGoToAction(const char* coordinates) {
    int x_dest, y_dest;
    if (sscanf(coordinates, "%d,%d", &x_dest, &y_dest) != 2) {
        printf("Invalid coordinates.\n");
        return;
    }

    int x_diff = x_dest - x_loc;
    int y_diff = y_dest - y_loc;

    double distance = sqrt(x_diff * x_diff + y_diff * y_diff);
    int duration = distance * distance;  // Adjust the duration calculation as desired

    printf("You go to %s.\n", coordinates);
    printf("Estimated travel time: %d seconds.\n", duration);

    x_loc = x_dest;
    y_loc = y_dest;

    printf("New position: x = %d, y = %d.\n", x_loc, y_loc);
    locationCheck();
}

// Function for handling action: Look
void performLookAction() {
    // Implement the logic for the "Look" action here
    printf("You look around.\n");
}

// Function for handling action: Quit
void performQuitAction() {
    // Implement the logic for the "Quit" action here
    printf("Goodbye!\n");
}

/*
---------------------------------------------
Places
---------------------------------------------
*/

// A Small Can
void locationCheck() {
    if (x_loc == 3 && y_loc == 4) {
        printf("You see a can.\n");
    }
}
