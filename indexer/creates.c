#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#include "creates.h"
#include "browses.h"


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
            iterator = newIterator(list);
            while((record = hasNext(iterator)) != NULL) {
                if(token == NULL || strcmp(record->token, token) != 0) {
                    count = 1;
                    if(!first) {
                        fprintf(fp, "\n</list>\n");
                    }
                    first = 0;
                    token = record->token;
                    fprintf(fp, "<list> %s\n %s %d", token, record->fileName, record->hits);
                }
                else {
                    /* */
                    if (count++ < 10) {
                        fprintf(fp, " %s %d", record->fileName, record->hits);
                    }
                }
            }
            freeIterator(iterator);
        }
    }
    if (close) {
        fprintf(fp, "\n</list>\n");
    }
    return 1;
}
