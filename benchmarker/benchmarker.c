#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* axpy */
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

int benchmark(void) {
    int N;       /* The matrix size, controlled by user input */
    int r, c;    /* Row and Column number */
    int randomX, randomY;  /* Random numbers to fill the matrces */
    int a = rand() % 20; /* Scale number to multiply x matrix */
    int loopCount = 0; /* Count computation loops */

    printf("Enter the size(N * N) of the matrices (Maximum 1,000,000)\n");
    if (scanf("%d", &N) != 1) {
        fprintf(stderr, "Input error!\n");
        return 0;
    }

    if (N > 1000000) {
        fprintf(stderr, "Matrix size is too large!\n");
        return 0;
    }

    /* Initialize and fill the matrix x and y */
    int (*xMatrix)[N] = malloc(N * sizeof(*xMatrix));
    int (*yMatrix)[N] = malloc(N * sizeof(*yMatrix));
    int (*resultMatrix)[N] = malloc(N * sizeof(*resultMatrix));

    if (xMatrix == NULL || yMatrix == NULL || resultMatrix == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        free(xMatrix);
        free(yMatrix);
        free(resultMatrix);
        return 0;
    }

    
    /* Initialize two matrices with random numbers filled in */
    for (r = 0; r < N; r++) {
        for (c = 0; c < N; c++) {
            randomX = rand() % 20;
            randomY = rand() % 20;
            xMatrix[r][c] = randomX;
            yMatrix[r][c] = randomY;
        }
    }

    /* AXPY Computation */
    /* Compute time for total loop */
    clock_t timetotal = clock();
    
    for (r = 0; r < N; r++) {
        for (c = 0; c < N; c++) {
            resultMatrix[r][c] = a * xMatrix[r][c] + yMatrix[r][c];
            loopCount++;
        }
    }
    
    timetotal = clock() - timetotal;

    double timeTaken = ((double)timetotal) / CLOCKS_PER_SEC;
    
    /* Computation time per AXPY */
    double timePerAxpy = timeTaken / ((long long)N * N);
    
    /* Computation time per vector */
    double timePerVec = timeTaken / loopCount;
    
    printf("\n -> 2) Vector length : %lld", (long long)N * N);
    printf("\n -> 3) Number of computing loops: %d", loopCount);
    printf("\n -> 4) Total computation time : %f seconds", timeTaken);
    printf("\n -> 5) Time per axpy vector : %f seconds", timePerAxpy);
    printf("\n -> 6) Time per vector element : %f seconds", timePerVec);
    printf("\n -> 7) ");
    
    free(xMatrix);
    free(yMatrix);
    free(resultMatrix);
    return 0;
}

int main()
{
    time_t t;
    srand((unsigned) time(&t));
    menu();
    benchmark();
 
   return 0;
}


