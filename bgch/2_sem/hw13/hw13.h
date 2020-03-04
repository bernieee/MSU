#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ERROR -1
#define SUCCESS 0
#define MAXIT 10000000

int init_array123(const char *fname, int n, double *x, double *y);
int init_array4(const char *fname, int n, double *x, double *y, double *d);
//double classic_newton(int n, double x0, double *x, double *y);
double bisect_method(double a, double b, double eps, double *x, double (*func) (double x));//1
double newton_method(double x0, double eps, double *x, double (*func) (double x), double (*deriv) (double x));//2
double chords_method(double a, double b, double eps, double *x, double (*func) (double x));//3
double secant_method(double a, double b, double eps, double *x, double (*func) (double x));//4
double interpolation_2_method(double a, double b, double eps, double *x, double (*func) (double x));//5
double interpolation_m_method(double a, double b, double eps, double *x, int m, double *d, double (*func) (double x));//6
