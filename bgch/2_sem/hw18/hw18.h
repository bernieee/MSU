#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


#define SUCCESS 0
#define ERROR_OPEN -1
#define ERROR_READ -2
#define ERROR -3

#define N_MAX 10
#define M_MAX 10

void init_matrix(double *a, int m, int n, int k);
int read_matrix(double *a, int m, int, const char *fname);
void print_matrix(double *a, int m, int);

double residual_1(double *A, double *b, double *x, int n);//L1 norm
double residual_2(double *x, int n);//L1 norm;

void make_b(double *A, double *b, int n);
double make_x_k(double *A_k, double *x_k, int n, int k);
void make_A_k(double *A_k, double *x_k, double a_norm, int n, int k);
void make_b_k(double *b_k, double *x_k, int n, int k);

void gauss_up_diagonal_method(double *A, double *b, double *x, int n);
void reflection_method_24(double *A, double *b, double *x, int n);
