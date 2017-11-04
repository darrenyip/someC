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

Node *newNode(Record *data, Node *next) {
    Node *node = (Node *) malloc(sizeof(struct Node));
    if(node) {
        node->data = data;
        node->next = next;
        node->references = 1;
        return node;
    }
    else {
        return NULL;
    }
}

int insertToList(SortedList *list, const char *token, const char *fileName) {
    Node *brandnewNode, *ptr, *prev;
    Record *record, *temp;
    int c, retval;
    
    temp = newRecord(token, fileName, 1);
    
    if (!list) {
        retval = 0;
    }
    /* If list is empty */
    else if (!list->head) {
        record = newRecord(token, fileName, 1);
        brandnewNode = newNode(record, NULL);
        if (record && brandnewNode) {
            list->head = brandnewNode;
            retval = 1;
        }
        else {
            free(record);
            free(brandnewNode);
            retval = 0;
        }
    }
    /* If list is not empty */
    else if ((c = list->compare(temp, list->head->data)) <= 0) {
        if (c < 0) {
            
        }
    }
}