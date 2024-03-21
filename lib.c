#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define WORD_LENGTH 6
#define GUESSES 7

int get_word(char* buffer , char* filename, int index) {
    FILE* file_pointer=fopen(filename , "r");
    int count=0;
    while(fgets(buffer , 10 , file_pointer)!=NULL && count<index) {
        count++;
    }
    fclose(file_pointer);
    return 0;
}

int remove_newline(char* word) {
    if (word==NULL) {
        printf("Invalid string passed \n");
        return -1;
    }
    char* buffer=word;
    for (int i=0; i<strlen(word); i++) {
        if (*buffer=='\n') {
            *buffer='\0';
            return 0;
        }
        buffer++;
    }
    return 2;
}

void reset_ptr(FILE* file_ptr) {
    fseek(file_ptr, 0, SEEK_SET);
}


void resolve(char* user_guess, char* word, char* resolved) {
    /*
    The resolved string might be a bunch of place holder characters, '-' or '_' works well
    Just like wordle, if the guess has a right letter in the right place, it is reflected in the resolved string
    If the letter is not in the right place, but appears elsewhere in the string, its spot is marked with a '|' in the resolved string.
    Any other characters are left untouched.
    */
    for (int i=0; i<WORD_LENGTH; i++) {
        if (user_guess[i]==word[i]) { //Right guess, right place
            resolved[i]=word[i];
        }
        else {                        //Wrong guess
            for (int j=0; j<WORD_LENGTH; j++) {
                if (word[j]==user_guess[i]) { //Check if letter appears anywhere else
                    resolved[i]='|';
                }
            }
        }
    }
}

int in_check(char* word, FILE* file_ptr) {
    if (word==NULL) {
        printf("inavlid word passed\n");
        return -1;
    }
    if (file_ptr==NULL) {
        printf("invalid file passed\n");
        return -2;
    }
    char buffer[WORD_LENGTH+2];
    while(fgets(buffer , WORD_LENGTH+2 , file_ptr) != NULL) {
        remove_newline(buffer);
        if (strcmp(buffer, word)==0) {
            reset_ptr(file_ptr);
            return 0;
        }
    }
    reset_ptr(file_ptr);
    return 1;
}

void reset(char* resolved) {
    for (int i=0; i<WORD_LENGTH; i++) {
        resolved[i]='.';
    }
}
/*
int make_puzzle(char* puzzle, char* word, int difficulty) { //Randomly replace some of the 
    srand(time(NULL));                                      //characters with a blank spot.
    if (word==NULL) {
        printf("Invalid word passed\n");
        return -1;
    }
    if (puzzle==NULL) {
        printf("Invalid memory block to store puzzle\n");
        return -2;
    }
    strcpy(puzzle, word);
    for (int i=0; i<strlen(word); i++) {
        if (rand()%100<difficulty) {
            puzzle[i]='_';
        }
    }
    return 0;
}
*/

//Learning
//The file pointer must be reset to the beginning of the guess_list after reading through it, each time.
