#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "browses.h"
#include "mystrtok.h"
#include <ctype.h>

/* Filt all symbols and take out all words */
char *mytok(char *str, int (*test)(int ch)){
    static char *store = NULL;
    char *token;
    if (str != NULL) {
        store = str;
    }
    if (store == NULL) return NULL;
    while (*store && !test(*store)){ /* Skip delimiter */
        ++store;
    }
    if (*store == '\0') return NULL;
    token=store;
    while (*store && test(*store)){
        ++store;
    }
    if (*store == '\0'){
        store = NULL;
    } 
    else {
        *store++ = '\0';
    }
    return token;
}

/* Convert all upper case in string to lower */
void strtolower(char *string) {
    int i;
    for (i = 0; i < strlen(string); i++) {
        string[i] = tolower(string[i]);
    }
}