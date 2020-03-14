#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hw13.h"


int main(int argc, char **argv)
{
    int m;
    int i;
    double a;
    double b;
    double l;
    double r;
    double h;
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

    h = (b - a) / 100;

    l = a;
    r = l + h;

    //time = clock();
    for (i = 0; i < 100; i++)
    {
        result = interpolation_m_method_root(l, r, eps, &x, m, d, &parabol);
        //time = clock() - time;

        //printf("Iterations = %d\n", result);
        if (result != -1)
            printf("Iterations = %d\nRoot = %e\nResidual = %e\n\n", result, x, parabol(x));

        l = r;
        r += h;
        //printf("Time = %lf\n", (double)time / CLOCKS_PER_SEC);
    }

    return 0;
}
