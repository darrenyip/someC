#include "Record.h"

typedef struct Node {
    Record *data;
    struct Node *next;
    int references;
} Node;

typedef int (*CompareFunction)(Record *, Record *);

typedef struct SortedList {
    Node *head;
    CompareFunction compare;
} SortedList;

SortedList *createSortedList(CompareFunction);