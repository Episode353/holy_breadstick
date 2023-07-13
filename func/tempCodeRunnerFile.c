                    if (j + x_loc - area.width / 2 >= walls[k].start_x && j + x_loc - area.width / 2 <= walls[k].end_x &&
                        i + y_loc - area.height / 2 >= walls[k].start_y && i + y_loc - area.height / 2 <= walls[k].end_y) {
                        strcpy(color, walls[k].color); // Set wall color
                        symbol = walls[k].symbol; // Set wall symbol
                        foundWall = 1;
                        break;
                    }
                }

                // If no wall is found, check if there is an item at the current position
                if (!foundWall) {
                    // Check if there is an item at the current position
                    for (int k = 0; k < numItems; k++) {
                        int x = items[k].x - x_loc + area.width / 2;
                        int y = items[k].y - y_loc + area.height / 2;
                        if (x == j && y == i) {
                            strcpy(color, items[k].color); // Set item color
                            symbol = items[k].symbol; // Set item symbol
                            foundItem = 1;
