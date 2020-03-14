#include <stdio.h>
#include <stdlib.h>
#include <math.h> //-lm
#include "hw13.h"


static double maximum(double a0, double *a, int n)
{
    int i;
    double res;

    res = fmax(fabs(a[0]), fabs(a0));

    for (i = 1; i < n; i++)
    {
        res = fmax(fabs(res), fabs(a[i]));
    }
    return res;
}


static double minimum(double a0, double *a, int n)
{
    int i;
    double res;

    res = fmin(fabs(a[0]), fabs(a0));

    for (i = 1; i < n; i++)
    {
        res = fmin(fabs(res), fabs(a[i]));
    }
    return res;
}


static int replace(double *xx, double *xx_diff, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        xx_diff[i] = xx[i];
    }
    return 0;
}


static int divided_difference(int n, int k, double *x, double *y)
{
    int i;

    for (i = n - 1; i > k; i--)
    {
        if (!(x[i - 1 - k] - x[i]))
            return ERROR;
        //printf("%lf  %lf  %lf  %lf\n", y[i - 1], y[i], x[i - 1 - k], x[i]);
        y[i] = (y[i - 1] - y[i]) / (x[i - 1 - k] - x[i]);
        //printf("%lf\n", y[i]);
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
        L *= (x0 - x[i - 1]);
    }
    L += y[0];

    return L;
}


int bisect_method_root(double a, double b, double eps, double *x, double (*func) (double x))//1
{
    int it;
    double c;
    double res_a;
    double res_b;
    double res_c;

    res_a = func(a);
    res_b = func(b);

    if (fabs(res_a) < eps)
    {
        *x = a;
        return 0;
    }

    if (fabs(res_b) < eps)
    {
        *x = b;
        return 0;
    }

    for (it = 0; it < MAXIT; it++)
    {
        c = (a + b) / 2;
        res_c = func(c);

        if (fabs(res_c) < eps)
        {
            *x = c;
            return it;
        }

        if ((res_c >= 0 && res_a <= 0) || (res_c <= 0 && res_a >= 0))
        {
            b = c;
            res_b = res_c;
        }
        else if ((res_c >= 0 && res_b <= 0) || (res_c <= 0 && res_b >= 0))
        {
            a = c;
            res_a = res_c;
        }
        else
            return ERROR;
    }

    if (it >= MAXIT)
        return ERROR;

    return it;
}


int newton_method_root(double x0, double eps, double *x, double (*func) (double x), double (*deriv) (double x))//2
{
    int it;
    double x1;
    double res_x0;
    double der_x0;
    double res_x1;

    res_x0 = func(x0);
    der_x0 = deriv(x0);

    if (fabs(res_x0) < eps)
    {
        *x = x0;
        return 0;
    }

    for (it = 0; it < MAXIT; it++)
    {
        if (!der_x0)
            return ERROR;

        x1 = x0 - res_x0 / der_x0;
        res_x1 = func(x1);
        der_x0 = deriv(x1);

        if (fabs(res_x1) < eps)
        {
            *x = x1;
            return it;
        }

        x0 = x1;
        res_x0 = res_x1;
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

    if (fabs(yy[0]) < eps)
    {
        *x = xx[0];
        return 0;
    }

    if (fabs(yy[1]) < eps)
    {
        *x = xx[1];
        return 0;
    }

    for (it = 0; it < MAXIT; it++)
    {
        x0 = classic_newton(2, 0, yy, xx_diff);
        y0 = func(x0);

        printf("%lf %lf %lf\n", xx[0], xx[1], x0);
        printf("%lf %lf %lf\n", yy[0], yy[1], y0);

        if (fabs(y0) < eps)
        {
            *x = x0;
            return it;
        }

        if ((y0 >= 0 && yy[0] <= 0/* && y0 >= a && y0 <= b*/) || (y0 < 0 && yy[0] > 0/* && y0 >= a && y0 <= b*/))
        {
            xx[1] = x0;
            yy[1] = y0;
        }
        else if ((y0 >= 0 && yy[1] <= 0/* && y0 >= a && y0 <= b*/) || (y0 < 0 && yy[1] > 0/* && y0 >= a && y0 <= b*/))
        {
            xx[0] = x0;
            yy[0] = y0;
        }
        else
            return ERROR;

        replace(xx, xx_diff, 2);
    }

    if (it >= MAXIT)
        return ERROR;

    return it;
}



int secant_method_root(double a, double b, double eps, double *x, double (*func) (double x))//4
{
    int it;
    int i;
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

    if (fabs(yy[0]) < eps)
    {
        *x = xx[0];
        return 0;
    }

    if (fabs(yy[1]) < eps)
    {
        *x = xx[1];
        return 0;
    }

    for (it = 0; it < MAXIT; it++)
    {
        x0 = classic_newton(2, 0, yy, xx_diff);
        y0 = func(x0);

        //printf("%lf %lf %lf\n", xx[0], xx[1], x0);
        //printf("%lf %lf %lf\n", yy[0], yy[1], y0);

        //printf("\n%lf\n", x0);

        if (fabs(y0) < eps)
        {
            *x = x0;
            return it;
        }

        if (((yy[0] > 0) && (yy[1] > 0) && (y0 > 0)) || ((yy[0] < 0) && (yy[1] < 0) && (y0 < 0)))
        {
            y_max = maximum(y0, yy, 2);
            //printf("1!\n");

            if ((y_max >= fabs(y0)) && (y_max <= fabs(y0)))
            {
                //printf("1 %lf %lf %lf  %d\n", xx[0], xx[1], x0, it);
                return ERROR;
            }

            for (i = 0; i < 2; i++)
            {
                if ((y_max >= fabs(yy[i])) && (y_max <= fabs(yy[i])))
                {
                    xx[i] = x0;
                    yy[i] = y0;
                }
            }
        }
        else
        {
            y_max = maximum(y0, yy, 2);
            //printf("2!\n");

            if ((y0 > 0 && yy[0] > 0 && y0 >= a && y0 <= b) || (y0 < 0 && yy[0] < 0 && y0 >= a && y0 <= b))// xa
            {
                /*if ((y_max >= fabs(y0)) && (y_max <= fabs(y0)))
                {
                    //printf("2 %lf %lf %lf  %d\n", xx[0], xx[1], x0, it);
                    return ERROR;
                }*/

                //if (fabs(y0) <= fabs(yy[0]))
                //{
                    xx[0] = x0;
                    yy[0] = y0;
                    continue;
                //}
                /*else
                {
                    xx[0] = x0;
                    yy[0] = y0;
                }*/
            }
            if ((y0 > 0 && yy[1] > 0 && y0 >= a && y0 <= b) || (y0 < 0 && yy[1] < 0 && y0 >= a && y0 <= b))// xb
            {
                /*if ((y_max >= fabs(y0)) && (y_max <= fabs(y0)))
                {
                    //printf("3 %d\n", it);
                    //printf("3 %lf %lf %lf  %d\n", xx[0], xx[1], x0, it);
                    return ERROR;
                }*/

                //if (fabs(y0) <= fabs(yy[1]))
                //{
                    xx[1] = x0;
                    yy[1] = y0;
                    continue;
                //}
                /*`else
                {
                    xx[1] = x0;
                    yy[1] = y0;
                }*/
            }
            else// if ((yy[0] > 0 && yy[1] > 0) || (yy[0] < 0 && yy[1] < 0)) ab
            {
                //y_max = maximum(y0, yy, 2);

                //if ((y_max >= fabs(y0)) && (y_max <= fabs(y0)))
                //    return ERROR;

                if (fabs(yy[0]) <= fabs(yy[1]))
                {
                    xx[1] = x0;
                    yy[1] = y0;
                }
                else //if (fabs(yy[0]) <= fabs(yy[1]))
                {
                    xx[0] = x0;
                    yy[0] = y0;
                }
                //else
                //    return ERROR;
            }
            //else
            //    return ERROR;

        }

        replace(xx, xx_diff, 2);
    }

    if (it >= MAXIT)
        return ERROR;

    return it;
}


/*int secant_method_root(double a, double b, double eps, double *x, double (*func) (double x))//4
{
    int it;
    int i;
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

    if (fabs(yy[0]) < eps)
    {
        *x = xx[0];
        return 0;
    }

    if (fabs(yy[1]) < eps)
    {
        *x = xx[1];
        return 0;
    }

    for (it = 0; it < MAXIT; it++)
    {
        x0 = classic_newton(2, 0, yy, xx_diff);
        y0 = func(x0);

        printf("%lf %lf %lf\n", xx[0], xx[1], x0);
        printf("%lf %lf %lf\n", yy[0], yy[1], y0);

        //printf("\n%lf\n", x0);

        if (fabs(y0) < eps)
        {
            *x = x0;
            return it;
        }

        if (((yy[0] > 0) && (yy[1] > 0) && (y0 > 0)) || ((yy[0] < 0) && (yy[1] < 0) && (y0 < 0)))
        {
            y_max = maximum(y0, yy, 2);
            printf("1!\n");

            if ((y_max >= fabs(y0)) && (y_max <= fabs(y0)))
            {
                printf("1 %lf %lf %lf  %d\n", xx[0], xx[1], x0, it);
                return ERROR;
            }

            for (i = 0; i < 2; i++)
            {
                if ((y_max >= fabs(yy[i])) && (y_max <= fabs(yy[i])))
                {
                    xx[i] = x0;
                    yy[i] = y0;
                }
            }
        }
        else
        {
            y_max = maximum(y0, yy, 2);
            printf("2!\n");

            if ((y0 > 0 && yy[0] > 0) || (y0 < 0 && yy[0] < 0))// xa
            {
                if ((y_max >= fabs(y0)) && (y_max <= fabs(y0)))
                {
                    printf("2 %lf %lf %lf  %d\n", xx[0], xx[1], x0, it);
                    return ERROR;
                }

                if (fabs(y0) <= fabs(yy[0]))
                {
                    xx[1] = x0;
                    yy[1] = y0;
                }
                else
                {
                    xx[0] = x0;
                    yy[0] = y0;
                }
            }
            else if ((y0 > 0 && yy[1] > 0) || (y0 < 0 && yy[1] < 0))// xb
            {
                if ((y_max >= fabs(y0)) && (y_max <= fabs(y0)))
                {
                    //printf("3 %d\n", it);
                    printf("3 %lf %lf %lf  %d\n", xx[0], xx[1], x0, it);
                    return ERROR;
                }

                if (fabs(y0) <= fabs(yy[1]))
                {
                    xx[0] = x0;
                    yy[0] = y0;
                }
                else
                {
                    xx[1] = x0;
                    yy[1] = y0;
                }
            }
            else// if ((yy[0] > 0 && yy[1] > 0) || (yy[0] < 0 && yy[1] < 0)) ab
            {
                //y_max = maximum(y0, yy, 2);

                //if ((y_max >= fabs(y0)) && (y_max <= fabs(y0)))
                //    return ERROR;

                if (fabs(yy[0]) <= fabs(yy[1]))
                {
                    xx[1] = x0;
                    yy[1] = y0;
                }
                else //if (fabs(yy[0]) <= fabs(yy[1]))
                {
                    xx[0] = x0;
                    yy[0] = y0;
                }
                //else
                //    return ERROR;
            }
            //else
            //    return ERROR;

        }

        replace(xx, xx_diff, 2);
    }

    if (it >= MAXIT)
        return ERROR;

    return it;
}*/


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

    if (((xx[2] >= xx[1]) && (xx[2] <= xx[1])) || ((xx[2] >= x[0]) && (xx[2] <= x[0])))
        return ERROR;

    if (fabs(yy[0]) < eps)
    {
        *x = xx[0];
        return 0;
    }

    if (fabs(yy[1]) < eps)
    {
        *x = xx[1];
        return 0;
    }

    if (fabs(yy[2]) < eps)
    {
        *x = xx[2];
        return 0;
    }

    for (it = 0; it < MAXIT; it++)
    {
        x0 = classic_newton(3, 0, yy, xx_diff);
        y0 = func(x0);

        if (fabs(y0) < eps)
        {
            *x = x0;
            return it;
        }

        y_max = maximum(y0, yy, 3);

        if ((y_max >= fabs(y0)) && (y_max <= fabs(y0)))
            return ERROR;

        for (i = 0; i < 3; i++)
        {
            if ((y_max >= fabs(yy[i])) && (y_max <= fabs(yy[i])))
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

    h = (fabs(a) + fabs(b)) / (m + 1);

    for (i = 0; i <= m; i++)
    {
        d[i] = a + h * i;//xx_diff
        d[i + m + 1] = a + h * i;//xx
        d[i + 2 * m + 2] = func(d[i]);//yy
    }

    //for (i = 0; i < 3 * (m + 1); i++)
    //    printf("%lf\n", d[i]);

    for (it = 0; it < MAXIT; it++)
    {
        x0 = classic_newton(m + 1, 0, d + 2 * m + 2, d);
        y0 = func(x0);

        if (fabs(y0) < eps)
        {
            *x = x0;
                return it;
        }

        y_max = maximum(y0, d + (2 * m + 2), m + 1);

        if ((y_max >= fabs(y0)) && (y_max <= fabs(y0)))
            return ERROR;

        for (i = 0; i <= m; i++)// m + 1 points
        {
            if ((y_max >= fabs(d[i + 2 * m + 2])) && (y_max <= fabs(d[i + 2 * m + 2])))
            {
                d[i + m + 1] = x0;
                d[i + 2 * m + 2] = y0;
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

        if (fabs(x1 - x0) < eps)
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

    h = (fabs(a) + fabs(b)) / 10;

    x0 = a;
    x1 = a + h;

    if (fabs(h) < eps)
    {
        *x = func(x0);
        return it;
    }

    for (it = 0; it < MAXIT; it++)
    {
        if (fabs(h) < eps)
        {
            *x = func(x1);
            return it;
        }

        //printf("%lf\n", x1);

        if ((func(x0) < func(x1)))
        {
            if (!(x1 + h < b))
                h /= 10;

            x0 = x1;
            x1 += h;
        }
        else if ((func(x0) > func(x1)))
        {
            h = (-1) * h;

            if (!(x1 + h > b))
                h /= 10;

            x0 = x1;
            x1 += h;
        }
        else
            return ERROR;
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
