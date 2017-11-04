#include "sortedList.h"

typedef struct Index {
    SortedList *lists[50];
} Index;

int myHash(const char *);

int tokenRecord(Index *, const char *, const char *);

Index *newIndex();

void freeIndex(Index *);