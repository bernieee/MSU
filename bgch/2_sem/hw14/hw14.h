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

int symmetry(double *a, int n);//1
double trace(double *a, int n);//2
void transponent(double *a, int n);//3
void matrix_plus_transponent(double *a, int n);//4
void matrix_minus_transponent(double *a, int n);//5
void replace_lines(double *a, int m, int n, int i, int j);//6
void replace_columns(double *a, int m, int n, int i, int j);//7
void sum_lines_multiplied_by_b(double *a, double b, int m, int n, int i, int j);//8
void matrix_multiplied_by_vector_to_vector(double *a, double *b, double *c, int m, int n);//9
void matrix_multiplied_by_matrix_to_matrix(double *a, double *b, double *c, int m, int n, int k);//10

