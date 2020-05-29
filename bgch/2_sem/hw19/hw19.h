#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAXIT 100
#define SUCCESS 0
#define ERROR -1

double func(int k, double x);
double func_x(double x);
double sign(double x);

double first_derivative_h(double x, double h, int k, double (*func) (int k, double x)); //1
double first_derivative_h_2(double x, double h, int k, double (*func) (int k, double x)); //2
double second_derivative_h_2(double x, double h, int k, double (*func) (int k, double x)); //3
double trapeze_integral(double a, double b, double n, int k, int *count, double (*func) (int k, double x)); //4
double simpson_integral(double a, double b, double n, int k, int *count, double (*func) (int k, double x)); //5
double trapeze_sqrt_integral(double a, double b, double n, int k, int *count, double (*func) (int k, double x)); //6
double simpson_sqrt_integral(double a, double b, double n, int k, int *count, double (*func) (int k, double x)); //7
int trapeze_eps_integral(double a, double b, double eps, double *r, int k, int *count, double (*func) (int k, double x)); //8
int simpson_eps_integral(double a, double b, double eps, double *r, int k, int *count, double (*func) (int k, double x)); //9
double  trapeze_area_eps_integral(double a, double eps, double *r, int k, int *count, double (*func) (int k, double x)); //10
double simpson_area_eps_integral(double a, double eps, double *r, int k, int *count, double (*func) (int k, double x)); //11
int curve_lengh(double a, double b, double eps, double *r, int k, int *count_x, int *count_y, double (*func_x) (double t), double (*func_y) (int k, double t)); //12
