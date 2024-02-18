#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* copied from not-strictly-standard part of math.h */

#define M_PI               3.14159265358979323846
#include <mpi.h>                    /* MPI header file */
#define NUM_STEPS 400000000

double integral_function(double x) {
    return 4.0 / (1.0 + x * x);
}

double calculate_integral(double start, double end, int num_steps) {
    double step_size = (end - start) / num_steps;
    double partial_sum = 0.0;
    int i;

    for (i = 0; i < num_steps; i++) {
        double x = start + (i + 0.5) * step_size;
        partial_sum += integral_function(x);
    }

    return partial_sum * step_size;
}

 /* main program */
int main(int argc, char *argv[]) {

    int nprocs;
    int myid;
	double start_time, end_time;
	double start, end;
    double x, pi;
    double sum = 0.0;
    double step = 1.0/(double) NUM_STEPS;

    /* initialize for MPI */
	MPI_Init(&argc, &argv);

    /* get number of processes */
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

    /* get this process's number (ranges from 0 to nprocs - 1) */
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    /* record start time */
	start_time = MPI_Wtime();

    /* do computation */
	
	// Calculate start and end indices for each processor
	start =0;
	end = 1;
    int local_num_steps = NUM_STEPS / nprocs;
    double local_start = start + myid * local_num_steps * ((end - start) / (double) NUM_STEPS);
    double local_end = local_start + local_num_steps * ((end - start) / (double) NUM_STEPS);


    // Calculate partial integral
    sum = calculate_integral(local_start, local_end, local_num_steps);
	
	MPI_Reduce(&sum, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);


	

    /* record end time */
	end_time = MPI_Wtime();

    /* print results */

    if (myid == 0) 
	{
        printf("parallel program results with %d processes and %d steps:\n", nprocs, NUM_STEPS);
        printf("computed pi = %g  (%17.15f)\n",pi, pi);
        printf("difference between computed pi and math.h M_PI = %17.15f\n", fabs(pi - M_PI));
        printf("time to compute = %g seconds\n", end_time - start_time);
    }

    /* clean up for MPI */
	MPI_Finalize();

    return 0;
}