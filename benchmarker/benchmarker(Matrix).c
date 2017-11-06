#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LOOP 1E4
#define CPU_CLK 2.6e9  /* 2.6GHz for Razer Blade */

/* Benchmark Core */
int benchmark(void) {
    int N;       /* The matrix size, controlled by user input */
    int r, c;    /* Row and Column number */
    int randomX, randomY;  /* Random numbers to fill the matrces */
    int loopCount = 0; /* Count computation loops */
    long long j; /* outer loop (accuracy improvment) count variable */
    
    int smallerLoop; /* Number of accuracy improvement loops when matrix size over 1024 */
    double OPS;
    double ElapsedTime;
	double ElapsedTimeForNXN;
	double ElapsedTimePerVector;
	long long OPS_PER_INSTR;  /* Number of arithmetic ops required per element */
	
	
    /* Declare time.h counter variables */
	time_t start_time;
	time_t end_time;

    printf("Enter the size(N x N) of the matrices:\n");
    if (scanf("%d", &N) != 1) {
        fprintf(stderr, "Input error!\n");
        return 0;
    }

    if (N > 5000) {
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
            randomX = rand() % 100;
            randomY = rand() % 100;
            xMatrix[r][c] = randomX;
            yMatrix[r][c] = randomY;
        }
    }
    
    printf("\n--- Matrices filled with data...  computation begins now...\n");
    
    /* We still need an accuracy improvement loops when matrix size is over 1024*/
    smallerLoop = 100;
    
    OPS_PER_INSTR = 2; /* Arithmetic Ops per vector element from algorithm expressed in C code */

    /* Matrix Computation */
    
    /* Begin timed portion of benchmark */
    start_time = (double)time(0);
    if (N >= 1024) {
        for (j = 0; j < smallerLoop; j++) {
            for (r = 0; r < N; r++) {
                for (c = 0; c < N; c++) {
                    resultMatrix[r][c] = xMatrix[r][c] * yMatrix[r][c];
                    loopCount++;
                }
            }
        }
        
    } else {
        for (j = 0; j <(LOOP); j++) {
            for (r = 0; r < N; r++) {
                for (c = 0; c < N; c++) {
                    resultMatrix[r][c] = xMatrix[r][c] * yMatrix[r][c];
                    loopCount++;
                }
            }
        }
    }
    
    /* End timed portion of benchmark */
    end_time = (double)time(0);
    
    
    ElapsedTime = ((end_time - start_time));
    
    printf("\n -> 1) Number of vector elements per matrix : %lld", (long long)N * N);
    printf("\n -> 2) Total vector elements (2 matrices): %lld", 2 * (long long)N * N);
    
    if( N < 1024) {
        printf("\n -> 3) Number of accuracy improvement loops: %e", (double)LOOP);
    } else {
        printf("\n -> 3) Number of accuracy improvement loops: %d", smallerLoop);
    }
    
    printf("\n -> 4) Total computation time : %0.4e seconds", ElapsedTime);
    
    if (N >= 1024) {
        ElapsedTimeForNXN = ElapsedTime / smallerLoop;
    } else {
        ElapsedTimeForNXN = ElapsedTime / ((double)LOOP);
    }
    
    printf("\n -> 5) Computation time for the complete NxN matrix multiplication : %0.4e seconds", ElapsedTimeForNXN);
    
    ElapsedTimePerVector = ElapsedTimeForNXN / N;
    
    printf("\n -> 6) Computation time per arithmetic operation : %0.4e seconds", ElapsedTimePerVector);
    
    printf("\n -> 7) Estimated OPs per second is: %0.3e  OPs per second", OPS = (OPS_PER_INSTR / ElapsedTimePerVector));
    printf("\n -> 8) Estimated number of clock cycles per OP is %0.2f CPU Clock Cycles per OP\n", (CPU_CLK) / (OPS));
    
    free(xMatrix);
    free(yMatrix);
    free(resultMatrix);
    return 0;
}

/* Matrix */
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

int main()
{
    menu();
    benchmark();
 
   return 0;
}


