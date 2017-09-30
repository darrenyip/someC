#include <stdio.h>
#include "constants.h"
#include "struct_def.h"
#include "globals.h"
#include "prototypes.h"

int main(void) {
    int key;
    h = NULL; // Initialize list to empty
    
    while (1) {
        printf("Key value? ");
        scanf("%d", &key);
        if ((key < MINKEY) || (key > MAXKEY)) {
            print_list();
            break;
        }
        else insert_key(key);
    } // End of while
    return 0;
} // End of main
