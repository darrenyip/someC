#include "invertIndex.h"
#include "mystrtok.h"

/* Struct define of Browser */
typedef struct Browser {
    Index *index;
} Browser;

/* Return 1 if the given name is a valid directory */
int validDir(const char *);

/* Return 1 if the given name is a valid file */
int validFile(const char *);

/* Index a single file */
void indexFile(Browser *, const char*);

/* Index a whole folder(include subfolder) */
void indexDir(Browser *, const char *);

/* Generate new browser pointer to the struct */
Browser *newBrowser();

/* Free memory of browser after use */
void freeBrowser(Browser *);