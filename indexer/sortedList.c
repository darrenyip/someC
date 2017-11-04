#include <stdlib.h>
#include <stdio.h>

#include "sortedList.h"

SortedList *newSortedList(CompareFunction cf) {
    SortedList *list = (SortedList *) malloc(sizeof(struct SortedList));
    if (list) {
        list->head = NULL;
        list->compare = cf;
        return list;
    }
    else {
        
        return NULL;
    }
}

/* Create new node for record */
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

/* Create a new list iterator to traversal a list. */
ListIterator *newIterator(SortedList *list) {
    if (!list) {
        return NULL;
    }
    ListIterator *iterator = (ListIterator *) malloc(sizeof(struct ListIterator));
    if (iterator) {
        iterator->ptr = list->head;
        return iterator;
    }
    else
        return NULL;
}

void freeIterator(ListIterator *it) {
    if (!it) {
        return;
    }
    free(it);
}

/* Insertion method that add the record into the linkedlist. Return 1 if successful. */
int insertToList(SortedList *list, const char *token, const char *fileName) {
    Node *brandnewNode, *ptr, *prev;
    Record *record, *temp;
    int c, status;
    
    temp = newRecord(token, fileName, 1);
    
    if (!list) {
        status = 0;
    }
    
    /* If list is empty */
    else if (!list->head) {

        record = newRecord(token, fileName, 1);
        
        brandnewNode = newNode(record, NULL);
        
        if (record && brandnewNode) {
            list->head = brandnewNode;
            status = 1;
        }
        else {
            free(record);
            free(brandnewNode);
            status = 0;
        }
    }
    
    /* If list is not empty */
    else if ((c = list->compare(temp, list->head->data)) <= 0) {
        
        /* Swap with head */
        if (c < 0) {
            record = newRecord(token, fileName, 1);
            brandnewNode = newNode(record, list->head);
            if(record && brandnewNode) {
                list->head = brandnewNode;
                status = 1;
            }
            else {
                free(record);
                free(brandnewNode);
                status = 0;
            }
        }
        else {
            /* Update existing record */
            list->head->data->hits++;
            status = 1;
        }
    }
    else {
        ptr = list->head;
        prev = NULL;
        for (; ptr; prev = ptr, ptr = ptr->next) {
            c = list->compare(temp, ptr->data);
            /* Update matched record */
            if (c == 0) {
                ptr->data->hits++;
                return 1;
            }
            /* Place new node in right place */
            else if (c < 0) {
                record = newRecord(token, fileName, 1);
                brandnewNode = newNode(record, ptr);
                if (record && brandnewNode) {
                    prev->next = brandnewNode;
                    return 1;
                }
                else {
                    free(record);
                    free(brandnewNode);
                    return 0;
                }
            }
        }
        /* Add record to the end of the list */
        record = newRecord(token, fileName, 1);
        brandnewNode = newNode(record, NULL);
        if (record && brandnewNode) {
            prev->next = brandnewNode;
            status = 1;
        }
        else {
            free(record);
            free(brandnewNode);
            status = 0;
        }
    }

    
    return status;
} /* End of insertion */








/* Return the next record in the iterator */
Record *hasNext(ListIterator *it) {
    if (!it || !it->ptr) {
        return NULL;
    }
    
    Record *data = it->ptr->data;
    Node *ptr = it->ptr;
    it->ptr = it->ptr->next;
    
    if (it->ptr) {
        it->ptr->references++;
    }
    
    if (ptr && --ptr->references <= 0) {
        free(ptr);
    }
    return data;
}

/**/
void freeSortedList(SortedList *list) {
    if (list) {
        Node *ptr = list->head;
        Node *prev = NULL;
        while (ptr) {
            prev = ptr;
            ptr = ptr->next;
            free(prev);
        }
        free(list);
    }
}