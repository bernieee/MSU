#include "hw19.h"


double func(int k, double x)
{
    if (k == 0)
        return 1;
    if (k == 1)
        return 1 + x;
    if (k == 2)
        return 1 + x + x * x;
    if (k == 3)
        return 1 + x + x * x + x * x * x;
    if (k == 4)
        return 1 + x + x * x + x * x * x + x * x * x * x;
    if (k == 5)
        return exp(-x);
    if (k == 6)
        return 1 / (25 * x * x + 1);
    return ERROR;
}


double func_x(double x)
{
    return x;
}


double sign(double x)
{
    if (x > 0)
        return 1;
    else if (x < 0)
        return -1;
    else
        return 0;
}


double first_derivative_h(double x, double h, int k, double (*func) (int k, double x)) //1 error = O(h)
{
    double res;
    double x1;
    double x2;
    double y1;
    double y2;

    x1 = x;
    x2 = x + h;

    y1 = func(k, x1);
    y2 = func(k, x2);


    if (fabs(h) > 0)
    {
        res = (y2 - y1) / h;

        return res;
    }
    else
    {
        return ERROR;
    }
}


double first_derivative_h_2(double x, double h, int k, double (*func) (int k, double x)) //2 error = O(h^2)
{
    double res;
    double x1;
    double x2;
    double x3;
    double y1;
    double y2;
    double y3;

    x1 = x - h;
    x2 = x;
    x3 = x + h;

    y1 = func(k, x1);
    y2 = func(k, x2);
    y3 = func(k, x3);


    if (fabs(h) > 0)
    {
         y3 = (y3 - y2) / h;
         y2 = (y2 - y1) / h;
         y3 = (y3 - y2) / 2 / h;
         res = y2 + y3 * h;

         return res;
    }
    else
    {
        return ERROR;
    }
}


double second_derivative_h_2(double x, double h, int k, double (*func) (int k, double x)) //3 error = O(h^2)
{
    double res;
    double x1;
    double x2;
    double x3;
    double y1;
    double y2;
    double y3;

    x1 = x - h;
    x2 = x;
    x3 = x + h;

    y1 = func(k, x1);
    y2 = func(k, x2);
    y3 = func(k, x3);

    if (fabs(h) > 0)
    {
         y3 = (y3 - y2) / h;
         y2 = (y2 - y1) / h;
         y3 = (y3 - y2) / 2 / h;
         res = 2 * y3;

         return res;
    }
    else
    {
        return ERROR;
    }
}


double trapeze_integral(double a, double b, double n, int k, int *count, double (*func) (int k, double x)) //4 error = O(h^2)
{
    double res;
    double x;
    double h;
    int i;

    res = (func(k, a) + func(k, b)) / 2;
    *count = 2;

    h = (b - a) / n;

    for (i = 1; i < n; i++)
    {
        x = a + h * i;
        res += func(k, x);
        *count += 1;
    }

    res *= h;

    return res;
}


double simpson_integral(double a, double b, double n, int k, int *count, double (*func) (int k, double x)) //5 error = O(h^2)
{
    double res;
    double x;
    double h;
    int i;

    res = (func(k, a) + func(k, b)) / 2;
    *count = 2;

    h = (b - a) / 2 / n;

    for (i = 1; i < n; i++)
    {
        x = a + h * 2 * i;
        res += func(k, x);
        *count += 1;
    }

    for (i = 0; i < n; i++)
    {
        x = a + h * (2 * i + 1);
        res += 2 * func(k, x);
        *count += 1;
    }

    res *= 2 * h / 3;

    return res;
}


double trapeze_sqrt_integral(double a, double b, double n, int k, int *count, double (*func) (int k, double x)) //6
{
    double res;
    double x1;
    double x1_sqrt;
    double x2;
    double x2_sqrt;
    double y1;
    double y2;
    double h;
    int i;

    res = 0;

    h = (b - a) / n;

    x1 = a;
    x1_sqrt = sqrt(fabs(a));

    y1 = func(k, a);
    *count = 1;

    for (i = 1; i < n; i++)
    {
        x2 = a + i * h;
        x2_sqrt = sqrt(fabs(x2));

        y2 = func(k, x2);
        *count += 1;

        //res += 2 * (y1 - x1 * (y2 - y1) / h) * (x2_sqrt * sign(x2) - x1_sqrt * sign(x1))
        //+ 2 * (y2 - y1) * (fabs(x2) * x2_sqrt * sign(x2) - fabs(x1) * x1_sqrt * sign(x1)) / 3 / h;

        res += 2 * (y1 - x1 * (y2 - y1) / h) * (x2_sqrt * sign(x2) - x1_sqrt * sign(x1))
        + 2 * (y2 - y1) * (fabs(x2) * x2_sqrt - fabs(x1) * x1_sqrt) / 3 / h;

        x1 = x2;
        x1_sqrt = x2_sqrt;
        y1 = y2;
    }

    return res;
}


double simpson_sqrt_integral(double a, double b, double n, int k, int *count, double (*func) (int k, double x)) //7
{
    double res;
    double x1;
    double x1_sqrt;
    double x1_squar;
    double x2;
    double x3;
    double x3_sqrt;
    double x3_squar;
    double y1;
    double y2;
    double y3;
    double h;
    int i;

    res = 0;

    h = (b - a) / 2 / n;

    x1 = a;
    x1_sqrt = sqrt(fabs(x1));
    x1_squar = x1 * x1;

    y1 = func(k, x1);
    *count = 1;

    for (i = 0; i < n; i++)
    {
        x2 = a + h * (2 * i + 1);

        y2 = func(k, x2);
        *count += 1;

        x3 = a + h * (2 * i + 2);
        x3_sqrt = sqrt(fabs(x3));
        x3_squar = x3 * x3;

        y3 = func(k, x3);
        *count += 1;

        /*
        res += 2 * (y1 - x1 * (y2 - y1) / h + x1 * x2 * (y3 - 2 * y2 + y1) / 2 / h / h)
        * (x3_sqrt * sign(x3) - x1_sqrt * sign(x1));

        res += 2 * ((y2 - y1) / h - (x1 + x2) * (y3 - 2 * y2 + y1) / 2 / h / h)
        * (fabs(x3) * x3_sqrt * sign(x3) - fabs(x1) * x1_sqrt * sign(x1)) / 3;

        res += (y3 - 2 * y2 + y1)
        * (x3_squar * x3_sqrt * sign(x3) - x1_squar * x1_sqrt * sign(x1)) / 5 / h / h;
        */

        res += 2 * (y1 - x1 * (y2 - y1) / h + x1 * x2 * (y3 - 2 * y2 + y1) / 2 / h / h)
        * (x3_sqrt * sign(x3) - x1_sqrt * sign(x1));

        res += 2 * ((y2 - y1) / h - (x1 + x2) * (y3 - 2 * y2 + y1) / 2 / h / h)
        * (fabs(x3) * x3_sqrt - fabs(x1) * x1_sqrt) / 3;

        res += (y3 - 2 * y2 + y1)
        * (x3_squar * x3_sqrt * sign(x3) - x1_squar * x1_sqrt * sign(x1)) / 5 / h / h;


        x1 = x3;
        x1_sqrt = x3_sqrt;
        x1_squar = x3_squar;
        y1 = y3;
    }

    return res;
}


int trapeze_eps_integral(double a, double b, double eps, double *r, int k, int *count, double (*func) (int k, double x)) //8
{
    double s_n;
    double s_2n;
    double h;
    double x;
    int n;
    int i;
    int t;

    s_n = 0;
    s_2n = 0;

    n = 60;
    h = (b - a) / n;

    s_n = (func(k, a) + func(k, b)) / 2;
    *count = 2;

    for (i = 1; i < n; i++)
    {
        x = a + h * i;
        s_n += func(k, x);
        *count += 1;
    }

    s_n *= h;

    for (t = 0; t < MAXIT; t++)
    {
        s_2n = s_n / 2;

        h /= 2;

        for (i = 0; i < n; i++)
        {
            x = a + (2 * i + 1) * h;
            s_2n += func(k, x) * h;
            *count += 1;
        }

        if (fabs(s_n - s_2n) < eps)
        {
            *r = s_2n;
            return n;
        }

        s_n = s_2n;
        n *= 2;
    }

    if (t >= MAXIT)
    {
        return ERROR;
    }

    return n;
}


int simpson_eps_integral(double a, double b, double eps, double *r, int k, int *count, double (*func) (int k, double x)) //9
{
    double s_n;
    double s_2n;
    double rem;
    double h;
    double x;
    double y;
    int n;
    int i;
    int t;

    s_n = 0;
    s_2n = 0;
    rem = 0;

    n = 40;
    h = (b - a) / 2 / n;

    s_n = (func(k, a) + func(k, b)) / 2;
    *count = 2;

    for (i = 1; i < n; i++)
    {
        x = a + h * 2 * i;
        y = func(k, x);
        *count += 1;
        s_n += y;
    }

    for (i = 0; i < n; i++)
    {
        x = a + h * (2 * i + 1);
        y = func(k, x);
        *count += 1;
        rem += y;
    }

    s_n += 2 * rem;
    rem *= h;
    s_n *= 2 * h / 3;

    for (t = 0; t < MAXIT; t++)
    {
        s_2n = s_n / 2 - rem / 3;

        n *= 2;
        h = (b - a) / 2 / n;
        rem = 0;

        for (i = 0; i < n; i++)
        {
            x = a + h * (2 * i + 1);
            y = func(k, x);
            *count += 1;
            rem += y;
        }

        rem *= h;
        s_2n += 4 * rem / 3;

        if (fabs(s_n - s_2n) < eps)
        {
            *r = s_2n;
            return n;
        }

        s_n = s_2n;
    }

    if (t >= MAXIT)
    {
        return ERROR;
    }

    return n;
}


double trapeze_area_eps_integral(double a, double eps, double *r, int k, int *count, double (*func) (int k, double x)) //10
{
    double h;
    double b;
    double I;
    double S;
    int t;
    int er;

    h = 1;
    S = 0;

    for (t = 0; t < MAXIT; t++)
    {
        b = a + h;

        er = trapeze_eps_integral(a, b, eps, &I, k, count, func);

        if (er == ERROR)
        {
            return ERROR;
        }

        S += I;

        if (fabs(I) < eps)
        {
            *r = S;
            return b;
        }

        h *= 2;
        a = b;
    }

    if (t >= MAXIT)
    {
        return ERROR;
    }

    return b;
}


double simpson_area_eps_integral(double a, double eps, double *r, int k, int *count, double (*func) (int k, double x)) //11
{
    double h;
    double b;
    double I;
    double S;
    int t;
    int er;

    h = 1;
    S = 0;

    for (t = 0; t < MAXIT; t++)
    {
        b = a + h;

        er = simpson_eps_integral(a, b, eps, &I, k, count, func);

        if (er == ERROR)
        {
            return ERROR;
        }

        S += I;

        if (fabs(I) < eps)
        {
            *r = S;
            return b;
        }

        h *= 2;
        a = b;
    }

    if (t >= MAXIT)
    {
        return ERROR;
    }

    return b;
}


int curve_lengh(double a, double b, double eps, double *r, int k, int *count_x, int *count_y, double (*func_x) (double t), double (*func_y) (int k, double t)) //12
{
    double h;
    double x1;
    double x2;
    double y1;
    double y2;
    double p1;
    double p2;
    double res1;
    double res2;
    double L1;
    double L2;
    int i;
    int t;
    int n;

    L1 = 0;
    L2 = 0;

    n = 40;
    h = (b - a) / n;

    p1 = a;

    x1 = func_x(p1);
    *count_x = 1;

    y1 = func_y(k, p1);
    *count_y = 1;

    for(i = 1; i < n; i++)
    {
        p2 = a + i * h;

        x2 = func_x(p2);
        *count_x += 1;

        y2 = func_y(k, p2);
        *count_y += 1;

        if (fabs(h) > 0)
        {
            res1 = (x2 - x1) / h;
            res2 = (y2 - y1) / h;
        }
        else
        {
            return ERROR;
        }

        L1 += sqrt(res1 * res1 + res2 * res2);

        p1 = p2;
        x1 = x2;
        y1 = y2;
    }

    L1 *= h;

    for (t = 0; t < MAXIT; t++)
    {
        n *= 2;
        h = (b - a) / n;
        L2 = 0;

        p1 = a;

        x1 = func_x(p1);
        *count_x += 1;

        y1 = func_y(k, p1);
        *count_y += 1;

        for(i = 1; i < n; i++)
        {
            p2 = a + i * h;

            x2 = func_x(p2);
            *count_x += 1;

            y2 = func_y(k, p2);
            *count_y += 1;

            if (fabs(h) > 0)
            {
                res1 = (x2 - x1) / h;
                res2 = (y2 - y1) / h;
            }
            else
            {
                return ERROR;
            }

            L2 += sqrt(res1 * res1 + res2 * res2);

            p1 = p2;
            x1 = x2;
            y1 = y2;
        }

        L2 *= h;

        if (fabs(L1 - L2) < eps)
        {
            *r = L2;
            return n;
        }

        L1 = L2;
    }

    if (t >= MAXIT)
    {
        return ERROR;
    }

    return n;
}


