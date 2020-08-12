#include <stdio.h>
#include "mpi.h"
#define SIZE 16
#define P    4

int i;

int main(int argc, char* argv[]) {
  int numtasks, rank, sendcount, recvcount, source;

/*
  float sendbuf_1[SIZE] = {
    1.0, 2.0, 3.0, 4.0,
    5.0, 6.0, 7.0, 8.0,
    9.0, 10.0, 11.0, 12.0,
    13.0, 14.0, 15.0, 16.0  };
*/
  float sendbuf_1[SIZE] = {
    1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0  };


  float recvbuf_1[SIZE/P];

  float result, result_, dZ;
  
  result  = 0;
  result_ = 0;
  dZ = 1;

  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

  if (numtasks == P) {
    source = 0;
    sendcount = SIZE/P;
    recvcount = SIZE/P;

    MPI_Scatter(sendbuf_1, sendcount, MPI_FLOAT, recvbuf_1, recvcount, MPI_FLOAT, source, MPI_COMM_WORLD);

    for (i=0; i<SIZE/P; i++){
        printf("%f from rank:%d\n", recvbuf_1[i], rank);
        //result = result + ( recvbuf_1[i] * 2);
		result = result + recvbuf_1[i];
    }
	
	result = result * 2;
	
	if (rank == 0){
		result = result - recvbuf_1[0];
	}
	if (rank == P-1){
		result = result - recvbuf_1[(SIZE/P)-1];
	}
	
	
    //printf("Result = %f, from process# %d\n ", result, rank);

    MPI_Reduce(&result, &result_ , 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
	
	result_ = dZ * result_ / 2;

    //printf("Result = %f, from process# %d\n ", result, rank);


    if (rank == 0)
        //MPI_Reduce(&result, &result_ , 1, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);
        printf("\nResult = %f \n\n", result_);

  } else {
    printf("Must specify %d processors. Terminating.\n",SIZE);
  }


  MPI_Finalize();
  return 0;
}
