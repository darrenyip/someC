/*
* The linked list struct which will be used in functions
*/
typedef struct logline {
  char level[20];
  char timestamp[20];
  char message[100];
} logline;

typedef struct loglist {
  logline line;
  struct loglist *next;
} loglist;
