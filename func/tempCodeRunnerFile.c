
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
                        if (strcmp(color, "black") == 0) {
                            printf("\033[0;30m"); // Black
                        } else if (strcmp(color, "red") == 0) {
                            printf("\033[0;31m"); // Red
                        } else if (strcmp(color, "green") == 0) {
                            printf("\033[0;32m"); // Green
                        } else if (strcmp(color, "yellow") == 0) {
                            printf("\033[0;33m"); // Yellow
                        } else if (strcmp(color, "blue") == 0) {
                            printf("\033[0;34m"); // Blue
                        } else if (strcmp(color, "magenta") == 0) {
                            printf("\033[0;35m"); // Magenta
                        } else if (strcmp(color, "cyan") == 0) {
                            printf("\033[0;36m"); // Cyan
                        } else if (strcmp(color, "white") == 0) {
                            printf("\033[0;37m"); // White
                        } else if (strcmp(color, "bright_black") == 0) {
                            printf("\033[0;90m"); // Bright Black
                        } else if (strcmp(color, "bright_red") == 0) {
                            printf("\033[0;91m"); // Bright Red
                        } else if (strcmp(color, "bright_green") == 0) {
                            printf("\033[0;92m"); // Bright Green
                        } else if (strcmp(color, "bright_yellow") == 0) {
                            printf("\033[0;93m"); // Bright Yellow
                        } else if (strcmp(color, "bright_blue") == 0) {
                            printf("\033[0;94m"); // Bright Blue
                        } else if (strcmp(color, "bright_magenta") == 0) {
                            printf("\033[0;95m"); // Bright Magenta
                        } else if (strcmp(color, "bright_cyan") == 0) {
                            printf("\033[0;96m"); // Bright Cyan
                        } else if (strcmp(color, "bright_white") == 0) {
                            printf("\033[0;97m"); // Bright White
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
    displayNPCs();
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

