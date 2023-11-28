/*=========================================================================
 *
 *               University College Dublin
 *          EEEN20010 - Computer Engineering I
 *      "Data Structures and Algorithms through C"
 *
 * Assignment:  Simulate a game of hangman - Lab 3
 *
 * File Name:   hangman.c
 *
 * Description: Play a game of hangman, allow the user to select a letter
 *              or guess a word.
 *
 * Authors:     Zac Reid 20470592
 *
 * Date:        28/11/2023
 *
 *=========================================================================*/

/*==================================================================
 * Systems header files
 *==================================================================*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    /* Prints the word out character by character if the character is contained
        within the letters_discovered string we print the letter if not we print *
     */
    for (int i = 0; i < strlen(word); i++) {
        if (strchr(letters_discovered, word[i]) != NULL) {
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
    int turns = MAX_TURNS;
    char guessed_word[MAX_WORD_LENGTH];
    char guess[MAX_WORD_LENGTH];
    char mode;
    
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

    do {
        /* Display our word and prompt the user what choice of guess they wish to make */
        printf("The word is: ");
        displayWord(word, letters_discovered);

        printf("The number of turns remaining: %i\n", turns);
        printf("Would you like to guess the word [w] or guess a letter [l]: ");
        scanf(" %c", &mode);

        /* Deinciment turns to allow us to keep track of how many turns remaining */
        turns -= 1;

        /* Select the guessing mode for the user. If input is invalid return an error */
        if (mode == 'w' || mode == 'W') {
            printf("What is your guessed word?: ");
            scanf(" %255[^\n]", guess);

            /* Compare guess to the word to see if guess is successful */
            if (strcmp(word, guess) == 0) {
                printf("\n Congratulations! \n");
                return; /* We return to exit game */
            }
        } else if (mode == 'l' || mode == 'L')
        {
            printf("What is your guessed letter?: ");
            scanf(" %c", guess);

            /* We add the guessed letter to our letters_discovered to use when printing word */
            strcat(letters_discovered, &guess[0]);
            /* If the guess is a good one we tell the user */
            if (strchr(word, guess[0]) != NULL) {
                printf("\n***********************************************\n");
                printf("Good Choice!\n");
                continue; /* continue to next round */
            }
        } else {
            printf("Error! The provided choice is invalid!\n");
            exit(-1);
        }

        /* User has inputed a bad choice so we tell them and contnue on to the next round */
        printf("\n***********************************************\n");
        printf("Bad Choice!\n");
    } while (turns > 0); /* Stop the game after turn limit is exeded */

    /* User has failed to guess the word in the turn limit */
    printf("\n***********************************************\n");
    printf("Game Over! Out of turns!\n");
}


int main() {
    char to_continue;
    do {

        /* We call the hangman_game function to start the game we
            at the end of our game we also prompt the user if they
            would like to play the game again.
         */

        hangman_game();

        printf("\n***********************************************\n");
        printf("Do you want to play again [y/n]: ");
        scanf(" %c", &to_continue);
    } while (to_continue == 'y' || to_continue == 'Y');

    return 0;
}