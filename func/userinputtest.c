#include <stdio.h>
#include <conio.h>

#define DEFINE_MOVE_UP_KEY 'A'  // Change this to the desired button

int main() {
    
    
    char MOVE_UP_KEY;
    printf("Press the '%c' key to trigger the printf command.\n", DEFINE_MOVE_UP_KEY);

    do {
        MOVE_UP_KEY = getch();
    } while (MOVE_UP_KEY != DEFINE_MOVE_UP_KEY);

    printf("Button '%c' was pressed. mOVED UP\n", DEFINE_MOVE_UP_KEY);

    return 0;
}
