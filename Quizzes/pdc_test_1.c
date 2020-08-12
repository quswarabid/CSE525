#include <stdio.h>
#include <omp.h>
#define SIZE   100

int main ()
{
        int i = 0, tid, gmax, gmin, lmax, lmin, array [SIZE];
        for (i = 0; i < SIZE; ++i)
           array [i] = 2*i;
        lmin = array [0];
        lmax = array [0];
        gmax = lmin;
        gmin = lmax;
#pragma omp parallel firstprivate (lmax, lmin) shared (gmax, gmin, array) private (i, tid)
{
        tid = omp_get_thread_num();
        #pragma omp for
        for (i = 1; i < SIZE; ++i)
        {
                if (array[i] > lmax){
                        lmax = array[i];
                }
                if (array[i] < lmin){
                        lmin = array[i];
                }
        }
        #pragma omp critical
        {
                if (lmax > gmax){
                        gmax = lmax;
                }
                if (lmin < gmin){
                        gmin = lmin;
                }
        }

}

        printf ("Global max and min are %d, %d\n", gmax, gmin);
}