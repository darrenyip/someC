#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define FILE "int_axpy.c"
#define SIZE 1 // vector dimension .  use 1000 as baseline.  If vector = 1  and LOOPs=1E10, and /O3 cycle per flop represent approx latency to L1
#define LOOP 1E9 // number of accuracy improvement loops
#define CPU_CLK 2.8e9  //2.8GHz for Surface Pro




int main()

{
	//declare vectors and variables
	long i;  // inner loop and array fill count variable
	long long j; //outer loop (accuracy improvment) count variable
	long * z;   //pointer declaration for VMA resultant vector
	long * x;    //pointer declaration for VMA vector 1
	long * y;     //pointer declaration for VMA vector 3
	long a;    //VMA scalar multiplier declaration
	double NumOfOps;  //variable declaration for total number of arithmetic Ops in computation 
	                   // LOOP * SIZE * #of arithemtic ops requires per element
	double OPS;
	double ElapsedTime;
	double ElapsedTimePerVector;
	double ElapsedTimePerVectorElement;
	long long OPS_PER_INSTR;  //number of arithmetic ops required per element of VMA
	
	//declare time.h counter variables

	time_t start_time;
	time_t end_time;

	
	a = 1; 
	// declare the axpy coefficient  and variables.  Allocate memory/stack space for them  
	z = (long*)malloc(SIZE * sizeof(long));
	x = (long*)malloc(SIZE * sizeof(long));
	y = (long*)malloc(SIZE * sizeof(long));

	//calulate LOOP value for defined accuracy value
	//LOOP = MAX_ITERATIONS * ACCURACY;
	OPS_PER_INSTR = 2;  //  arithmetic Ops per vector element from algorithm expressed in C code



	//fill vectors with random values 1 to 100
	for (i = 0; i <= (SIZE - 1); i++)
	{
		x[i] = (long)1 + rand() % 100;
		y[i] = (long)1 + rand() % 100;
		//printf("Sample of random data generated for y[i] :  %d \n", y[i]);
		z[i] = 0.0;
	}

	printf("\n\nFile being run :  %s  \n", FILE);
	printf("Arrays filled with data...  computation begins now...\n");
	printf("Number of elements per vector is:                       %d   \n", SIZE);
	printf("Number of resolution loops is:                          %e   \n", (double)LOOP);
	printf("Processor clock frequency is:                           %0.2e  cycles per second \n", CPU_CLK);

	NumOfOps = (double)(OPS_PER_INSTR * SIZE*(double)LOOP);  //evaluate total number of multiply adds

	printf("# of floating point multiply adds is:                   %0.3e   \n", NumOfOps);

	//printf("Clocks per Sec =                                        %d \n", CLOCKS_PER_SEC);
	printf("Ops per instruction =                                   %d \n", OPS_PER_INSTR);
	printf("Vectors populated.. computation begins now ... \n\n");


	///begin timed portion of benchmark
	start_time = (double)time(0);
	for (j = 0; j<(LOOP); j++) //loop thru a bunch of times to offset low resolution (1usec) timer
	{
		for (i = 0; i <(SIZE); i++)
		{
		
			z[i] = (a*x[i]) + y[i];  //single line of code to implement axpy
		}
	}


	end_time = (double)time(0);
	///end timed portion of benchmark

	printf("Computation Done !\n\n\n\n");

	//data analysis portion -  compute total elapsed time and other parameters
	ElapsedTime = ((end_time - start_time)); //elapsed time in double precision format
	//printf("start time  %0.4d  \n\n", start_time);

	printf("Measured elasped time was:                              %0.4e seconds \n\n", ElapsedTime);
	
	//optional printfs
	//printf("Start number of seconds since 0 is:  %d  \n", start_time);
	//printf("End number of seconds since 0 is:    %d   \n", end_time);
	//printf("Start time in number of system clock ticks since 0 is:  %0.12e \n", (double)CPU_CLK*start_time);
	//printf("End time in number of system clock ticks since 0 is:    %0.12e   \n", (double)CPU_CLK*end_time);
	//printf("Number of system clock ticks in measurement is :        %0.12e \n\n", CPU_CLK*(end_time - start_time)); */
	//time() is returning an integer value representing the number of seconds since time 0 ..  so for a valid measurement, 
	//the entire computation  must take at lease 1 second,  otherwise the timer won't be able to capture the event.
	//print execution time of multiply add operation
	
	ElapsedTimePerVector = (double)ElapsedTime / (double)LOOP;
	printf("Execution time per vector  is:                          %0.4e  seconds \n", ElapsedTimePerVector);
	ElapsedTimePerVectorElement = ElapsedTimePerVector / ((double)SIZE);
	printf("Execution time per vector element is:                   %0.4e  seconds \n\n", ElapsedTimePerVectorElement);
	printf("Execution time per arithmetic Op  is:                   %0.4e  seconds \n\n", ElapsedTimePerVectorElement / OPS_PER_INSTR);   //need to divide by 2 for complete multiply add functionality
    printf("Estimated OPs per second is:                            %0.3e  OPs per second \n", OPS = (OPS_PER_INSTR / ElapsedTimePerVectorElement)); //ned 2 in numerator for case of multiply add
	printf("Estimated number of clock cycles per OP is              %0.2f  CPU Clock Cycles per OP\n", (CPU_CLK) / (OPS));

	getchar();  //uncomment this if needed by IDE  need to keep command concole open after execution

	free(x);
	free(y);
	free(z);
	return 0;

}
