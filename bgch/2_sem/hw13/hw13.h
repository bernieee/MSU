#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ERROR -1
#define SUCCESS 0
#define MAXIT 10000000

double parabol(double x);
double line(double x);

double sin_deriv(double x);
double parabol_deriv(double x);
double line_deriv(double x);

int init_array123(const char *fname, int n, double *x, double *y);
int init_array4(const char *fname, int n, double *x, double *y, double *d);
//double classic_newton(int n, double x0, double *x, double *y);
int bisect_method_root(double a, double b, double eps, double *x, double (*func) (double x));//1
int newton_method_root(double x0, double eps, double *x, double (*func) (double x), double (*deriv) (double x));//2
int chords_method_root(double a, double b, double eps, double *x, double (*func) (double x));//3
int secant_method_root(double a, double b, double eps, double *x, double (*func) (double x));//4
int interpolation_2_method_root(double a, double b, double eps, double *x, double (*func) (double x));//5
int interpolation_m_method_root(double a, double b, double eps, double *x, int m, double *d, double (*func) (double x));//6
int approximation_method_root(double x0, double eps, double *x, double (*func) (double x));//7
int linear_search_method_max(double a, double b, double eps, double *x, double (*func) (double x));//8
int golden_section_method_max(double a, double b, double eps, double *x, double (*func) (double x));//9
int interpolation_2_method_max(double a, double b, double eps, double *x, double (*func) (double x));//10

