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

loglist* mergeLists(loglist* resultlist, loglist* inlist) {
    /*
    loglist* ph = resultlist;
    while(ph->next != NULL){
      ph = ph->next;
    }
    ph->next = inlist->head;
    */
}

/*
* Sort the provided linked list inlist
* and return a pointer to the head of the sorted list.
*/
loglist* sortList(loglist* inlist) {

  /*
  loglist* templist;
  char tlevel, ttimestamp, tmessage;
  while(inlist->next != NULL){
  templist = inlist->next;
    while(templist !=NULL){
      if(inlist->timestamp < templist->timestamp){
        tlevel = resultlist->level;
        ttimestamp = resultlist->timestamp;
        tmessage = resultlist->message;
        resultlist->level = templist->level;
        resultlist->timestamp = templist->timestamp;
        resultlist->message = templist->message;
        templist->level = tlevel;
        templist->timestamp = ttimestamp;
        templist->message = tmessage;
      }
    }
  }
  return resultlist;
  */
}