 the item at the current position (i, j)
            char color[20] = "";
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

            printf("%c ", grid[i][j]);
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