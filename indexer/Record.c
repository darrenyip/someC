#include <stdlib.h>
#include <string.h>

#include "Record.h"

int recCompare(Record *rec1, Record *rec2) {
    
}

Record *newRecord(const char *token, const char *fileName, int hits) {
    Record *record = (Record *) malloc(sizeof(struct Record));
    
}