/*
* The header file that contains the prototypes using
* in functionA.c
*/

#include "structDef.h"

void insert_node(loglist **h, loglist **t, logline v);
void print_list(loglist *h);
logline* parseLine(char *line);
void deleteList(loglist* l);
void printLines(loglist* l);
