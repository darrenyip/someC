#include "Record.h"

typedef struct Node {
    Record *data;
    struct Node *next;
    int references;
} Node;

typedef struct ListIterator {
    Node *ptr;
} ListIterator;

typedef int (*CompareFunction)(Record *, Record *);

typedef struct SortedList {
    Node *head;
    CompareFunction compare;
} SortedList;

SortedList *newSortedList(CompareFunction);

Node *newNode(Record *, Node *);

ListIterator *newIterator(SortedList *);

void freeIterator(ListIterator *);

int insertToList(SortedList *, const char *, const char *);

Record *hasNext(ListIterator *);

void freeSortedList(SortedList *);