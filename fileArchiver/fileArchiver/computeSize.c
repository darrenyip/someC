#include <stdio.h>
#include <stdlib.h>

int getSize(char *fileName) {
    FILE *fp;
    int size;
    /* Open file to check the size. */
    fp = fopen(fileName, "r");
    if (fp == NULL) {
        fprintf(stderr, "Can't open input file in.list!\n");
        exit(1);
    }
    /* Fetch the size of the file. */
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    /* Reset the file pointer to beginning position. */
    rewind(fp);
    /* Close the file. */
    fclose(fp);
    /* Return the size. */
    return size;
}