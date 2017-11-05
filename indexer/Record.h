typedef struct Record {
    char *token;
    char *fileName;
    int hits;
} Record;

/* Compares the words of a record */
int recCompare(Record *, Record *);

/* Generate a new record */
Record *newRecord(const char *, const char *, int);