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

