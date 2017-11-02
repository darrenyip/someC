#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structDef.h"

void recordInfo(char *t1, char *t2, char *t3, char *t4) {
    flightRecord fl;
    printf("\nRecording...\n");
    
    printf("%s %s %s %s \n", t1, t2, t3, t4);
    
    printf("\n -Check!- \n");
    
    strcpy(fl.AirlineCodeFlightNumber, t1);
    strcpy(fl.OriginAirportCode, t2);
    strcpy(fl.DestinationAirportCode, t3);
    strcpy(fl.DepartureDate, t4);
    printf("\n-Record Finished-\n");
    
    
    
    
   
    
    
}

// Basic error checking before inserting a record into the binary file
int inputChecking(char *userInput) {
    
    char *firstWord, *secondWord, *thirdWord, *restWords, *context;
    char delimiter[] = " ";
    
    int inputLength = strlen(userInput);
    char *inputCopy = (char*) calloc(inputLength + 1, sizeof(char));
    strncpy(inputCopy, userInput, inputLength);
    
    firstWord  = strtok_r (inputCopy, delimiter, &context);
    secondWord = strtok_r (NULL, delimiter, &context);
    thirdWord = strtok_r (NULL, delimiter, &context);
    restWords = context;
    
    if (strlen(firstWord) != 4) {
        printf("You have invalid AirlineCodeFlightNumber Input! [%s]\n", firstWord);
        return 0;
    }
    else if (strlen(secondWord) != 3) {
        printf("You have invalid OriginAirportCode Input! [%s]\n", secondWord);
        return 0;
    }
    else if (strlen(thirdWord) != 3) {
        printf("You have invalid DestinationAirportCode Input! [%s]\n", secondWord);
        return 0;
    } else if (strlen(restWords) == 0) {
        printf("You have empty input for DepartureDate!\n");
        return 0;
    } else {
        recordInfo(firstWord, secondWord, thirdWord, restWords);
    }
    
    free(inputCopy);
}

void readUserInput() {
    char userInput[150];
    printf("Enter Flight Information: ");
    scanf(" %[^\n]s", userInput);
    inputChecking(userInput);
}