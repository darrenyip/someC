#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>

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
  int i;
  char * buffer = 0;
  long length;
  FILE *f;
  
  for(i = 0; i < fileCount; i++) {
    
    printf("%s \n", logfiles[i]);
    
    f = fopen (logfiles[i], "r");
    
    if(f == NULL) {
      printf("\n ????wtf \n");
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
      printf("%s\n", buffer);
    }
    
  }
  return 0;
}
