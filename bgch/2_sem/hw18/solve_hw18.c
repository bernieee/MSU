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

    //print_matrix(b, 1, n, 5);
}


/*int make_x_k(double *A_k, double A_norm, int n, int k)
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
        s_k += A_k[j + k * n] * A_k[j + k * n];
        //x_k[j - k] = A_k[j + k * n];
    }

    a_norm = sqrt(A_k[k * n + k] * A_k[k * n + k] + s_k);
    //x_k[0] = A_k[k * n + k] - a_norm;
    A_k[k * n + k] -= a_norm;
    x_k_norm = sqrt(A_k[k * n + k] * A_k[k * n + k] + s_k);

    A_k[k * n + k] = a_norm;

    if (x_k_norm > EPS * A_norm)
    {
        for (j = k; j < n; j++)
        {
            x_k[j - k] /= x_k_norm;
        }

        return SUCCESS;
    }
    else
    {
        //printf("11) %11.3e\n", x_k_norm / A_norm);
        return ERROR;
    }

    return SUCCESS;
}


int make_A_k(double *A_k, int n, int k)
{
    int i;
    int j;
    double alpha;

    for (j = k + 1; j < n; j++)// U(x_k) * A[j] -- умножение на столбец
    {
        alpha = 0;

        for (i = k; i < n; i++)
        {
            alpha += A_k[i + j * n] * A_k[i + (j - 1) * n];
        }

        alpha *= 2;

        for (i = k; i < n; i++)
        {
            A_k[i +  j * n] -= alpha * A_k[i + (j - 1) * n];
        }
    }

    return SUCCESS;
}


int make_b_k(double *A_k, double *b_k, int n, int k)
{
    int i;
    double alpha;

    alpha = 0;

    for (i = k; i < n; i++)
    {
        alpha += b_k[i] * A_k[i + (j - 1) * n];
    }

    alpha *= 2;

    for (i = k; i < n; i++)
    {
        b_k[i] = b_k[i] - alpha * A_k[i + (j - 1) * n];
    }

    return SUCCESS;
}


int gauss_up_diagonal_method(double *A, double *b, double A_norm, int n)
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
}*/


/*int reflection_method_24(double *A, double *b, double A_norm, int n)
{
    int k;
    int er;

    for (k = 0; k < n - 1; k++)
    {
        er = make_x_k(A, A_norm, n, k);

        if (er == ERROR)
        {
            return ERROR;
        }

        make_A_k(A, n, k);
        make_b_k(b, n, k);
    }

    er = gauss_up_diagonal_method(A, b, A_norm, n);

    if (er == ERROR)
    {
        return ERROR;
    }

    return SUCCESS;
}*/


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


    //printf("%10.3e\n\n", A_norm);

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

        a_norm = sqrt(A[k * n + k] * A[k * n + k] + s_k);
        A[k * n + k] -= a_norm;

        if (s_k > EPS * A_norm)
        {
            x_k_norm = sqrt(A[k * n + k] * A[k * n + k] + s_k);

            if (x_k_norm > EPS * A_norm)
            {
                for (j = k; j < n; j++)
                {
                    A[j + k * n] /= x_k_norm;
                }
            }
            else
            {
                //printf("1\n");
                return ERROR;
            }

            //print_matrix(A, n, n, 5);
            //printf("\n");
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

        //print_matrix(A, n, n, 5);
        //printf("\n");

        //b
        alpha = 0;

        for (i = k; i < n; i++)
        {
            alpha += b[i] * A[i + k * n];
        }

        alpha *= 2;

        //printf("%10.3e\n", alpha);

        for (i = k; i < n; i++)
        {
            b[i] -= alpha * A[i + k * n];
        }

        //print_matrix(b, 1, n, 5);
        //printf("\n");

        A[k + k * n] = a_norm;
    }


    if (fabs(A[n * (n - 1) + n - 1])  > EPS * A_norm)
    {
        A[n * (n - 1) + n - 1] = b[n - 1] / A[n * (n - 1) + n - 1];
    }
    else
    {
        //printf("2\n");
        return ERROR;
    }

    //printf("%10.3e\n", A[n * (n - 1) + n - 1]);

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
            //printf("3\n");
            return ERROR;
        }
    }

    for (i = 0; i < n; i++)
    {
        x[i] = A[i * n + (n - 1)];
    }


    return SUCCESS;
}

