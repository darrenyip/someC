#include "sortedList.h"

typedef struct Index {
    SortedList *lists[50];
} Index;

/* A simple hash method to turn first letter of the string to number */
int myHash(const char *);

/* Like Java how you did list.add(), this is actual same thing */
int tokenRecord(Index *, const char *, const char *);

/* Generate pointer to a new inverted index */
Index *newIndex();

/* Free index pointer after use */
void freeIndex(Index *);