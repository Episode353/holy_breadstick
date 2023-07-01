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

// Function to parse location data from locations.txt
void parseLocations(Location* locations, int* numLocations) {
    FILE* file = fopen("locations.txt", "r");
    if (file == NULL) {
        printf("Failed to open locations.txt.\n");
        return;
    }

    int count = 0;
    while (!feof(file)) {
        Location location;
        if (fscanf(file, "%d,%d,%[^,],%[^,],%[^\n]\n", &location.x, &location.y, location.color, location.name, location.description) == 5) {
            locations[count] = location;
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

void reloadApplication() {
#ifdef _WIN32
    char command[100] = "start intro.exe";
    system(command);
#else
    char path[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", path, PATH_MAX);
    if (count != -1 && count < PATH_MAX) {
        path[count] = '\0';
        execl(path, path, NULL);
    }
#endif
}
