#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


#define SUCCESS 0
#define ERROR_OPEN -1
#define ERROR_READ -2
#define ERROR -3

#define EPS 9.181147276828874e-16
//#define EPS 1e-17

double L1_matrix_norm(double *A, int n);//L1 norm
double residual_1(double *A, double *b, double *x, double A_norm, int n);//L1 norm
double residual_2(double *x, int n);//L1 norm;

void make_b(double *A, double *b, int n);
int make_x_k(double *A_k, double *x_k, double A_norm, int n, int k);
int make_A_k(double *A_k, double *x_k, int n, int k);
int make_b_k(double *b_k, double *x_k, int n, int k);
int gauss_up_diagonal_method(double *A, double *b, double *x, double A_norm, int n);

int reflection_method_24(double *A, double *b, double *x, double A_norm, int n);
