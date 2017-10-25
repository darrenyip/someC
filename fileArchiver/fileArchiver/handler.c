#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "handler.h"
#include "constants.h"

/* Function below will print total size of the archive, */
/* the number of files in the archive, */
/* and each filename along with the corresponding file size. */

void list(char *archivedFileName){
    
    /* Declared variables which will be used */
    FILE *ifp;
    int i;
    int numberOfFiles;
    char fileNameLength;
    char fileNameBuffer[MAXFILENAME];
    int record;
    unsigned char buffer[BUFFERSIZE];
    
    int fileSize;
    
    /* Open the file for binary read */
    ifp = fopen(archivedFileName, "rb");
    if (ifp == NULL) {
        printf("Unable to open archived file [ %s ] for reading!\n", archivedFileName);
        exit(1);
    }
    
    /* Call the function from other source file to compute and get the file size */
    fileSize = getSize(archivedFileName);
    printf("The size of the archived file [ %s ] is %d bytes.\n", archivedFileName, fileSize);
    
    /* Using fread to count files inside an archived file. */
    fread(&numberOfFiles, sizeof(int), 1, ifp);
    printf("There are [%d] file(s) inside this archive.\n", numberOfFiles);
    
    /* Get details from the archived file. */
    for (i = 0; i < numberOfFiles; ++i) {
        /* Get the file name. */
        fread(&fileNameLength, sizeof(char), 1, ifp);
        fread(fileNameBuffer, sizeof(char), fileNameLength, ifp);
        /* Get the file size. */
        fread(&fileSize, sizeof(int), 1, ifp);
        printf("File#[%d] : %s, %d bytes.\n", i + 1, fileNameBuffer, fileSize);
        
        /* Fix the file Size for next fread. */
        while ((record = fread(buffer, sizeof(unsigned char), BUFFERSIZE < fileSize ? BUFFERSIZE : fileSize, ifp)) != 0) {
            fileSize -= record;
            if(fileSize == 0) {
                break;
            }
        }
    }
    fclose(ifp);
}

/* Below is the "private" function for verification function */
int insideChecking(char** fileNames, int numFiles, char* archiveName) {
    
    /* Declared variables which will be used */
    FILE *ofp;
    FILE *ifp;
    int numberOfFilesInArchive;
    int i, j;
    int fileSize;
    char fileNameLength;
    char fileNameBuffer[MAXFILENAME];
    int record1, record2;
    unsigned char buffer1[BUFFERSIZE];
    unsigned char buffer2[BUFFERSIZE];
    
    /* Open the file for binary read */
    ifp = fopen(archiveName, "rb");
    if (ifp == NULL) {
        printf("Unable to open archive file %s for reading!\n", archiveName);
        return 0;
    }
    
    /* Comparing the number of files inside archive file with user's input files */
    fread(&numberOfFilesInArchive, sizeof(int), 1, ifp);
    
    /* Handdling the difference between input files and archived files */
    if(numFiles != numberOfFilesInArchive) {
        printf("You input [%d] file(s), but there are [%d] file(s) in archived file.\n", numFiles, numberOfFilesInArchive);
        fclose(ifp);
        return 0;
    }
    
    /* Print out the files with order number and name */
    for (i = 0; i < numFiles; ++i) {
        fread(&fileNameLength, sizeof(char), 1, ifp);
        fread(fileNameBuffer, sizeof(char), fileNameLength, ifp);
        if (strcmp(fileNameBuffer, fileNames[i]) != 0) {
            return 0;
        }
        
        ofp = fopen(fileNameBuffer, "rb");
        if (ofp == NULL) {
            printf("Unable to open file %s for reading!\n", fileNameBuffer);
            return 0;
        }
        fread(&fileSize, sizeof(int), 1, ifp);
        
        /* Compare content between archvied file and input files */
        while(1) {
            record1 = fread(buffer1, sizeof(unsigned char), BUFFERSIZE, ofp);
            if (record1 == 0) {
                break;
            }
            record2 = fread(buffer2, sizeof(unsigned char), record1, ifp);
            if (record1 != record2) {
                printf("Content of files are different.\n");
                fclose(ifp);
                fclose(ofp);
                return 0;
            }
            for(j = 0; j < record1; ++j) {
                if(buffer1[j] != buffer2[j]) {
                    fclose(ifp);
                    fclose(ofp);
                    return 0;
                }
            }
        }
        fclose(ofp);
    }
    fclose(ifp);
    return 1;
}

/* Determine whether or not the specified archive is damaged. */
void verification(char** fileNames, int numFiles, char* archiveName) {
    int i;
    int totalSize;
    int archiveSize;
    
    if (insideChecking(fileNames, numFiles, archiveName) == 1) {
        printf("Archive verified!\n");
        return;
    }
    
    /* Compute input files size */
    totalSize = sizeof(int);
    for (i = 0; i < numFiles; ++i) {
        totalSize += 1;
        totalSize += strlen(fileNames[i])+ 1;
        totalSize += sizeof(int);
        totalSize += getSize(fileNames[i]);
    }
    /* Compare archived file size with input totoal size to see if missing some data. */
    archiveSize = getSize(archiveName);
    if(totalSize != archiveSize) {
        printf("Archive is missing %d bytes content!\n", totalSize - archiveSize);
        return;
    }
    printf("Archive is corrupted\n");
}

