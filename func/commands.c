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
void fadeTextIn(const wchar_t* text, int delay) {
    int len = wcslen(text);
    for (int i = 0; i < len; i++) {
        wprintf(L"%lc", text[i]);
        fflush(stdout);
        Sleep(delay);
    }
    printf("\n");
}

