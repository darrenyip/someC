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
      // fprintf(stdout, "current working dir: %s\n", cwd);
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
  /* This might be too complicated and not efficient */
  int maxLogFiles = 16;
  char **logfiles = malloc(maxLogFiles * sizeof(char *));
  
  int fileCount = 0;

  while((entry = readdir(dp)))
    if (has_log_extension(entry->d_name)) {
      // strcat(logfiles[fileCount], entry->d_name);
      logfiles[fileCount] = entry->d_name;
      if(fileCount == maxLogFiles -1) {
        maxLogFiles *= 2;
        logfiles = realloc(logfiles, 16 * sizeof(char *));
      }
      fileCount++;
    }
  closedir(dp);
  
  /*Now its time to open the files*/
  int k;
  char * buffer = 0;
  long length;
  FILE *f;

  /* for loop does not work in here */  
  
  /* This chunk of code does not work yet since 
   * fopen (logfiles[k], "r") will not work.
  */
  
  for(k = 0; k < fileCount; k++) {
    
    /* Still stock in open multiple files. */
    /* Might ask stackoverflow later. */
    
    char openThisShit[20];
    // strcpy(openThisShit, logfiles[k]);
    // printf("%s \n", logfiles[k]);
    // printf("%s \n", openThisShit);
    // strcpy(openThisShit, "server.log");
    
    
    // f = fopen (openThisShit, "r");
    
    // if(f == NULL) {
    //   printf("\n ????wtf \n");
    // }
    
    // if (f) {
    //   fseek (f, 0, SEEK_END);
    //   length = ftell (f);
    //   fseek (f, 0, SEEK_SET);
    //   buffer = malloc (length);
    //   if (buffer) {
    //     fread (buffer, 1, length, f);
    //   }
    //   fclose (f);
    // }
    
    if (buffer) {
      /* If the log file is not start with #, skip this log file */
      if(buffer[0] != '#') {
          printf("\nlogfile %s is not start with #. Skipped...\n", logfiles[0]);
      }
  
     char * curLine = buffer;
     while(curLine)
     {
        char * nextLine = strchr(curLine, '\n');
        if (nextLine) *nextLine = '\0';  // temporarily terminate the current line
        i = parseLine(curLine);
        if(i != 0) {
          // printf("deref: %s %s %s \n", i->level, i->timestamp, i->message);
          strcpy(j.level,  i->level);
          strcpy(j.timestamp,  i->timestamp);
          strcpy(j.message,  i->message);
          // printf("REF: %s %s %s \n", j.level, j.timestamp, j.message);
          insert_node(&head, &tail, j);
        }
        if (nextLine) *nextLine = '\n';  // then restore newline-char, just to be tidy    
        curLine = nextLine ? (nextLine+1) : NULL;
     }
    }
    printLines(head);
  }
  return 0;
}
