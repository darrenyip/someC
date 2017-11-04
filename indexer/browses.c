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

Browser *newBrowser() {
    Browser *browser = (Browser *)malloc(sizeof(struct Browser));
    if(browser) {
        browser->index = newIndex();
        if(browser->index) {
            return browser;
        }
        else {
            free(browser);
        }
    }
    return NULL;
}

void freeBrowser(Browser *browser) {
    if (browser) {
        freeIndex(browser->index);
        free(browser);
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
        strtolower(token);
        tokenRecord(browser->index, token, fileName);
    }
}

/* Browse the directory for indexing all the files */
void indexDir(Browser *browser, const char *dirName) {
    DIR *dir;
    struct dirent *dent;
    dir = opendir(dirName);
    if (!dir) {
        printf("Unable to open directory [%s]!\n", dirName);
    }
    else {
        while ((dent = readdir(dir))) {
            size_t size = strlen(dent->d_name) + strlen(dirName) + 2;
            char *name = calloc(size, sizeof(char));
            
            /* redirects the output of printf to a buffer */
            snprintf(name, size, "%s/%s", dirName, dent->d_name);
            
            /* Ignore the weired dot stuff */
            if (strncmp(dent->d_name, ".", sizeof(char)) == 0) {
                continue;
            }
            /* Check weather the name is a dir or a file */
            else if (validDir(name)) {
                /* And call indexDir itself (recursion) */
                indexDir(browser, name);
            }
            else if (validFile(name)) {
                indexFile(browser, name);
            }
        }
        closedir(dir);
    }
    
}