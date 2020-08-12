//Help taken from this code: http://homepages.math.uic.edu/~hanson/MPI_Reduce_PPMPI.c, and my assignment code of MPI
//Completed at 07:36PM
#include <stdio.h>
#include "mpi.h"

int i;

int main(int argc, char ** argv) {
	int numtasks, rank, sendcount, recvcount, source;
	
	double a = 0.0; /* Left endpoint */
	double b = 1.0; /* Right endpoint */
	int n = 1024; /* Number of trapezoids */
	double h; /* Trapezoid base length */
	double total; /* Total integral */
	
	double Trap(double local_a, double local_b, int local_n, double h);
	
	//h = (b-a)/n; /* base of trapezoids */
	
	//Initialize MPI
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
	
	{
		source = 0;
	    MPI_Bcast(&a, 1, MPI_DOUBLE, source, MPI_COMM_WORLD);
		MPI_Bcast(&b, 1, MPI_DOUBLE, source, MPI_COMM_WORLD);
		MPI_Bcast(&n, 1, MPI_INT,    source, MPI_COMM_WORLD);

		double h_local = (b-a)/n;    /* h is the same for all processes */
		int    n_local = n/numtasks;  /* So is the number of trapezoids */
		double a_local = a + rank*n_local*h_local;
		double b_local = a_local + n_local*h_local;
		
		double integral = Trap(a_local, b_local, n_local, h_local);

		/* Add up the integrals calculated by each process */
		MPI_Reduce(&integral, &total, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

		/* Print the result */
		if (rank == 0) {
			printf("With n = %d trapezoids, our estimate\n", n);
			printf("of the integral from %f to %f = %f\n", a, b, total); 
		}
	}/*
	else{
		printf("Must specify %d processors. Terminating.\n",P);
	}*/
	
	MPI_Finalize();
	
	//printf("With n = %d trapezoids, our estimate\n",n);
	//printf("of the integral from %f to %f = %f\n",a,b,total);
	return 0;
}



double Trap(double local_a, double local_b, int local_n, double h) {
	double integral;
	double x;
	int i;
	double f(double x);
	integral = (f(local_a) + f(local_b))/2.0;
	x = local_a;
	for (i=1; i<=local_n;i++) {
		x = x+h;
		integral = integral + f(x);
	}
	integral = integral*h;
	return integral;
}
double f(double x) {
	return x*x;
}
