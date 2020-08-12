/*
	Code copied from SETH's HOME PAGE[http://www-personal.umich.edu/~smeyer/cuda/grid.pdf] and edited by Quswar[CS2003]
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 32
#define BLOCK_DIM 32

__global__ void matrixAdd (int *a, int *b, int *c) {
 int col = blockIdx.x * blockDim.x + threadIdx.x;
 int row = blockIdx.y * blockDim.y + threadIdx.y;
 int index = col + row * N;
 if (col < N && row < N) {
 c[index] = a[index] + b[index];
 }
}



int main() {
 int h_a[N][N], h_b[N][N], h_c[N][N];
 int *d_a, *d_b, *d_c;
 int size = N * N * sizeof(int);

 //initialize a and b with real values
 for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
                h_a[i][j] = 1;
                h_b[i][j] = 0;
        }
 }

 cudaMalloc((void**)&d_a, size);
 cudaMalloc((void**)&d_b, size);
 cudaMalloc((void**)&d_c, size);

 cudaMemcpy(d_a, h_a, size, cudaMemcpyHostToDevice);
 cudaMemcpy(d_b, h_b, size, cudaMemcpyHostToDevice);

 dim3 dimBlock(BLOCK_DIM, BLOCK_DIM);
 dim3 dimGrid((int)ceil(N/dimBlock.x),(int)ceil(N/dimBlock.y));

 matrixAdd<<<dimGrid,dimBlock>>>(d_a,d_b,d_c);

 cudaMemcpy(h_c, d_c, size, cudaMemcpyDeviceToHost);

 /*free(h_a); free(h_b); free(h_c);*/
 cudaFree(d_a); cudaFree(d_b); cudaFree(d_c);

 //print output
 for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
                printf("%d  ", h_c[i][j]);
        }
        printf("\n");
 }

}
