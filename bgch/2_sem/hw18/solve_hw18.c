#include "solve_hw18.h"


double L1_matrix_norm(double *A, int n)
{
    int i;
    int j;
    double sum;
    double max_sum;
    double *pj;

    max_sum = -1;

    for (j = 0; j < n; j++)
    {
        pj = A + j;
        sum = 0;
        for (i = 0; i < n; i++)
        {
            sum += fabs(pj[i * n]);
        }
        max_sum = fmax(sum, max_sum);
    }

    return max_sum;
}


double residual_1(double *A, double *b, double *x, double A_norm, int n)//L1 norm
{
    int i;
    int j;
    double rem;
    double res1;
    double res2;

    res1 = 0;
    res2 = 0;

    for (i = 0; i < n; i++)
    {
        rem = 0;

        for (j = 0; j < n; j++)
        {
            rem += A[i * n + j] * x[j];
        }

        res1 += fabs(rem - b[i]);
        res2 += fabs(b[i]);
    }

    if (res2 > EPS * A_norm)
    {
        res1 /= res2;
        return res1;
    }
    else
    {
        return ERROR;
    }
}


double residual_2(double *x, int n)//L1 norm, x - x0, x0 = (101010...)
{
    int i;
    double res;

    res = 0;

    for (i = 0; i < n; i++)
    {
        res += fabs(x[i] - ((i + 1) % 2));
    }

    return res;
}


void make_b(double *A, double *b, int n)
{
    int i;
    int j;
    double sum;
    double *pi;

    for (i = 0; i < n; i++)
    {
        pi = A + i * n;
        sum = 0;

        for (j = 0; j < (n + 1) / 2; j++)
        {
            sum += pi[2 * j];
        }

        b[i] = sum;
    }
}


int make_x_k(double *A_k, double *x_k, double A_norm, int n, int k)
{
    int j;
    double s_k;
    double a_norm;
    double x_k_norm;

    s_k = 0;
    a_norm = 0;
    x_k_norm = 0;

    for (j = k + 1; j < n; j++)
    {
        s_k += A_k[j * n + k] * A_k[j * n + k];
        x_k[j - k] = A_k[j * n + k];
    }

    a_norm = sqrt(A_k[k * n + k] * A_k[k * n + k] + s_k);
    x_k[0] = A_k[k * n + k] - a_norm;
    x_k_norm = sqrt(x_k[0] * x_k[0] + s_k);

    if (x_k_norm > EPS * A_norm)
    {
        for (j = k; j < n; j++)
        {
            x_k[j - k] /= x_k_norm;
        }

        A_k[k * n + k] = a_norm;

        return SUCCESS;
    }
    else
    {
        return ERROR;
    }
}


int make_A_k(double *A_k, double *x_k, int n, int k)
{
    int i;
    int j;
    double alpha;

    for (j = k + 1; j < n; j++)// U(x_k) * A[j] -- умножение на столбец
    {
        alpha = 0;

        for (i = k; i < n; i++)
        {
            alpha += A_k[i * n + j] * x_k[i - k];
        }

        alpha *= 2;

        for (i = k; i < n; i++)
        {
            A_k[i * n + j] -= alpha * x_k[i - k];
        }
    }

    return SUCCESS;
}


int make_b_k(double *b_k, double *x_k, int n, int k)
{
    int i;
    double alpha;

    alpha = 0;

    for (i = k; i < n; i++)
    {
        alpha += b_k[i] * x_k[i - k];
    }

    alpha *= 2;

    for (i = k; i < n; i++)
    {
        b_k[i] = b_k[i] - alpha * x_k[i - k];
    }

    return SUCCESS;
}


int gauss_up_diagonal_method(double *A, double *b, double *x, double A_norm, int n)
{
    int i;
    int j;

    if (fabs(A[n * (n - 1) + n - 1]) > EPS * A_norm)
    {
        x[n - 1] = b[n - 1] / A[n * (n - 1) + n - 1];
    }
    else
    {
        return ERROR;
    }

    for (i = n - 2; i >= 0; i--)
    {
        x[i] = b[i];

        for (j = n - 2; j >= i; j--)
        {
            x[i] -= x[j + 1] * A[i * n + j + 1];
        }

        if (fabs(A[i * n + i]) > EPS * A_norm)
        {
            x[i] /= A[i * n + i];
        }
        else
        {
            return ERROR;
        }
    }

    return SUCCESS;
}


int reflection_method_24(double *A, double *b, double *x, double A_norm, int n)
{
    int k;
    int er;
    double t;
    double res;

    res = 0;

    for (k = 0; k < n - 1; k++)
    {
        er = make_x_k(A, x, A_norm, n, k);

        if (er == ERROR)
        {
            return ERROR;
        }

        t = clock();
        make_A_k(A, x, n, k);
        t = clock() - t;
        res += t;
        make_b_k(b, x, n, k);
    }

    er = gauss_up_diagonal_method(A, b, x, A_norm, n);

    printf("%.5lf\n", res / CLOCKS_PER_SEC);

    if (er == ERROR)
    {
        return ERROR;
    }

    return SUCCESS;
}

