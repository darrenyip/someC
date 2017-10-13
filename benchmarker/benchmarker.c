#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SYS_CLOCK_SPEED 2400000000

/* BenchMark Core */
int benchmark(void) {
    int N;       /* The size of array, controlled by user input */
    int i;      /* Index of the array */
    int a = rand() % 20; /* Scale number to multiply X Array */
    int loopCount = 0; /* Count computation loops */

    printf("Enter the size of the Array (Maximum 1,000,000)\n");
    if (scanf("%d", &N) != 1) {
        fprintf(stderr, "Input error!\n");
        return 0;
    }
    
    /* Error handle if user input is too large */
    if (N > 1000000) {
        fprintf(stderr, "Array size is too large!\n");
        return 0;
    }

    /* Initialize and fill the Array X and Y */
    int *arrayX = malloc(N * sizeof(int));
    int *arrayY = malloc(N * sizeof(int));
    int *resultArray = malloc(N * sizeof(int));
    
    /* Error handle if malloc fail */
    if (arrayX == NULL || arrayY == NULL || resultArray == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        free(arrayX);
        free(arrayY);
        free(resultArray);
        return 0;
    }

    /* Initialize two arrays with random numbers filled in */
    for (i = 0; i < N; i++) {
        arrayX[i] = rand () % 20;
        arrayY[i] = rand () % 30;
    }

    /* AXPY Computation */
    /* Compute time for total loop */
    clock_t timetotal = clock();
    for (i = 0; i < N; i++) {
        resultArray[i] = a * arrayX[i] + arrayY[i];
        loopCount++;
    }
    timetotal = clock() - timetotal;
    
    /* Convert total time to milliseconds */
    double timeTaken = ((double)timetotal) / CLOCKS_PER_SEC;
    
    /* Computation time per AXPY */
    double timePerAxpy = timeTaken / loopCount;
    
    /* Computation time per vector */
    /* There are 2 arithmetic operations per axpy computation */
    double timePerVec = timePerAxpy / 2;
    
    /* Compute machine cycles per arithmetic operation */
    long int numberOfCycle = timePerVec * SYS_CLOCK_SPEED;
    
    /* Print out result to screen */
    
    printf("\n -> 1) Vector length : %d", N);
    printf("\n -> 2) Number of computing loops: %d", loopCount);
    printf("\n -> 3) Total computation time : %f seconds", timeTaken);
    printf("\n -> 4) Time per axpy vector : %f milliseconds", timePerAxpy * 1000);
    printf("\n -> 5) Time per vector element : %f milliseconds", timePerVec * 1000);
    printf("\n -> 6) The number of machine cycles per arithmetic operation : %ld", numberOfCycle);
    
    /* Refresh memory */
    free(arrayX);
    free(arrayY);
    free(resultArray);
    return 0;
}

/* Cool AXPY computation benchmark menu*/
int menu(void) {
    int choice;
    do {
        printf("\n Menu:");
        printf("\n 1: Run benchmark.");
        printf("\n 2: Quit.\n");
        scanf("%d", &choice);
        (void) getchar();
        switch (choice) {
            case 1:
                benchmark();
                break;
            case 2:
                exit(1);
                break;
            default:
                printf("\n-Error: Invalid input, please try again\n");
                break;
        }
    }while(choice != 2);
    
    return 0;
}

/* Program start in here */
int main()
{
    menu();
    benchmark();
 
   return 0;
}


