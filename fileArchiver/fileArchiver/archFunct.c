#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "archFunct.h"
#include "constants.h"

/* Create an archive with the specified name and size from the specified files. */
void archive (char** fileNames, int numFiles, char* archivename) {
    /* Necessary variables declared. */
    FILE *ifp;
    FILE *ofp;
    char fileNameLength;
    int fileSize;
    int i;
    int record;
    unsigned char buffer[BUFFERSIZE];
    
    /* Open file for binary writing */
    ofp = fopen(archivename, "wb");
    if (ofp == NULL) {
        printf("Unable to open output file %s for writting!\n", archivename);
        exit(1);
    }
    
    fwrite(&numFiles, sizeof(int), 1, ofp);
    
    /* The archiving processing details */
    /* Following the rule N l1 n1 s1 c1 l2 n2 s2 c2 . . . lN nN sN cN*/
    for (i = 0; i < numFiles; ++i) {
        fileSize = 0;
        fileNameLength = strlen(fileNames[i]) + 1;
        /* 1 byte to store li */
        fwrite(&fileNameLength, sizeof(char), 1, ofp);
        /* li + 1 bytes to store ni */
        fwrite(fileNames[i], sizeof(char), fileNameLength, ofp);
        /* 4 bytes to store si */
        fileSize = getSize(fileNames[i]);
        fwrite(&fileSize, sizeof(int), 1, ofp);
        /* si bytes to store ci */
        ifp = fopen(fileNames[i], "rb");
        if (ifp == NULL) {
            printf("Unable to open input file %s for reading!\n", fileNames[i]);
            exit(1);
        }
        while((record = fread(buffer, sizeof(unsigned char), BUFFERSIZE, ifp)) != 0) {
            fwrite(buffer, sizeof(unsigned char), record, ofp);
        }
        fclose(ifp);
    }
    fclose(ofp);
}

/* Unpack the specified archive and generate each file contained within */
void unarchive (char* archiveFile) {
    FILE *ofp;
    FILE *ifp;
    int numberOfFiles;
    int i;
    char fileNameLength;
    char fileNameBuffer[MAXFILENAME];
    int record;
    unsigned char buffer[BUFFERSIZE];
    int fileSize;
    
    /* Open archived file to get how many files in it*/
    ifp = fopen(archiveFile, "rb");
    if (ifp == NULL) {
        printf("Unable to open archived file %s for reading!\n", archiveFile);
        exit(1);
    }
    /* Read content file by file */
    fread(&numberOfFiles, sizeof(int), 1, ifp);
    
    for (i = 0; i < numberOfFiles; ++i) {
        fread(&fileNameLength, sizeof(char), 1, ifp);
        fread(fileNameBuffer, sizeof(char), fileNameLength, ifp);
        
        /* File pointer for output files */
        ofp = fopen(fileNameBuffer, "wb");
        if (ofp == NULL) {
            printf("Unable to create file %s for writting!\n", fileNameBuffer);
            exit(1);
        }
        
        fread(&fileSize, sizeof(int), 1, ifp);
        /* "Unpacking" processing */
        while((record = fread(buffer, sizeof(unsigned char), BUFFERSIZE < fileSize ? BUFFERSIZE : fileSize, ifp)) != 0) {
            fileSize -= record;
            fwrite(buffer, sizeof(unsigned char), record, ofp);
            if(fileSize == 0) {
                break;
            }
        }
        fclose(ofp);
    }
    fclose(ifp);
}