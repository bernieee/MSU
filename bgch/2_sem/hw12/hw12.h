#include<stdio.h>

#define ERROR_OPEN -1
#define SUCCESS 0
#define MISTAKE -2

int init_array4(const char *fname, int n, double *x, double *y, double *d);
double lagrange(int n, double x0, double *x, double *y);//1
double classic_newton(int n, double x0, double *x, double *y);//2
double aitken(int n, double x0, double *x, double *y);//3
double derivative_newton(int n, double x0, double *x, double *y, double *d);//4
double sin_eps_x(double x, double eps);//5
double cos_eps_x(double x, double eps);//6
double e_eps_x(double x, double eps);//7
double log_eps_x(double x, double eps);//8
