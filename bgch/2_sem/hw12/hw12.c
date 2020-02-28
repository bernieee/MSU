#include <stdio.h>
#include <stdlib.h>
#include <math.h> //-lm
#include "hw12.h"


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


static int divided_difference(int n, int k, double *x, double *y)//2
{
    int i;

    for (i = n - 1; i >= k; i--)
    {
        y[i] = (y[i - 1] - y[i]) / (x[i - 1 - k] - x[i]);
    }

    return 0;
}


double classic_newton(int n, double x0, double *x, double *y)//2
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


static int make_scheme(int n, int k, double x0, double *x, double *y)//3
{
    int i;

    for (i = 0; i < n - k; i++)
    {
        y[i] = (y[i + 1] * (x0 - x[i + 1 + k]) - y[i] * (x0 - x[i])) / (x[i + 1 + k] - x[i]);
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


static int derivative_divided_difference(int n, int k, double *x, double *y, double *d, int d_k, int y_k)//4
{
    int i;
    int j;

    for (i = 2 * n - 1; i > k; i--)
    {
        j = i >> 1;

        if (i & 1)// == 1
        {
            d[j] = (y[j] - d[j]) / (x[j - d_k] - x[j]);
        }
        else
        {
            y[j] = (y[j] - d[j - 1]) / (x[j] - x[j - y_k]);
        }
    }

    return 0;
}


double derivative_newton(int n, double x0, double *x, double *y, double *d)//4
{
    int i;
    int j;
    int num;
    int d_k;
    int y_k;
    double L;
    double D;
    double z;

    D = 1.;
    d_k = 1;
    y_k = 1;

    divided_difference(n, 0, x, y);

    /*for (int k = n - 1; k >= 0; k--)
    {
        printf("%lf  %lf\n", d[k], y[k]);
    }

    printf("\n");*/

    for (i = 1; i < 2 * n - 1; i++)
    {
        derivative_divided_difference(n, i, x, y, d, d_k, y_k);

        /*for (int k = n - 1; k >= 0; k--)
        {
            printf("%lf  %lf\n", d[k], y[k]);
        }

        printf("\n");*/

        if (i % 2 == 0)
            d_k++;
        else
            y_k++;
    }

    L = y[0];
    D = (x0 - x[0]);

    for (i = 2; i <= 2 * n; i++)
    {
        j = i >> 1;

        if (i % 2 == 0)
        {
            j -= 1;
            L += d[j] * D;
        }
        else
        {
            L += y[j] * D;
        }

        D *= (x0 - x[j]);
    }

    return L;
}


/*double sin_eps_x(double x, double eps)//5
{
    double sin_eps;
    double step;
    int fact;
    int i;

    x -= floor(x / 2 / M_PI) * 2 * M_PI;// 0 =< x < 2pi

    step = x;
    sin_eps = step;
    i = 1;
    fact = 1;

    while (step > eps)
    {
        step *= x * x / (fact + 1) / (fact + 2);
        fact += 2;
        if (i == 1)
        {
            sin_eps -= step;
            i = 0;
        }
        else
        {
            sin_eps += step;
            i = 1;
        }
    }

    return sin_eps;
}*/


static double sin_(double x, double eps)//5
{
    double sin_eps;
    double step;
    double fact;

    step = x;
    sin_eps = step;
    fact = 2.;

    while (fabs(step) > eps)
    {
        step *= (-1) * x * x / fact / (fact + 1);
        fact += 2;
        sin_eps += step;
    }

    return sin_eps;
}


static double cos_(double x, double eps)//6
{
    double cos_eps;
    double step;
    int fact;

    step = 1.;
    cos_eps = step;
    fact = 1;

    while (fabs(step) > eps)
    {
        step *= (-1) * x * x / fact / (fact + 1);
        fact += 2;
        cos_eps += step;
    }

    return cos_eps;
}


static double sin_quarter(double x, double eps)//5
{
    if ((x >= 0.) && (x <= M_PI_4))//1
    {
        return sin_(x, eps);
    }
    else if ((x > M_PI_4) && (x <= M_PI_2))//2
    {
        return 2 * sin_(x / 2, eps) * cos_(x / 2, eps);
    }
    else if ((x > M_PI_2) && (x <= M_PI_4 * 3))//3
    {
        return 2 * sin_((M_PI - x) / 2, eps) * cos_((M_PI - x) / 2, eps);
    }
    else if ((x > M_PI_4 * 3) && (x <= M_PI))//4
    {
        return sin_(M_PI - x, eps);
    }
    else if ((x > M_PI) && (x <= M_PI_4 * 5))//5
    {
        return (-1) * sin_(x - M_PI, eps);
    }
    else if ((x > M_PI_4 * 5) && (x <= M_PI_2 * 3))//6
    {
        return (-2) * sin_((x - M_PI) / 2, eps) * cos_((x - M_PI) / 2, eps);
    }
    else if ((x > M_PI_2 * 3) && (x <= M_PI_4 * 7))//7
    {
        return (-2) * sin_((2 * M_PI - x) / 2, eps) * cos_((2 * M_PI - x) / 2, eps);
    }
    else if ((x > M_PI_4 * 7) && (x < 2 * M_PI))//8
    {
        return (-1) * sin_(2 * M_PI - x, eps);
    }
    return MISTAKE;
}


static double cos_quarter(double x, double eps)//6
{
    double cos_2;

    if ((x >= 0.) && (x <= M_PI_4))
    {
        return cos_(x, eps);
    }
    else if ((x > M_PI_4) && (x <= M_PI_2))
    {
        cos_2 = cos_(x / 2, eps);
        return 2 * cos_2 * cos_2 - 1;
    }
    else if ((x > M_PI_2) && (x <= M_PI_4 * 3))
    {
        cos_2 = cos_((M_PI - x) / 2, eps);
        return 1 - 2 * cos_2 * cos_2;
    }
    else if ((x > M_PI_4 * 3) && (x <= M_PI))
    {
        return (-1) * cos_(M_PI - x, eps);
    }
    else if ((x > M_PI) && (x <= M_PI_4 * 5))
    {
        return (-1) * cos_(x - M_PI, eps);
    }
    else if ((x > M_PI_4 * 5) && (x <= M_PI_2 * 3))
    {
        cos_2 = cos_((x - M_PI) / 2, eps);
        return 1 - 2 * cos_2 * cos_2;
    }
    else if ((x > M_PI_2 * 3) && (x <= M_PI_4 * 7))
    {
        cos_2 = cos_((2 * M_PI - x) / 2, eps);
        return 2 * cos_2 * cos_2 - 1;
    }
    else if ((x > M_PI_4 * 7) && (x < 2 * M_PI))
    {
        return cos_(2 * M_PI - x, eps);
    }
    return MISTAKE;
}


double sin_eps_x(double x, double eps)//5
{
    double sin_eps;

    x -= floor(x / 2 / M_PI) * 2 * M_PI;// 0 =< x < 2pi

    sin_eps = sin_quarter(x, eps);

    return sin_eps;
}


double cos_eps_x(double x, double eps)//6
{
    double cos_eps;

    x -= floor(x / 2 / M_PI) * 2 * M_PI;// 0 =< x < 2pi

    cos_eps = cos_quarter(x, eps);

    return cos_eps;
}


/*double cos_eps_x(double x, double eps)//6
{
    double cos_eps;
    double step;
    int fact;
    int i;

    x -= floor(x / 2 / M_PI) * 2 * M_PI;// 0 =< x < 2pi

    step = 1;
    cos_eps = step;
    i = 1;
    fact = 0;

    while (step > eps)
    {
        step *= x * x / (fact + 1) / (fact + 2);
        fact += 2;
        if (i == 1)
        {
            cos_eps -= step;
            i = 0;
        }
        else
        {
            cos_eps += step;
            i = 1;
        }
    }

    return cos_eps;
}*/


static double exp_(double x)
{
    double exp_x;
    int i;

    exp_x = 1.;

    for (i = 0; i < (int)x; i++)
    {
        exp_x *= M_E;
    }

    return exp_x;
}

double e_eps_x(double x, double eps)//7
{
    double e_eps_int;
    double e_eps_fract;
    double step;
    double fact;
    int flag = 0;
    int i;

    if (x < 0.)
    {
        e_eps_int = floor(-x);
        x = x + e_eps_int;
        flag = 1;
    }
    else
    {
        e_eps_int = ceil(x);
        x = x - e_eps_int;
    }
    step = 1.;
    e_eps_int = exp_(e_eps_int);
    e_eps_fract = step;
    fact = 1;

    while (fabs(step) > eps)
    {
        step *= x / fact;
        fact++;
        e_eps_fract += step;
    }

    if (flag == 1)
        e_eps_int = 1 / e_eps_int;

    e_eps_int *= e_eps_fract;

    return e_eps_int;
}


double log_eps_x(double x, double eps)//8
{
    double log_eps;
    double log_a;
    double x_2;
    double step;
    double fact;
    int log_2;

    x_2 = x;
    log_2 = 0;

    while (x_2 > 1.)
    {
        x_2 /= 2;
        log_2++;
    }

    log_a = x_2 - 1;
    step = log_a;
    fact = 2;
    log_eps = step;

    while (fabs(step) > eps)
    {
        step *= (-1) * log_a;
        log_eps += step / fact;
        fact++;
    }

    log_eps += log_2 * M_LN2;

    return log_eps;
}
