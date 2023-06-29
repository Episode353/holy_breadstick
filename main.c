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


#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

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

    press_any_key_to_continue();


    FILE *does_char_data_exist;

    // If "char_data/name.txt" exists, then go to read the file
    if (does_char_data_exist = fopen("func/char_data/age.txt", "r")) {
        fclose(does_char_data_exist);
        printf("File exists\n");

#ifdef _WIN32
        // Windows command to clear screen, change directory, and execute the file
        system("cls && cd func && intro.exe");
#else
        // UNIX-based command to clear screen, change directory, and execute the file
        system("clear && cd func && ./intro.exe");
#endif
    } else {
        // If file does not exist, let's make one
        printf("File doesn't exist\n");

#ifdef _WIN32
        // Windows command to clear screen, change directory, and execute the file
        system("cls && cd func && char_data_generator.exe");
#else
        // UNIX-based command to clear screen, change directory, and execute the file
        system("clear && cd func && ./char_data_generator.exe");
#endif
    }

    return 0;
}
