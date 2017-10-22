#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "archFunct.h"
#include "handler.h"

int main(int argc, char **argv){
    char **filesName;
    
    if (argc < 3) {
        printf("Invalid input!\n");
        return 0;
    }
    
    /* Create an archive with the specified name from the specified files. */
    if (strcmp(argv[1], "-a") == 0 && argc >= 4) {
        printf("Archiving, please wait...\n");
        archive(argv + 3, argc - 3, argv[2]);
        printf("Arcihve finished!\n");
    }
    
    /* Unpack the specified archive and generate each file contained within. */
    else if (strcmp(argv[1], "-u") == 0 && argc == 3) {
        printf("Unarchiving, please wait...\n");
        unarchive(argv[2]);
        printf("Unarchive finished!\n");
    }
    
    /* Print total size of the archive, the number of files in the archive, */
    /* and each filename along with the corresponding file size. */
    else if (strcmp(argv[1], "-l") == 0 && argc == 3) {
        list(argv[2]);
    }
    
    /* Determine whether or not the specified archive is damaged. */
    else if (strcmp(argv[1], "-v") == 0 && argc >= 4) {
        verification(argv + 3, argc - 3, argv[2]);
    }
    else {
        printf("Invalid command flag!\n");
        return 0;
    }
    
    return 0;
}