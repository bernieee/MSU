#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


#define SUCCESS 0
#define ERROR_OPEN -1
#define ERROR_READ -2
#define ERROR -3


void init_matrix(double *a, int m, int n, int k);
int read_matrix(double *a, int m, int n, const char *fname);
void print_matrix(double *a, int m, int n, int max_len);
