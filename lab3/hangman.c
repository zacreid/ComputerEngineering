/*=========================================================================
 *
 *               University College Dublin
 *          EEEN20010 - Computer Engineering I
 *      "Data Structures and Algorithms through C"
 *
 * Assignment:  Find root of a cubic function - Lab 2
 *
 * File Name:   root.c
 *
 * Description: find one root of the cubic using an efficient search
 *              method called “the bisection method”
 *
 * Authors:     Zac Reid 20470592
 *
 * Date:        24/10/2023
 *
 *=========================================================================*/

/*==================================================================
 * Systems header files
 *==================================================================*/
#include <stdio.h>
#include <stdlib.h>
/*==================================================================
 * Constant definitions
 *==================================================================*/
#define MAX_FILENAME_LENGTH 256
#define MAX_WORD_LENGTH 256
#define MAX_TURNS 10
/*==================================================================
 * Function definitions
 *==================================================================*/

void displayWord(char word[], char letters_discovered[]) {
    for (int i = 0; i < strlen(word); i++) {
        if (strchr(guessedLetters, word[i]) != NULL) {
            printf("%c", word[i]);
        } else {
            printf("*");
        }
    }
    printf("\n");
}

void hangman_game() {
    char filename[MAX_FILENAME_LENGTH];
    char word[MAX_WORD_LENGTH];
    char letters_discovered[MAX_WORD_LENGTH] = "";
    int turns = 0;
    
    printf("Give the filename with the unknown word: ");
    scanf(" %255[^\n]", filename);
    printf("\n");

    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {  
        printf("Error! Could not open file\n");
        exit(-1);
    }

    // Read a word from the file
    if (fscanf(file, "%255s", word) != 1) {
        printf("Error! Could not read word from file\n");
        fclose(file);
        exit(-1);
    }

    printf("Ready to Start!\n");
}


int main() {
    char to_continue;
    do {

        hangman_game();

        printf("Do you want to play again [y/n]: ");
        scanf(" %c", &to_continue);
    } while (to_continue == 'y' || to_continue == 'Y');

    return 0;
}