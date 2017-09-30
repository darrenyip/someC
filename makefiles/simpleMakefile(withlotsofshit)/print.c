#include <stdio.h>
#include <stdlib.h> // for malloc
#include "constants.h"
#include "struct_def.h"
#include "externs.h"

void print_list (void) {
    keyptr cur;
    if(h == NULL) {
        printf("The list is empty.\n");
    } else {
        cur = h;
        while(cur != NULL) {
            printf("%d\n", cur->value);
            cur = cur->next;
        }
    }
}// End of print_list;