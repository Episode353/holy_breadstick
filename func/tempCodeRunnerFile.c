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
                    } else {
                        printf("\033[0m"); // Default color
                    }