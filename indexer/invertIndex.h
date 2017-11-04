#include "sortedList.h"

typedef struct Index {
    SortedList *lists[36];
} Index;

int tokenRecord(Index *, const char *, const char *);

int insertToList(SortedList *, const char *, const char *);