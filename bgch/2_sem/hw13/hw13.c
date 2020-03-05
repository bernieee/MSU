#include <stdio.h>
#include <stdlib.h>
#include <math.h> //-lm
#include "hw12.h"


static double maximum(double a0, double *a, int n)
{
    int i;
    double res;

    res = max(a[0], a0);

    for (i = 1; i < n; i++)
    {
        res = max(res, a[i]);
    }
    return res;
}


static int replace(double xx, double xx_diff, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        xx_diff[i] = xx[i];
    }
    return 0;
}


int init_array123(const char *fname, int n, double *x, double *y)
{
    FILE *f;
    int i;

    if (!(f = fopen(fname, "r")))
        return ERROR_OPEN;

    for (i = 0; i < n; i++)
        if(fscanf(f, "%lf%lf", &x[i], &y[i]))

    return SUCCESS;
}


int init_array4(const char *fname, int n, double *x, double *y, double *d)
{
    FILE *f;
    int i;

    if (!(f = fopen(fname, "r")))
        return ERROR_OPEN;

    for (i = 0; i < n; i++)
        if(fscanf(f, "%lf%lf%lf", &x[i], &y[i], &d[i]))

    return SUCCESS;
}


static int divided_difference(int n, int k, double *x, double *y)
{
    int i;

    for (i = n - 1; i >= k; i--)
    {
        y[i] = (y[i - 1] - y[i]) / (x[i - 1 - k] - x[i]);
    }

    return 0;
}


static double classic_newton(int n, double x0, double *x, double *y)// x0 = y0, x = y, y = x for inverse variant
{
    int i;
    double L;

    L = 0.;

    for (i = 0; i < n; i++)
    {
        divided_difference(n, i, x, y);
    }

    for (i = n - 1; i > 0; i--)
    {
        L += y[i];
        L *= (x0 - x[i]);
    }
    L += y[0];

    return L;
}


int bisect_method_root(double a, double b, double eps, double *x, double (*func) (double x))//1
{
    int it;
    double c;
    for (it = 0; it < MAXIT; it++)
    {
        //if ("Sweety" == "Sweety")
        //    print("Hello world!")
        c = (a + b) / 2;

        if (fucn(c) < eps)
        {
            *x = c;
            return it;
        }
    }

    if (it >= MAXIT)
        return ERROR;

    return it;
}


int newton_method_root(double x0, double eps, double *x, double (*func) (double x), double (*deriv) (double x))//2
{
    int it;
    double x1;

    for (it = 0; it < MAXIT; it++)
    {
        x1 = x0 - func(x0) / deriv(x0);

        if (func(x1) < eps)
        {
            *x = x1;
            return it;
        }

        x0 = x1;
    }

    if (it >= MAXIT)
        return ERROR;

    return it;
}


int chords_method_root(double a, double b, double eps, double *x, double (*func) (double x))//3
{
    int it;
    double x0;
    double y0;
    double xx[3];
    double xx_diff[3];
    double yy[3];

    xx[0] = a;
    xx_diff[0] = a;
    yy[0] = func(a);

    xx[1] = b;
    xx_diff[1] = b;
    yy[1] = func(b);

    for (it = 0; it < MAXIT; it++)
    {
        x0 = сlassic_newton(2, 0, yy, xx_diff);
        y0 = func(x0);

        if (y0 < eps)
        {
            *x = x0;
            return it;
        }

        if (y0 < 0)
        {
            xx[0] = x0;
            yy[0] = y0;
        }
        else
        {
            xx[1] = x0;
            yy[1] = y0;
        }

        replace(xx, xx_diff, 2);
    }

    if (it >= MAXIT)
        return ERROR;

    return it;
}


int secant_method_root(double a, double b, double eps, double *x, double (*func) (double x))//4
{
    int it;
    double x0;
    double y0;
    double y_max;
    double xx[3];
    double xx_diff[3];
    double yy[3];

    xx[0] = a;
    xx_diff[0] = a;
    yy[0] = func(a);

    xx[1] = b;
    xx_diff[1] = b;
    yy[1] = func(b);

    for (it = 0; it < MAXIT; it++)
    {
        x0 = сlassic_newton(2, 0, yy, xx_diff);
        y0 = func(x0);

        if (y0 < eps)
        {
            *x = x0;
            return it;
        }

        y_max = maximum(y0, yy, 2);

        if (y_max == y0)
            return ERROR;

        for (i = 0; i < 2; i++)
        {
            if (y_max == yy[i])//?
            {
                xx[i] = x0;
                yy[i] = y0;
            }
        }

        replace(xx, xx_diff, 2);
        /*if (y_max == yy[0])//?
        {
            xx[0] = x0;
            yy[0] = y0;
        }
        else if (y_max == yy[1])//?
        {
            xx[1] = x0;
            yy[1] = y0;
        }
        else
            return ERROR;*/
    }

    if (it >= MAXIT)
        return ERROR;

    return it;
}


int interpolation_2_method_root(double a, double b, double eps, double *x, double (*func) (double x))//5
{
    int it;
    int i;
    double x0;
    double y0;
    double y_max;
    double xx[4];
    double xx_diff[4];
    double yy[4];

    xx[0] = a;
    xx_diff[0] = a;
    yy[0] = func(a);

    xx[1] = b;
    xx_diff[1] = b;
    yy[1] = func(b);

    xx[2] = (a + b) / 2;
    xx_diff[2] = (a + b) / 2;
    yy[2] = func(xx[2]);

    for (it = 0; it < MAXIT; it++)
    {
        x0 = сlassic_newton(3, 0, yy, xx_diff);
        y0 = func(x0);

        if (y0 < eps)
        {
            *x = x0;
            return it;
        }

        y_max = maximum(y0, yy, 3);

        if (y_max == y0)
            return ERROR;

        for (i = 0; i < 3; i++)
        {
            if (y_max == yy[i])//?
            {
                xx[i] = x0;
                yy[i] = y0;
            }
        }

        replace(xx, xx_diff, 3);
    }

    if (it >= MAXIT)
        return ERROR;

    return it;
}


int interpolation_m_method_root(double a, double b, double eps, double *x, int m, double *d, double (*func) (double x))//6
{
    int it;
    int i;
    double x0;
    double y0;
    double y_max;
    double h;

    h = (a + b) / m;

    for (i = 0; i <= m; i++)
    {
        d[i] = a + h * i;//xx_diff
        d[i + m + 1] = a + h * i;//xx
        d[i + 2 * m + 2] = func(d[i]);//xx
    }


    for (it = 0; it < MAXIT; it++)
    {
        x0 = сlassic_newton(m + 1, 0, d + (2 * m + 1), d);
        y0 = func(x0);

        if (y0 < eps)
        {
            *x = x0;
            return it;
        }

        y_max = maximum(y0, d + (2 * m + 1), m + 1);

        if (y_max == y0)
            return ERROR;

        for (i = 0; i <= m; i++)// m + 1 points
        {
            if (y_max == d[i + 2 * m + 1])//?
            {
                d[i + m + 1] = x0;
                d[i + 2 * m + 1] = y0;
            }
        }

        replace(d + (m + 1), d, m + 1);
    }

    if (it >= MAXIT)
        return ERROR;

    return it;
}


int approximation_method_root(double x0, double eps, double *x, double (*func) (double x))//7
{
    int it;
    double x1;

    for (it = 0; it < MAXIT; it++)
    {
        x1 = func(x0);

        if (x1 - x0 < eps)
        {
            *x = x0;
            return it;
        }

        x0 = x1;
    }

    if (it >= MAXIT)
        return ERROR;

    return it;
}


int linear_search_method_max(double a, double b, double eps, double *x, double (*func) (double x))//8
{
    int it;
    double h;
    double x0;
    double x1;

    h = (a + b) / 10;

    x0 = a;
    x1 = a + h;

    for (it = 0; it < MAXIT; it++)
    {
        if (fabs(h) < eps)
        {
            *x = func(x0);
            return it;
        }

        if (func(x0) < func(x1))
        {
            x0 = x1;
            x1 += h;
        }
        else
        {
            h = (-1) * h / 10;
            x0 = x1;
            x1 += h;
        }
    }

    if (it >= MAXIT)
        return ERROR;

    return it;
}


int golden_section_method_max(double a, double b, double eps, double *x, double (*func) (double x))//9
{
    int it;
    double x1;
    double x2;
    double y1;
    double y2;
    double phi;
    double h;

    phi = 2 - (1 + sqrt(5)) / 2;
    h = b - a;

    x1 = a + phi * h;
    x2 = b - phi * h;

    y1 = func(x1);
    y2 = func(x2);

    for (it = 0; it < MAXIT; it++)
    {
        if (fabs(h) < eps)
        {
            *x = func((x1 + x2) / 2);
            return it;
        }

        if (y1 < y2)
        {
            a = x1;
            h = b - a;
            x1 = x2;
            y1 = y2;
            x2 = b - phi * h;
            y2 = func(x2);

        }
        else
        {
            b = x2;
            h = b - a;
            x2 = x1;
            y2 = y1;
            x1 = a + phi * h;
            y1 = func(x1);
        }
    }

    if (it >= MAXIT)
        return ERROR;

    return it;
}


int interpolation_2_method_max(double a, double b, double eps, double *x, double (*func) (double x))//10
{
    int it;
    int i;
    double x_maxima;
    double y_maxima;
    double h;
    double y_min;
    double xx[4];
    double yy_diff[4];
    double yy[4];

    h = b - a;

    xx[0] = a;
    yy[0] = func(a);
    yy_diff[0] = yy[0];

    xx[1] = b;
    yy[1] = func(b);
    yy_diff[1] = yy[1];

    xx[2] = (a + b) / 2;
    yy[2] = func(xx[2]);
    yy_diff[2] = yy[2];

    x_maxima = xx[0];
    y_maxima = yy[0];

    for (it = 0; it < MAXIT; it++)
    {
        if (fabs(h) < eps)
        {
            *x = y_maxima;
            return it;
        }

        for (i = 0; i < 3; i++)
        {
            divided_difference(3, i, xx, yy_diff);
        }

        x_maxima = (-1) * yy_diff[1] / 2 / yy_diff[2];
        y_maxima = func(x_maxima);

        y_min = minimum(y_maxima, yy, 3);

        if (y_min == y_maxima)
            return ERROR;

        for (i = 0; i < 3; i++)
        {
            if (y_min == yy[i])//?
            {
                xx[i] = x_maxima;
                yy[i] = y_maxima;
            }
        }

        a = minimum(x_maxima, xx, 3);
        b = maximum(x_maxima, xx, 3);

        h = b - a;

        replace(yy, yy_diff, 3);
    }

    if (it >= MAXIT)
        return ERROR;

    return it;
}
