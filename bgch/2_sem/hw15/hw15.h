#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


#define SUCCESS 0
#define ERROR_OPEN -1
#define ERROR_READ -2

#define N_MAX 10
#define M_MAX 10

void init_matrix(double *a, int m, int n);
int read_matrix(double *a, int m, int, const char *fname);
void print_matrix(double *a, int m, int);

double max_sum_lines(double *a, int m, int n);//1
double max_sum_columns(double *a, int m, int n);//2
double first_norm(double *A, double *b, double *x, double *r, int m, int n);//3
double max_norm(double *A, double *b, double *x, double *r, int m, int n);//4
double max_sum_lines_1_norm(double *A, double *B, double *R, int m, int n);//5
double max_sum_columns_1_norm(double *A, double *B, double *R, int m, int n);//6
void make_b_formula_1(double *a, int m, int n);//7
void make_b_formula_2(double *a, int m, int n);//8
void make_b_formula_3(double *a, int m, int n);//9
void make_b_formula_4(double *a, int m, int n);//10
void replace_max_to_1(double *a, int m, int n);//11
