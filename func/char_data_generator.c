#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h> // Added for opendir function
#include "textcolors.c"
#include "commands.c"

int main() {
    system("cls");
    printf("\033[0;32m");  // Set text color to green


    printf(YEL  "\nA Voice echos from the distance...\n"   RESET);
    printf("\n\n\n\n\n");

    // Delay before the text starts fading in
    sleep(2);
    
    fadeTextIn(WHT "\nHey, um... excuse me.... how did you even get u- i mean,... who are you?!?\n" RESET, 50);
    printf("\n\n\n\n\n");



    // Check if "char_data" folder already exists
    DIR *dir = opendir("char_data");
    if (dir != NULL) {
        printf("The 'char_data' directory already exists.\n");
        printf("Exiting...\n");
        closedir(dir);
        return 0;
    }

    // Create the "char_data" folder if it doesn't exist
    int result = system("mkdir char_data");
    if (result != 0) {
        printf("Error creating 'char_data' directory.\n");
        return 1;
    }

    // Variables to store user input
    char name[100];
    char age[100];
    char gender[100];

    // Get user input for name
    printf("Enter Your Name:\n");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';  // Remove trailing newline

    // Save name to a separate text file
    char nameFile[100];
    snprintf(nameFile, sizeof(nameFile), "char_data/name.txt");
    FILE *namePtr = fopen(nameFile, "w");
    if (namePtr == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    fprintf(namePtr, "%s", name);
    fclose(namePtr);

    // Get user input for age
    printf("Enter Your Age:\n");
    fgets(age, sizeof(age), stdin);
    age[strcspn(age, "\n")] = '\0';  // Remove trailing newline

    // Save age to a separate text file
    char ageFile[100];
    snprintf(ageFile, sizeof(ageFile), "char_data/age.txt");
    FILE *agePtr = fopen(ageFile, "w");
    if (agePtr == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    fprintf(agePtr, "%s", age);
    fclose(agePtr);

    // Get user input for gender
    printf("Enter Your Gender (Male or Female):\n");
    fgets(gender, sizeof(gender), stdin);
    gender[strcspn(gender, "\n")] = '\0';  // Remove trailing newline

    // Save gender to a separate text file
    char genderFile[100];
    snprintf(genderFile, sizeof(genderFile), "char_data/gender.txt");
    FILE *genderPtr = fopen(genderFile, "w");
    if (genderPtr == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    fprintf(genderPtr, "%s", gender);
    fclose(genderPtr);

    printf("Alright, well ill see you in there!\n");
    system("pause"); // Pause the program (for Windows)

    // Load another .exe file
    system("intro.exe");

    return 0;
}
