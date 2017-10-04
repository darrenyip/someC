#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

/* to remove warning comparison between pointer and iteger */
#include <unistd.h>

/* Main driver */
int main(int argc, char **argv) {
  FILE *ifp;
  DIR *dp;
  struct dirent *d;
  char cwd[1024];
  char *pathName;
  
  /* Get current working directory */
  if (argc == 1) {
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
      fprintf(stdout, "current working dir: %s\n", cwd);
      pathName = cwd;
    } else {
      perror("getcwd() error");
    }
  }
  
  /* Get directory from user input */
  else if (argc == 2) {
    pathName = argv[1];
    // fprintf(stdout, "input working dir: %s\n", pathName);
  } 
  
  /* Invalid user input from command line */
  else {
    fprintf(stderr, "Error:  invalid No. of command line arguments.\n"); exit(1);
  }
  
  /* End of user input */
  
  
  /* Open the working directory */
  if (dp = opendir(pathName) == NULL) {
    perror("Unable to open directory");
    exit(1);
  }
  
  
  
  
  
  
  
  
  /* Close the working directory */
  // if (closedir(dp) != 0) {
  //   perror("Unable to close directory");
  // }
  
  
  /* Read content from directory */
  
  
  
  
  
  
  
  
  
  /* List all the file in current directory. */
  // if(d) {
  //   while((dir = readdir(d)) != NULL) {
  //     printf("%s\n", dir->d_name);
  //   }
  //   closedir(d);
  // }
  
  return 0;
}
