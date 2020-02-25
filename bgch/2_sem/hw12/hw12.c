#include <stdio.h>
#include <stdlib.h>


static double l(int n, double x0, int i, double *x)//1
{
    int j;
    double res;

    res = 1.;
    for (j = 0; j <= n; j++)
    {
        res *= (x0 - x[j]) / (x[i] - x[j]);
    }

    return res;
}

double lagrange(int n, double x0, double *x, double *y)//1
{
    int i;
    double L;

    L = 0.;

    for (i = 0; i <= n; i++)
    {
        L += y[i] * l(n, x0, i, x);
    }

    return L;
}
