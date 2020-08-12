#include <stdio.h>
#include <omp.h>

int main(int argc, char ** argv) {
        double a = 0.0; /* Left endpoint */
        double b = 1.0; /* Right endpoint */
        int n = 1024; /* Number of trapezoids */
        double h; /* Trapezoid base length */

        double total; /* Total integral */

        double Trap(double local_a, double local_b, int local_n, double h);

        h = (b-a)/n; /* base of trapezoids */

        /* Calculate integral */
        total = Trap(a,b,n,h);

        /* print result */
        printf("With n = %d trapezoids, our estimate\n",n);
        printf("of the integral from %f to %f = %f\n",a,b,total);
}



double Trap(double local_a, double local_b, int local_n, double h) {
        double integral_global, integral_local;
        double x;
        int i;
        double f(double x);

        integral_global = (f(local_a) + f(local_b))/2.0;
        integral_local = 0.0;

        x = local_a;

        int num_proc = omp_get_thread_num();

        #pragma omp parallel private(x, integral_local) //shared(integral_global, local_n, num_proc)
        {
                #pragma omp for
                for (i=1; i<=local_n;i++){
                #pragma omp critical
                {
                    x = x+h;
                }
                        integral_local = integral_local + f(x);
                }
                #pragma omp critical
                {
                        integral_global += integral_local;
                }

        }

        integral_global = integral_global * h;                          //h = (b-a)/n; /* base of trapezoids */

        return integral_global;
}



double f(double x) {
        return x*x;
}


