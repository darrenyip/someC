/*
 * This class implemented sort the lists.
 */

#include <string.h>
#include <stdlib.h>
#include "prototypeB.h"

void swap(loglist *p1, loglist *p2)
{
	logline temp = p1->line;
	p1->line = p2->line;
	p2->line = temp;
}

loglist* sortList(loglist* inlist) {
  
  loglist *head = inlist;
  loglist *traverse;
  loglist *min;
  
  while(head->next) {
    min = head;
    traverse = head->next;
    while(traverse) {
      if (strcmp(min->line.timestamp, traverse->line.timestamp) > 0) {
        min = traverse;
      }
      traverse = traverse->next;
    }
    swap(head, min);
    head = head->next;
  }
}

