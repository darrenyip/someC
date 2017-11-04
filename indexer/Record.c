#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Record.h"

int recCompare(Record *rec1, Record *rec2) {
    int result;
    Record *r1 = (Record *) rec1;
    Record *r2 = (Record *) rec2;
    
    result = strcmp(r1->token, r2->token);
    return result == 0 ? strcmp(r1->fileName, r2->fileName) : result;
}

/* Creates a new record. Returns a pointer to the new object */
Record *newRecord(const char *token, const char *fileName, int hits) {
    Record *record = (Record *) malloc(sizeof(struct Record));
    
    if (record) {
        record->token = (char *) malloc(strlen(token) + 1);
        record->fileName = (char *) malloc(strlen(fileName) + 1);
        if (!record->token || !record->fileName) {
            free(record);
        }
        else {
            strcpy(record->fileName, fileName);
            strcpy(record->token, token);
            record->hits = hits;
            return record;
        }
    }
    return NULL;
}