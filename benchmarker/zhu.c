#include <stdio.h>
#include <stdlib.h>

int main()
{
    int N;
    
    int xMatrix[N][N], yMatrix[N][N], resultMatrix[N][N];
    
    printf("Enter the size(N*N) of the matrix\n");
    scanf("%d", &N);
    
    if(N > 10000) {
        fprintf(stderr, "Size of matrix is too big\n");
        exit(1);
    }
}