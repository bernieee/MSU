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

void init_matrix(double *a, int m, int n);
int read_matrix(double *a, int m, int, const char *fname);
void print_matrix(double *a, int m, int);

void delete_column_with_min_elem(double *a, int m, int n);//1
void delete_column_and_line_with_min_elem(double *a, int m, int n);//2
void delete_column_with_min_sum(double *a, int m, int n);//3
void delete_column_and_line_with_min_sum(double *a, int m, int n);//4
void delete_column_with_max_sum(double *a, int m, int n);//5
void delete_column_with_max_sum_minus_main_elem(double *a, int m, int n);//6
void delete_column_with_min_dispersion(double *a, int m, int n);//7
void delete_column_and_line_with_max_sum(double *a, int m, int n);//8
void delete_column_and_line_with_max_sum_minus_intersection(double *a, int m, int n);//9
void delete_column_and_line_with_min_dispersion(double *a, int m, int n);//10
