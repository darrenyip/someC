#include "invertIndex.h"
#include "mystrtok.h"

typedef struct Browser {
    Index *index;
} Browser;

int validDir(const char *);

int validFile(const char *);

void indexFile(Browser *, const char*);