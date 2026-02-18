#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define MAX_STR_LEN 30
#define NUM_SENTENCES 5

bool readSentences(char *rows[], char buffer[]);
void flushInputBuffer(char *actualPos);
bool checkSentenceIsUnique(char *rows[], char *actualPos, int index);
void printSentences(char *rows[]);
