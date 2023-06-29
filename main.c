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
#endif



void print_image(FILE *fptr)
{
    char read_string[MAX_LEN];
 
    while(fgets(read_string,sizeof(read_string),fptr) != NULL)
        printf("%s",read_string);
}





int main() {
    clear_screen();
       printf("\033[0;32m");  // Set text color to green
    
        char *filename = "func/image.txt";
    FILE *splash = NULL;
 
    if((splash = fopen(filename,"r")) == NULL)
    {
        fprintf(stderr,"error opening %s\n",filename);
        return 1;
    }
 
    print_image(splash);
 
    fclose(splash);


    



    press_any_key_to_continue();

    FILE *does_char_data_exist;

    // If "char_data/name.txt" exists, then go to read the file
    if (does_char_data_exist = fopen("func/char_data/name.txt", "r")) {
        fclose(does_char_data_exist);
        printf("File exists\n");

#ifdef _WIN32
        // Windows command to change directory and execute the file
        system("cd func && start intro.exe");
#else
        // UNIX-based command to change directory and execute the file
        system("cd func && ./intro.exe");
#endif
    } else {
        // If file does not exist, let's make one
        printf("File doesn't exist\n");

#ifdef _WIN32
        // Windows command to change directory and execute the file
        system("cd func && start char_data_generator.exe");
#else
        // UNIX-based command to change directory and execute the file
        system("cd func && ./char_data_generator.exe");
#endif
    }

    return 0;
}

