#include <stdio.h>
#include <stdlib.h> // for malloc
#include "constants.h"
#include "struct_def.h"
#include "externs.h"

void insert_key (int k) {
    keyptr x, cur, prev;
    if((x = (keyptr) malloc(sizeof(struct key_record))) == NULL) {
        printf("Allocation failed.\n");
        exit(1);
    }
    
    x->value = k;
    x->next = NULL;
    if(h == NULL) {
        h = x;
    } else {
        cur = h;
        prev = NULL;
        while( cur != NULL) {
            prev = cur;
            cur = cur->next;
        }
        prev->next = x;
    }
} // End of insert_key