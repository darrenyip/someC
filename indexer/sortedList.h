#include "Record.h"

/* Type define of list Node */
typedef struct Node {
    Record *data;
    struct Node *next;
    int references;
} Node;

/* Type define of the list iterator */
typedef struct ListIterator {
    Node *ptr;
} ListIterator;

/* Function call of a comparison function */
typedef int (*CompareFunction)(Record *, Record *);

/* Type define of the list */
typedef struct SortedList {
    Node *head;
    CompareFunction compare;
} SortedList;

/* Generate new list */
SortedList *newSortedList(CompareFunction);

/* Generate new node */
Node *newNode(Record *, Node *);

/* Generate new iterator object */
ListIterator *newIterator(SortedList *);

/* Free memory after use iterator */
void freeIterator(ListIterator *);

/* Insertion method of the linked list */
int insertToList(SortedList *, const char *, const char *);

/* Check if node has next pointer */
Record *hasNext(ListIterator *);

/* Free memory after usage */
void freeSortedList(SortedList *);