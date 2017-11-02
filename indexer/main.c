/* Leader: Weicheng Ji */
/* Coder: Zuoli Zhu */
/* Testing and Error Handling: Michael Krill */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <ftw.h>

#include "list.h"

#define PATHNAME 250

int main (int argc, char *argv[]) {
    DIR *dirptr;
    struct dirent *dp;
    char dirName[PATHNAME];
    
    if (argc == 1) {
        printf("CWD:\n");
        if (getcwd(dirName, PATHNAME) == NULL) {
            fprintf(stderr, "Unable to obtain cwd!\n");
            exit(1);
        }
        printf("You are in : %s\n", dirName);
        ftw(".", list, 1);
        exit(1);
    }
    // else if (argc == 2) {
    //     printf("1 Argument");
    //     exit(1);
    // }
    
    else if (argc == 3) {
        printf("Pointed dir: %s\n", argv[2]);
        ftw(argv[2], list, 1);
    }
    
    else {
        fprintf(stderr, "Invalid cmd argument input!\n");
        exit(1);
    }
}