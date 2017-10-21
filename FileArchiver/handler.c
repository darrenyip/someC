#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "handler.h"

void list(char *archivedFileName){
    
    FILE *ifp;
    
    int i;
    int numberOfFiles;
    char fileNameLength;
    char fileNameBuffer[100];
    int record;
    unsigned char buffer[1000];
    
    int fileSize;
    
    ifp = fopen(archivedFileName, "rb");
    if (ifp == NULL) {
        printf("Unable to open archived file [ %s ] for reading!\n", archivedFileName);
        exit(1);
    }
    
    fileSize = getSize(archivedFileName);
    printf("The size of the archived file [ %s ] is %d bytes.\n", archivedFileName, fileSize);
    
    fread(&numberOfFiles, sizeof(int), 1, ifp);
    printf("There are [%d] file(s) inside this archive.\n", numberOfFiles);
    
    for (i = 0; i < numberOfFiles; ++i) {
        fread(&fileNameLength, sizeof(char), 1, ifp);
        fread(fileNameBuffer, sizeof(char), fileNameLength, ifp);
        fread(&fileSize, sizeof(int), 1, ifp);
        printf("File#[%d] : %s, %d bytes.\n", i + 1, fileNameBuffer, fileSize);
        
        while ((record = fread(buffer, sizeof(unsigned char), 1000 < fileSize ? 1000 : fileSize, ifp)) != 0) {
            fileSize -= record;
            if(fileSize == 0) {
                break;
            }
        }
    }
    fclose(ifp);
}

int insideChecking(char** fileNames, int numFiles, char* archiveName) {
    FILE *ofp;
    FILE *ifp;
    int numberOfFilesInArchive;
    int i, j;
    int fileSize;
    char fileNameLength;
    char fileNameBuffer[100];
    int record1, record2;
    unsigned char buffer1[1000];
    unsigned char buffer2[1000];
    
    ifp = fopen(archiveName, "rb");
    if (ifp == NULL) {
        printf("Unable to open archive file %s for reading!\n", archiveName);
        return 0;
    }
    
    fread(&numberOfFilesInArchive, sizeof(int), 1, ifp);
    if(numFiles != numberOfFilesInArchive) {
        printf("You input [%d] file(s), but there are [%d] file(s) in archived file.\n", numFiles, numberOfFilesInArchive);
        fclose(ifp);
        return 0;
    }
    
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
        while(1) {
            record1 = fread(buffer1, sizeof(unsigned char), 1000, ofp);
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

void verification(char** fileNames, int numFiles, char* archiveName) {
    int i;
    int totalSize;
    int archiveSize;
    
    if (insideChecking(fileNames, numFiles, archiveName) == 1) {
        printf("Archive verified\n");
        return;
    }
    
    totalSize = sizeof(int);
    for (i = 0; i < numFiles; ++i) {
        totalSize += 1;
        totalSize += strlen(fileNames[i])+ 1;
        totalSize += sizeof(int);
        totalSize += getSize(fileNames[i]);
    }
    
    archiveSize = getSize(archiveName);
    if(totalSize != archiveSize) {
        printf("Archive is missing %d bytes content!\n", totalSize - archiveSize);
        return;
    }
    
    printf("Archive is corrupted\n");
}

