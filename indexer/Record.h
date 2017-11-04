typedef struct Record {
    char *token;
    char *filename;
    int hits;
} Record;

int recCompare(Record *, Record *);

Record *newRecord(const char *, const char *, int);