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