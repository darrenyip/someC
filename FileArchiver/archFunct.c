#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "archFunct.h"

void archive (char** fileNames, int numFiles, char* archivename) {
    FILE *ifp;
    FILE *ofp;
    char fileNameLength;
    int fileSize;
    int i;
    int record;
    unsigned char buffer[1000];
    
    ofp = fopen(archivename, "wb");
    if (ofp == NULL) {
        printf("Unable to open output file %s for writting!\n", archivename);
        exit(1);
    }
    
    fwrite(&numFiles, sizeof(int), 1, ofp);
    
    for (i = 0; i < numFiles; ++i) {
        
        fileSize = 0;
        
        fileNameLength = strlen(fileNames[i]) + 1;
        
        ifp = fopen(fileNames[i], "rb");
        if (ifp == NULL) {
            printf("Unable to open input file %s for reading!\n", fileNames[i]);
            exit(1);
        }
        
        fwrite(&fileNameLength, sizeof(char), 1, ofp);
        fwrite(fileNames[i], sizeof(char), fileNameLength, ofp);
        
        fileSize = getSize(fileNames[i]);
        printf("File size check: %d \n", fileSize);
        fwrite(&fileSize, sizeof(int), 1, ofp);
        
        while((record = fread(buffer, sizeof(unsigned char), 1000, ifp)) != 0) {
            fwrite(buffer, sizeof(unsigned char), record, ofp);
        }
        
        fclose(ifp);
    }
    fclose(ofp);
}

void unarchive (char* archiveFile) {
    FILE *ofp;
    FILE *ifp;
    int numberOfFiles;
    int i;
    char fileNameLength;
    char fileNameBuffer[100];
    int record;
    unsigned char buffer[1000];
    int fileSize;
    
    ifp = fopen(archiveFile, "rb");
    if (ifp == NULL) {
        printf("Unable to open archived file %s for reading!\n", archiveFile);
        exit(1);
    }
    
    fread(&numberOfFiles, sizeof(int), 1, ifp);
    
    for (i = 0; i < numberOfFiles; ++i) {
        fread(&fileNameLength, sizeof(char), 1, ifp);
        fread(fileNameBuffer, sizeof(char), fileNameLength, ifp);
        
        ofp = fopen(fileNameBuffer, "wb");
        if (ofp == NULL) {
            printf("Unable to create file %s for writting!\n", fileNameBuffer);
            exit(1);
        }
        
        fread(&fileSize, sizeof(int), 1, ifp);
        
        while((record = fread(buffer, sizeof(unsigned char), 1000 < fileSize ? 1000 : fileSize, ifp)) != 0) {
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