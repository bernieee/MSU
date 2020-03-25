#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hw13.h"


int main(int argc, char **argv)
{
    int m;
    double a;
    double b;
    double eps;
    double x;
    double *d;
    int result;
    clock_t time;

    if (argc != 5)
    {
        printf("You have only <%d> args instead of <5>\n", argc);
        return -1;
    }

    m = atoi(argv[1]);
    a = atof(argv[2]);      // filename1 to read
    b = atof(argv[3]);
    eps = atof(argv[4]);

    d = malloc((3 * (m + 1)) * sizeof(double));

    time = clock();
    result = interpolation_m_method_root(a, b, eps, &x, m, d, &parabol);
    time = clock() - time;

    printf("Iterations = %d\n", result);
    if (result != -1)
        printf("Root = %lf\n", x);
    printf("Time = %lf\n", (double)time / CLOCKS_PER_SEC);

    free(d);

    return 0;
}
