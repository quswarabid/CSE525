#include <stdio.h>

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
