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



// User Location
int x_loc;
int y_loc;

int main() {



    
    
    system("cls");
    printf("\033[0;32m");  // Set text color to green
    FILE *read_name;

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
