#ifndef WORDLE_H
#define WORDLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define WORD_LENGTH 5
#define GUESSES 7

#define EXPLANATION "Wordle, but with 6 letters\nYou will get 7 tries, to guess a 6 letter word.\nAll the guesses made must be valid words\nRules:\n1. If a letter in the guess is at the right place, it is reflected in the resolved string.\n2. If a letter in the guess appears in the word, but in a different spot, it will be replaced by a '|' in the resolved string.\n3. Any letters in the guess that do not appear in the word will be replaced with a '_' in the resolved string.\nEnjoy !!"

// Function to get a random word from a file
int get_word(char* buffer, char* filename, int index);

// Function to remove the newline character from a string
int remove_newline(char* word);

//Reset the read head to the beginning of the guess_list file
void reset_ptr(FILE* file_ptr);

// Function to resolve the user's guess against the word
void resolve(char* user_guess, char* word, char* resolved);

int in_check(char* word, FILE* file_ptr);

void reset(char* resolved);
#endif // WORDLE_H