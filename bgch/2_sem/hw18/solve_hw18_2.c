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
            rem += A[j * n + i] * x[j];
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
    //double *pi;

    for (j = 0; j < n; j++)
    {
        //pi = A + i;
        sum = 0;

        for (i = 0; i < (n + 1) / 2; i++)
        {
            //sum += pi[2 * j];
            sum += A[2 * i * n + j];
        }

        b[i] = sum;
    }

    print_matrix(b, n, 1, n);
}


static double sign(double x)
{
    if (x > EPS)
        return 1;
    else
        return -1;
}


int reflection_method_24(double *A, double *b, double *x, double A_norm, int n)
{
    int k;
    int er;
    int i;
    int j;
    double s_k;
    double a_norm;
    double x_k_norm;
    double alpha;

    //printf("%10.3e\n", A_norm);

    for (k = 0; k < n - 1; k++)
    {
        s_k = 0;
        a_norm = 0;
        x_k_norm = 0;

        for (j = k + 1; j < n; j++)
        {
            s_k += A[j + k * n] * A[j + k * n];
            x[j - k] = A[j + k * n];
        }

        a_norm = sqrt(A[k * n + k] * A[k * n + k] + s_k);

        /*if (a_norm > EPS * A_norm)
        {
            for (j = k; j < n; j++)
            {
                A[j * n + k] /= a_norm;
            }
        }
        else
        {
            return ERROR;
        }*/

        /*for (j = k + 1; j < n; j++)
        {
            x[j - k] = A[j * n + k];
        }*/

        x[0] = A[k * n + k] - a_norm;
        //x[0] = A[k * n + k] + sign(A[k * n + k]);
        x_k_norm = sqrt(x[0] * x[0] + s_k);

        A[k * n + k] = a_norm;

        if (x_k_norm > EPS * A_norm)
        {
            for (j = k; j < n; j++)
            {
                x[j - k] /= x_k_norm;
            }
        }
        else
        {
            return ERROR;
        }

        //make_A_k(A, x, n, k);
        //make_b_k(b, x, n, k);


        for (j = k + 1; j < n; j++)// U(x_k) * A[j] -- умножение на столбец
        {
            alpha = 0;

            for (i = k; i < n; i++)
            {
                alpha += A[i + j * n] * x[i - k];
            }

            alpha *= 2;

            for (i = k; i < n; i++)
            {
                A[i + j * n] -= alpha * x[i - k];
            }
        }

        alpha = 0;

        for (i = k; i < n; i++)
        {
            alpha += b[i] * x[i - k];
        }

        alpha *= 2;

        for (i = k; i < n; i++)
        {
            b[i] -= alpha * x[i - k];
        }

    }

    //er = gauss_up_diagonal_method(A, b, x, A_norm, n);

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
            x[i] -= x[j + 1] * A[i + (j + 1) * n];
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

