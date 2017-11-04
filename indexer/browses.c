#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <ctype.h>

#include "browses.h"

/* Returns 1 if the given directory name is valid directory */
int validDir(const char *dir) {
    DIR *directory = opendir(dir);
    if(directory) {
        closedir(directory);
        return 1;
    } else {
        return 0;
    }
}

/* Returns 1 if the filename is exitings file */
int validFile(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp) {
        fclose(fp);
        return 1;
    }
    else {
        return 0;
    }
}

/* Index a single file */
void indexFile(Browser *browser, const char *fileName) {
    FILE *fp;
    size_t fileSize;
    char *content;
    char *token;
    
    fp = fopen(fileName, "r");
    if(!fp) {
        fprintf(stderr, "Unable to open [%s] for reading", fileName);
    }
    
    /* Read file to a string */
    fseek(fp, 0, SEEK_END);
    fileSize = ftell(fp);
    rewind(fp);
    /* Allocate memory size for content string */
    content = (char *)malloc(fileSize * sizeof(char));
    fread(content, sizeof(char), fileSize, fp);
    fclose(fp);
    
    /* Seperate string into small peice of shit, and save into list */
    for(token = mytok(content, isalnum); token; token = mytok(NULL, isalnum)){
        printf("%s\n", token);
        
        tokenRecord(browser->index, token, fileName);
    }
}