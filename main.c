#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "lib.h"


int main(void)
{
    struct timespec res;                    //
    long nsec1;                             //
    clock_gettime(CLOCK_REALTIME, &res);    // Set rand() seed according to the nanosecond time of the system clock.
    nsec1=res.tv_nsec;                      //
    srand(nsec1);                           //

    FILE* guess_list=fopen("guess_list.txt", "r");
    int index=rand()%1002;
    char word[WORD_LENGTH+2];
    get_word(word, "word_list.txt", index);
    remove_newline(word);
    int guesses=0;
    char user_guess[WORD_LENGTH+2];
    
    char resolved[WORD_LENGTH];            //
    for (int i=0; i<WORD_LENGTH; i++) {    //This string before resolution looks like '.......'
        resolved[i]='.';                   //
    }                                      //
    
    while (true) {
        printf("Enter Guess: ");
        scanf("%s", user_guess);
        //---------------------
        if (strcmp(user_guess, ".exit")==0) { //To quit game
            printf("Game terminated by user\n");
            fclose(guess_list);
            return -1;
        }

        if (strcmp(user_guess, ".help")==0) { //Help playing the game
            printf(EXPLANATION);
            continue;
        }

        if (in_check(user_guess , guess_list)==0) {
            if (strcmp(user_guess, word)==0) {
                printf("That's Correct\n");
                fclose(guess_list);
                return 0;
            }
            else if (guesses==GUESSES) {
                printf("You lost! The word was: %s\n", word);
                fclose(guess_list);
                return 1;
            }
        }
        else {
            printf("Word not recognized\n");
            reset(resolved);
            continue;
        }
        resolve(user_guess, word, resolved);
        printf("-------------%s\n", resolved);
        reset(resolved);
        guesses+=1;
    }
}
