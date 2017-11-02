#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <ftw.h>
#define MODE_MASK 0777

int list (const char *name, const struct stat *status, int type) {
    /* If the call to stat failed, then just return. */
    if (type == FTW_NS) {
        return 0;
    }
    /* Otherwise, print the name of the file, permissions and the ’*’ suffix */
    /* if the file is a directory or a symbolic link. */
    /* The "-30" parameter used in printf call ensures that the name is */
    /* left justified in a field of length 30 characters. The "3o" format */
    /* prints the permissions in octal. */
    if (type == FTW_F) {
        printf("%-30s\t0%3o\n", name, status->st_mode & MODE_MASK);
    }
    else {
        printf("%-30s*\t0%3o\n", name, status->st_mode & MODE_MASK);
    }
    return 0;
} /* End of list. */