#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "func/commands.c"
#define MAX_LEN 128
#ifdef _WIN32
#include<conio.h>
#else
#include <stdio_ext.h>
#include <unistd.h> // for usleep function (UNIX-based systems)
#endif
#include "func/textcolors.c"

void print_image(FILE *fptr)
{
    char read_string[MAX_LEN];
    int line_count = 0;

    while (fgets(read_string, sizeof(read_string), fptr) != NULL) {
        printf("%s", read_string);
        line_count++;

        if (line_count == 22) {
            printf("\033[0;37m"); // Set text color to cyan
        }

        if (line_count == 33) {
            printf("\033[0;33m"); // Set text color to magenta
        }

#ifdef _WIN32
        Sleep(100); // I like 300 milliseconds
#else
        usleep(100); // Delay between lines (in microseconds) for UNIX-based systems
#endif
    }
}

void show_menu()
{
    printf("\nOptions:\n");
    printf("1. Start Game (go to intro.exe)\n");
    printf("2. How to Play (load a .txt into the cmd, then after it is loaded give the user these options again)\n");
    printf("3. Delete Character (delete folder char_data)\n");
    printf("4. Quit\n");
}

int main() {
    clear_screen();
    printf("\033[0;32m");  // Set text color to green

    char *filename = "func/title_splash.txt";
    FILE *splash = NULL;

    if ((splash = fopen(filename, "r")) == NULL)
    {
        fprintf(stderr, "Error opening %s\n", filename);
        return 1;
    }

    print_image(splash);

    fclose(splash);

   

    int choice;
    do {
        
        show_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume the newline character

        switch (choice) {
            case 1:
#ifdef _WIN32
                // Windows command to clear screen, change directory, and execute the file
                system("cls && cd func && char_data_generator.exe");
#else
                // UNIX-based command to clear screen, change directory, and execute the file
                system("clear && cd func && ./char_data_generator.exe");
#endif
                break;

            case 2:
                // Load a .txt into the cmd
                // Replace "path_to_file.txt" with the actual path to the file you want to load
#ifdef _WIN32
                system("type actions.txt");
#else
                system("cat actions.txt");
#endif
                press_any_key_to_continue();
                break;

            case 3:
#ifdef _WIN32
                // Windows command to delete folder char_data
                system("rmdir /s /q func\\char_data");
#else
                // UNIX-based command to delete folder char_data
                system("rm -rf func/char_data");
#endif
                printf("Character deleted.\n");
                press_any_key_to_continue();
                break;

            case 4:
                printf("Quitting...\n");
                break;

            default:
                printf("Invalid choice. Please try again.\n");
                press_any_key_to_continue();
                break;
        }
    } while (choice != 4);

    return 0;
}
