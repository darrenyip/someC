#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

#include "browses.h"


#define PATHNAME 250
#define MAXFILENAME 100

int main (int argc, char *argv[]) {
    DIR *dirptr;
    struct dirent *dp;
    char dirName[PATHNAME];
    Browser *browser;
    int output;
    FILE *fp;
    char resultFile[MAXFILENAME];
    
    browser = newBrowser();
    
    if (argc == 1) {
        strcpy(resultFile, "invind.txt");
        
        if (getcwd(dirName, PATHNAME) == NULL) {
            fprintf(stderr, "Unable to obtain Current Working Directory!!\n");
            exit(1);
        }
        if (validDir(dirName)) {
            indexDir(browser, dirName);
        }
        
    }
    
    else if (argc == 2) {
        strcpy(resultFile, "invind.txt");
        if (validDir(argv[1])) {
            indexDir(browser, argv[1]);
        }
        if (validFile(argv[1])) {
            indexFile(browser, argv[1]);
        }
    }
    
    else if (argc == 3) {
        
        strcpy(resultFile, argv[1]);
        
        if (validFile(argv[2])) {
            indexFile(browser ,argv[2]);
        }
        if (validDir(argv[2])) {
            indexDir(browser, argv[2]);
        }
        else {
            fprintf(stderr, "Error: [%s] is not a valid file or directory.\n", argv[2]);
        }
    }
    
    else {
        fprintf(stderr, "Invalid cmd argument input!\n");
        exit(1);
    }
    
    /* Write result to file*/
    fp = fopen(resultFile, "w");
    if(!fp){
        printf("Unable to open %s for write.\n", resultFile);
        exit(1);
    }
    output = create(browser, fp);
    
    if(output) {
        printf("Index finished! Check file [%s] for result! \n", resultFile);
    }
    else {
        printf("Nothing output.\n");
    }
    freeBrowser(browser);
    fclose(fp);
}