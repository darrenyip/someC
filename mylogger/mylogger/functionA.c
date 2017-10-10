/*
* This class implemented 3 methods
* 1. parseLine
* 2. delete the list
* 3. print out the list to the console
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "prototypeA.h"


void insert_node(loglist **h, loglist **t, logline v) {
    loglist *temp;
    if((temp = (loglist *)malloc(sizeof(loglist))) == NULL) {
        printf("Allocation falild!\n");
        exit(1);
    }
    temp->line = v;
    temp->next = NULL;
    if(*h == NULL) {
        *h = *t = temp;
    }
    else {
        (*t)->next = temp;
        *t = (*t)->next;
    }
} /* End of insert */



/* string line will not work in here */
/*
* To construct a logline with 3 fields (Level, Timestamp, Message)
* based on the input string.
* This function allocates memory.
*/
logline* parseLine(char *line) {
    
    const char takeMyComma[] = ",";
    char *token;
    char subLine[3][100];
    int subLineIndex = 0;
    
    
    if (line[0] == '#') {
    //   printf("Header skiped.\n");
      return 0;
    }
    
    /* Get the first comma */
    token = strtok(line, takeMyComma);
    
    /* Walk through other commas */
    while(token != NULL) {
      strcpy(subLine[subLineIndex++], token);
      token = strtok(NULL, takeMyComma);
    }
    
    logline *i;
    if((i = (logline *)malloc(sizeof(logline))) == NULL) {
        printf("Allocation falild!\n");
        exit(1);
    }
    
    strcpy(i->level, subLine[0]);
    strcpy(i->timestamp, subLine[1]);
    strcpy(i->message,  subLine[2]);
    return i;
}

/* Free all memory allocated for the list. */
void deleteList(loglist* l) {
    
}

/* Print all the lines contained in the list. */
void printLines(loglist* l) {
    if (l == NULL) {
    printf("The list is empty.\n");
    }
    else {
        // printf("Logs list : \n");
        while (l != NULL) {
            printf("%s %s %s\n", l->line.level, l->line.timestamp, l->line.message);
            l = l->next;
        }
    }
}/* End of print */


/* Print all the lines contained in the list. */
void writeToFile(loglist* l) {
    FILE *sortedLogs;
    
    if (l == NULL) {
    printf("The list is empty.\n");
    }
    else {
        printf("\n Writing...\n");
        /* Create the file to write */
        if((sortedLogs = fopen("combinedlogs.log", "w")) == NULL) {
            fprintf(stderr, "Could not open file: combinedlogs.log \n");
            exit(1);
        }
        
        /* Write data */
        while(l != NULL) {
            fprintf(sortedLogs, "%s %s %s\n", l->line.level, l->line.timestamp, l->line.message);
            l = l->next;
        }
        
        /* Close file */
        if(fclose(sortedLogs) == EOF) {
            fprintf(stderr, "Could not close file: combinedlogs.log \n");
        }
        printf("\n Done! \n");
    }
}/* End of print */
