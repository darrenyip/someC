#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*This program run axpy algorithm to measure the perfomance of a machine.*/
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
    int N;  /* The matrix size, controlled by user input */
    int r, c; /* Row and Column number */
    int random; /* Random number to fill the matix */
    int a = rand() % 20; /* Scale number to multiply x matrix */
    
    printf("Enter the size(N*N) of the matrixs(Maximum 1,000,000)\n");
    scanf("%d", &N);
    
    if(N > 1000000) {
        fprintf(stderr, "Size of matrix is too large!\n");
        return 0;
    }
  
    /* Initialize and fill the matix x and y */
    int xMatrix[N][N], yMatrix[N][N], resultMatrix[N][N];
    
    
    
    /* Compute time */
    clock_t t;
    
    t = clock();
    
    for (r = 0; r < N; r++) {
        for (c = 0; c < N; c++) {
            random = rand() % 100;
            xMatrix[r][c] = a * random; /* Multiply matix x with random value a */
        }
    }
    
    for (r = 0; r < N; r++) {
        for (c = 0; c < N; c++) {
            int random = rand() % 100;
            yMatrix[r][c] = random;
        }
    }
    
    /* Add two matrix together */
    for (r = 0; r < N; r++) {
        for (c = 0; c < N; c++) {
            resultMatrix[r][c] = xMatrix[r][c] + yMatrix[r][c];
        }
    }
    
    t = clock() - t;

    double timeTaken = ((double)t)/CLOCKS_PER_SEC;
    printf("\n -> Total time : %f seconds\n", timeTaken);
    printf("\n -> Vector length : %d", N*N);
    
}

int main()
{
    time_t t;
    srand((unsigned) time(&t));
    printf("Name: Zuoli Zhu\nProgramming Pxercise: 1\n");
    menu();
    benchmark();
 
   return 0;
}


