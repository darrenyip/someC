#include <stdlib.h>

#include "sortedList.h"

SortedList *createSortedList(CompareFunction cf) {
    SortedList *list = (SortedList *) malloc(sizeof(struct SortedList));
    if (list) {
        list->head = NULL;
        list->compare = cf;
        return list;
    }
    else
        return NULL;
}

int insertToList(SortedList *list, const char *token, const char *fileName) {
    Node *new, *ptr, *prev;
    Record *record, *temp;
    int c, retval;
    
    temp = newRecord(token, fileName, 1);
}