#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#include "invertIndex.h"

/* A hash method returns an index based on given token's first letter */
int myHash(const char *token) {
    if (isalpha(token[0])) {
        return (int) (tolower(token[0]) - 'a');
    }
    else if (isdigit(token[0])) {
        return (int) (token[0] - '0') + 26;
    }
    else {
        return -1;
    }
}

/* Put passing token into the list */
int tokenRecord(Index *index, const char *token, const char *fileName) {
    SortedList *list;
    int i;
    
    i = myHash(token);
    /* Invalid hash value */
    if (i == -1) {
        return 0;
    }
    /* Add to list */
    else {
        list = index->lists[i];
        if (list == NULL) {
            index->lists[i] = newSortedList(recCompare);
        }
        return insertToList(index->lists[i], token, fileName);
    }
    
}

/* Generate pointer to a new inverted index */
Index *newIndex() {
    return (Index *) malloc(sizeof(struct Index));
}

/* Free memory of index object */
void freeIndex(Index *index) {
    int i;
    for (i = 0; i < 50; i++) {
        freeSortedList(index->lists[i]);
    }
    free(index);
}
