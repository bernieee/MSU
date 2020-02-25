#include <stdio.h>
#include <stdlib.h>
#include <math.h> //-lm


static double l(int n, double x0, int i, double *x)//1
{
    int j;
    double res;

    res = 1.;
    for (j = 0; j < n; j++)
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

    for (i = 0; i < n; i++)
    {
        L += y[i] * l(n, x0, i, x);
    }

    return L;
}


static int divided_difference(int n, int k, double *x, double *y)//2 до куда идем снизу вверх, кажый раз уменьшение на 1
{
    int i;
    for (i = n - 1; i >= k; i--)
    {
        y[i] += (y[i - 1] - y[i]) / (x[i - 1 - k] - x[i]);
    }
    return 0;
}


double newton(int n, double x0, double *x, double *y)//2
{
    int i;
    double L;
    double D;

    L = 0.;
    D = 1.;

    for (i = 0; i < n; i++)
    {
        divided_difference(n, i, x, y);
    }

    for (i = 0; i < n; i++)
    {
        L += y[i] * D;
        D *= (x0 - x[i]);//возможно переполнение??
    }

    /*
    for (i = n - 1; i > 0; i--)
    {
        L += y[i];
        L *= (x0 - x[i];
    }
    L += y[0];
    */

    return L;
}


double make_scheme(int n, int k, double x0, double *x, double *y)//3
{
    int i;
    for (i = 0; i < n - k; i++)
     {
        y[i] += (y[i + 1] * (x0 - x[i + 1 + k]) - y[i] * (x0 - x[i])) / (x[i + 1 + k] - x[i]);
    }
    return 0;
}



double aitken(int n, double x0, double *x, double *y)//3
{
    int i;

    for (i = 0; i < n; i++)
    {
        make_scheme(n, i, x0, x, y);
    }

    return y[0];
}
