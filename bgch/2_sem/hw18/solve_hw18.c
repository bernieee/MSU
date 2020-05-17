#include "solve_hw18.h"
#include "io_hw18.h"


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
        pj = A + j * n;
        sum = 0;
        for (i = 0; i < n; i++)
        {
            sum += fabs(pj[i]);
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
            rem += A[i + j * n] * x[j];
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
        pi = A + i;
        sum = 0;

        for (j = 0; j < (n + 1) / 2; j++)
        {
            sum += pi[2 * j * n];
        }

        b[i] = sum;
    }
}


static double sign(double x)
{
    if (x < 0)
        return -1;
    else
        return 1;
}


int reflection_method_24(double *A, double *b, double *x, double A_norm, int n)
{
    double s_k;
    double a_norm;
    double x_k_norm;
    double alpha;

    int i;
    int j;
    int k;
    int er;

    for (k = 0; k < n - 1; k++)
    {
        //x
        s_k = 0;
        a_norm = 0;
        x_k_norm = 0;

        for (j = k + 1; j < n; j++)
        {
            s_k += A[j + k * n] * A[j + k * n];
        }

        //a_norm = (-1) * sign(A[k * n + k]) * sqrt(A[k * n + k] * A[k * n + k] + s_k);
        a_norm = sqrt(A[k * n + k] * A[k * n + k] + s_k);
        A[k * n + k] -= a_norm;

        x_k_norm = sqrt(A[k * n + k] * A[k * n + k] + s_k);

        if (fabs(s_k) > EPS * A_norm)
        //if (fabs(x_k_norm) > EPS * A_norm)
        {
            for (j = k; j < n; j++)
            {
                A[j + k * n] /= x_k_norm;
            }
        }

        //A
        for (j = k + 1; j < n; j++)// U(x_k) * A[j] -- умножение на столбец
        {
            alpha = 0;

            for (i = k; i < n; i++)
            {
                alpha += A[i + j * n] * A[i + k * n];
            }

            alpha *= 2;

            for (i = k; i < n; i++)
            {
                A[i + j * n] -= alpha * A[i + k * n];
            }
        }

        //b
        alpha = 0;

        for (i = k; i < n; i++)
        {
            alpha += b[i] * A[i + k * n];
        }

        alpha *= 2;

        for (i = k; i < n; i++)
        {
            b[i] -= alpha * A[i + k * n];
        }

        A[k + k * n] = a_norm;
    }

    if (fabs(A[n * (n - 1) + n - 1]) > EPS * A_norm)
    {
        A[n * (n - 1) + n - 1] = b[n - 1] / A[n * (n - 1) + n - 1];
    }
    else
    {
        return ERROR;
    }

    for (i = n - 2; i >= 0; i--)
    {
        A[i * n + (n - 1)] = b[i];

        for (j = n - 1; j > i; j--)
        {
            A[i * n + (n - 1)] -= A[j * n + (n - 1)] * A[j * n + i];
        }

        if (fabs(A[i * n + i]) > EPS * A_norm)
        {
            A[i * n + (n - 1)] /= A[i * n + i];
        }
        else
        {
            return ERROR;
        }
    }

    for (i = 0; i < n; i++)
    {
        x[i] = A[i * n + (n - 1)];
    }

    return SUCCESS;
}

