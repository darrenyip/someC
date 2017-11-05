#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#include "creates.h"

/* Traversal the whole sorted lists and print to the file, return 1 if successful */
int create(Browser *browser, FILE *fp) {
    Record *record;
    SortedList *list;
    ListIterator *iterator;
    char *token;
    int i, first, close, count;
    
    close = 0;
    count = 0;
    first = 1;
    
    /* Traversal the whole lists */
    for (i = 0; i < 50; i++) {
        count = 0;
        token = NULL;
        list = browser->index->lists[i];
        if (list) {
            close = 1;
            /* Generate list iterator to traversal all records in this list */
            iterator = newIterator(list);
            /* Looks like Java? Of course, we love Java. */
            while((record = hasNext(iterator)) != NULL) {
                if(token == NULL || strcmp(record->token, token) != 0) {
                    count = 1;
                    if(!first) {
                        fprintf(fp, "\n</list>\n");
                    }
                    first = 0;
                    token = record->token;
                    /* This is actually what you want to see inside the result file */
                    fprintf(fp, "<list> %s\n %s %d", token, record->fileName, record->hits);
                }
                else {
                    /*Print first 10 records of this particular list, avoid too many content of one term*/
                    if (count++ < 10) {
                        fprintf(fp, " %s %d", record->fileName, record->hits);
                    }
                }
            }
            /* Free memory after use, C does not have trash recycle. */
            freeIterator(iterator);
            /* But Java does. XD */
        }
    }
    if (close) {
        fprintf(fp, "\n</list>\n");
    }
    return 1;
}