#include <stdio.h>
#include <string.h>
#include <stdlib.h>



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

// Clear the Screen
void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/*
Lets Npcs Dialogue load in slowly, for example
// Call the fadeTextIn function for the NPC dialogue
fadeTextIn(WHT "\nHey, um... excuse me.... how did you even get u- i mean,... who are you?!?\n" RESET, 50);
*/
void fadeTextIn(const char* text, int delay) {
    int length = strlen(text);
    for (int i = 0; i < length; i++) {
        putchar(text[i]);
        fflush(stdout); // Flush the output buffer to display the character immediately
        usleep(delay * 1000); // Delay in milliseconds
    }
}

