/*
	Code copied from SETH's HOME PAGE[http://www-personal.umich.edu/~smeyer/cuda/grid.pdf] and edited by Quswar[CS2003]
*/

#include <stdio.h>

#define N 16

__global__ void matrixMult (int *a, int *b, int *c, int width) {
 int k, sum = 0;
 int col = threadIdx.x + blockDim.x * blockIdx.x;
 int row = threadIdx.y + blockDim.y * blockIdx.y;
 if(col < width && row < width) {
 for (k = 0; k < width; k++)
 sum += a[row * width + k] * b[k * width + col];
 c[row * width + col] = sum;
 }
}

int main() {
 int h_a[N][N], h_b[N][N], h_c[N][N];
 int *d_a, *d_b, *d_c;
 
 //initialize a and b with real values
 for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
                h_a[i][j] = 2;//(i*j)+i;
                h_b[i][j] = 1;//(i*j)+i;
        }
 }

 
 int size = N * N * sizeof(int);
 
 cudaMalloc((void **) &d_a, size);
 cudaMalloc((void **) &d_b, size);
 cudaMalloc((void **) &d_c, size);
 
 cudaMemcpy(d_a, h_a, size, cudaMemcpyHostToDevice);
 cudaMemcpy(d_b, h_b, size, cudaMemcpyHostToDevice);
 
 dim3 dimGrid(1, 1);
 dim3 dimBlock(N, N);
 
 matrixMult<<<dimGrid, dimBlock>>>(d_a, d_b, d_c, N);
 
 cudaMemcpy(h_c, d_c, size, cudaMemcpyDeviceToHost);
 
 cudaFree(dev_a); cudaFree(dev_b); cudaFree(dev_c);
 
 //print output
 for (int i=0; i<N; i++){
        for (int j=0; j<N; j++){
                printf("%d  ", h_c[i][j]);
        }
        printf("\n");
 }


}