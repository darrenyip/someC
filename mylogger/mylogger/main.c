#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include "structDef.h"
/* to remove warning comparison between pointer and iteger */
#include <unistd.h>

/*Return true when file name end with suffix .log*/
bool has_log_extension(char const *name)
{
    size_t len = strlen(name);
    return len > 4 && strcmp(name + len - 4, ".log") == 0;
}

/* Main driver */
int main(int argc, char **argv) {
  char cwd[1024];
  char *pathName;
  loglist *head, *tail;
  head = tail = NULL;
  logline *i;
  logline j;
  if((i = (logline *)malloc(sizeof(logline))) == NULL) {
      printf("Allocation falild!\n");
      exit(1);
  }
  
  /* Get current working directory */
  if (argc == 1) {
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
      pathName = cwd;
    } else {
      perror("getcwd() error");
    }
  }
  
  /* Get directory from user input */
  else if (argc == 2) {
    pathName = argv[1];
    fprintf(stdout, "input working dir: %s\n", pathName);
  }
  
  /* Invalid user input from command line */
  else {
    fprintf(stderr, "Error:  invalid No. of command line arguments.\n"); exit(1);
  }
  
  /* End of user input */
  
  /* Open .log files in specified directory (default is cwd). */
  struct dirent *entry;
  DIR *dp;

  dp = opendir(pathName);
  if (dp == NULL) 
  {
    perror("opendir");
    return -1;
  }
  
  /* Save filenames into a string array */
  int maxLogFiles = 16;
  char filetoOpen[maxLogFiles][20];
  
  int fileCount = 0;
  while((entry = readdir(dp)))
    if (has_log_extension(entry->d_name)) {
      /* Avoid open combinedlogs.log file*/
      if(strcmp(entry->d_name, "combinedlogs.log") != 0){
        strcpy(filetoOpen[fileCount], entry->d_name);
        fileCount++;
        if(fileCount == maxLogFiles -1) {
          maxLogFiles *= 2;
        }
      }
    }
  closedir(dp);
  
  /*Now its time to open the files*/
  int k;
  char * buffer = 0;
  long length;
  FILE *f;

  for(k = 0; k < fileCount; k++) {

    f = fopen (filetoOpen[k], "r");
    
    if(f == NULL) {
      printf("\n Unable to open %s \n", filetoOpen[k]);
    }
    
    if (f) {
      fseek (f, 0, SEEK_END);
      length = ftell (f);
      fseek (f, 0, SEEK_SET);
      buffer = malloc (length);
      if (buffer) {
        fread (buffer, 1, length, f);
      }
      fclose (f);
    }
    
    if (buffer) {
      /* Make sure only work in files start with # */
      if(buffer[0] == '#') {
        char * curLine = buffer;
        while(curLine)
        {
          char * nextLine = strchr(curLine, '\n');
          if (nextLine) *nextLine = '\0';  /* Temporarily terminate the current line */
          i = parseLine(curLine);
          if(i != 0) {
            strcpy(j.level,  i->level);
            strcpy(j.timestamp,  i->timestamp);
            strcpy(j.message,  i->message);
            insert_node(&head, &tail, j);
          }
          if (nextLine) *nextLine = '\n';  /* Then restore newline-char, just to be tidy */ 
          curLine = nextLine ? (nextLine+1) : NULL;
        }
      }
  
     
    }
  }
  
  sortList(head);
  
  
  printf("\n --Sorted list: \n");
  printLines(head);
  writeToFile(head);
  
  
  return 0;
}
