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

double lambda_sequence(double *A, double *x0, double *x, int n, int m);//1
void sequence_2(double *A, double *x0, double *b, double *x, int n, int m, double t, double *error1, double *error2);//2
void sequence_3(double *A, double *x0, double *b, double *x, double *r, int n, int m, double *error1, double *error2);//3
void sequence_4(double *A, double *x0, double *b, double *x, double *r, int n, int m, double *error1, double *error2);//4
void sequence_5(double *A, double *x0, double *b, double *x, double *r, int n, int m, double *error1, double *error2);//5
void sequence_6(double *A, double *x0, double *b, double *x, double *r, int n, int m, double *error1, double *error2);//6
void sequence_7(double *A, double *x0, double *b, double *x, double *r, int n, int m, double t, double *error1, double *error2);//7
void sequence_8(double *A, double *x0, double *b, double *x, double *r, double *w, int n, int m, double t, double *error1, double *error2);//8
void sequence_9(double *A, double *x0, double *b, double *x, double *r, double *w, int n, int m, double t, double *error1, double *error2);//9
