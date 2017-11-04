/* Leader: Weicheng Ji */
/* Coder: Zuoli Zhu */
/* Testing and Error Handling: Michael Krill */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <ftw.h>

#include "browses.h"

#define PATHNAME 250

int main (int argc, char *argv[]) {
    DIR *dirptr;
    struct dirent *dp;
    char dirName[PATHNAME];
    Browser *browser;
    
    if (argc == 1) {
        printf("CWD:\n");
        if (getcwd(dirName, PATHNAME) == NULL) {
            fprintf(stderr, "Unable to obtain cwd!\n");
            exit(1);
        }
        printf("You are in : %s\n", dirName);
        exit(1);
    }
    
    else if (argc == 3) {
        
        if (validFile(argv[2])) {
            printf("\nvalid!\n");
            indexFile(browser ,argv[2]);
        }
        else if (validDir(argv[2])) {
            printf("\nvalid!\n");
        }
        else {
            fprintf(stderr, "Error: [%s] is not a valid file or directory.\n", argv[2]);
        }
    }
    
    else {
        fprintf(stderr, "Invalid cmd argument input!\n");
        exit(1);
    }
    
    
}