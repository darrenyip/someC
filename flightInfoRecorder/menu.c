#include <stdio.h>
#include <stdlib.h>
#include "recorder.h"


void loadMenu() {
    int choice;
    char test[100];
    do
    {
        printf("\n------Menu------\n");
        printf("1. Record \n");
        printf("2. Print \n");
        printf("3. Exit \n");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                readUserInput();
                break;
            case 2: 
                
                break;
            case 3: 
                printf("BYE!\n");
                exit(0);
                break;
            default: 
                printf("Invalid choice!\n");
                break;
        }
 
    } while (choice != 3);
}
