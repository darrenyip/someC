/*
* This class implemented 2 methods
* 1. Merge the lists
* 2. sort the lists
*/

/*
* Merge sorted linked list inlist into resultlist
* and return a pointer to the head of the combined list.
*/

#include <string.h>
#include <stdlib.h>
#include "prototypeB.h"

/*
* Sort the provided linked list inlist
* and return a pointer to the head of the sorted list.
*/
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
      if (min->line.timestamp > traverse->line.timestamp) {
        min = traverse;
      }
      traverse = traverse->next;
    }
    swap(head, min);
    head = head->next;
  }
}

