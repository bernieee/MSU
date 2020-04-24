#include "hw18.h"


static double formula(int n, int i, int j, int k)//func for formula
{
    if (k == 1)
    {
        return n - fmax(i, j) + 1;
    }

    if (k == 2)
    {
        return fmax(i, j);
    }

    if (k == 3)
    {
        return fabs(i - j);
    }

    if (k == 4)
    {
        return 1.0 / (i + j - 1.0);
    }

    return -1;
}


void init_matrix(double *a, int m, int n, int k)//for formula
{
    int i;
    int j;
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            a[i * n + j] = formula(n, i + 1, j + 1, k);
}


int read_matrix(double *a, int m, int n, const char *fname)
{
    FILE *f;
    int i;
    int len;

    len = n * m;

    if (!(f = fopen(fname, "r")))
        return ERROR_OPEN;

    for (i = 0; i < len; i++)
        if (fscanf(f, "%lf", a + i) != 1)
        {
            fclose(f);
            return ERROR_READ;
        }

    fclose(f);
    return SUCCESS;
}


void print_matrix(double *a, int m, int n, int max_len)
{
    int i;
    int j;
    int n_max;
    int m_max;

    n_max = (n > max_len ? max_len : n);
    m_max = (m > max_len ? max_len : m);

    for (i = 0; i < m_max; i++)
    {
        for (j = 0; j < n_max; j++)
            printf("%11.3e", a[i * n + j]);
        printf("\n");
    }
}


double residual_1(double *A, double *b, double *x, int n)//L1 norm
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

    if (res2 > EPS)
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


int make_x_k(double *A_k, double *x_k, int n, int k)
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
        s_k += A_k[j * n] * A_k[j * n];
        x_k[j - k] = A_k[j * n];
    }

    a_norm = sqrt(A_k[k * n + k] * A_k[k * n + k] + s_k);
    x_k[0] = A_k[k * n + k] - a_norm;
    x_k_norm = sqrt(x_k[0] * x_k[0] + s_k);

    printf("a_norm = %e\n", a_norm);
    printf("x_k_norm = %e\n", x_k_norm);

    for (j = k; j < n; j++)
    {
        printf("%e ", x_k[j - k]);
    }
    printf("\n");


    if (x_k_norm > EPS)
    {
        for (j = k; j < n; j++)
        {
            x_k[j - k] /= x_k_norm;
        }

        for (j = k; j < n; j++)
        {
            printf("%e ", x_k[j - k]);
        }
        printf("\n");

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

   // A_k[k * n + k] = a_norm;

    for (j = k + 1; j < n; j++)// U(x_k) * A[j] -- умножение на столбец
    {
        alpha = 0;

        for (i = k; i < n; i++)
        {
            alpha += A_k[i * n + j] * x_k[i - k];
        }

        alpha *= 2;

        printf("alpha_A = %e\n", alpha);

        for (i = k; i < n; i++)
        {
            A_k[i * n + j] = A_k[i * n + j] - alpha * x_k[i - k];
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

    printf("alpha_b = %e\n", alpha);

    for (i = k; i < n; i++)
    {
        b_k[i] = b_k[i] - alpha * x_k[i - k];
    }

    return SUCCESS;
}


int gauss_up_diagonal_method(double *A, double *b, double *x, int n)
{
    int i;
    int j;

    if (fabs(A[n * (n - 1) + n - 1]) > EPS)
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
            x[i] -= x[j - 1] * A[i * n + j - 1];
        }

        if (fabs(A[i * n + i]) > EPS)
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


int reflection_method_24(double *A, double *b, double *x, int n)
{
    int k;
    int er;

    for (k = 0; k < n - 1; k++)
    {
        er = make_x_k(A, x, n, k);

        if (er == ERROR)
        {
            return ERROR;
        }

        make_A_k(A, x, n, k);
        make_b_k(b, x, n, k);

        print_matrix(A, n, n, n);
        printf("\n");
        print_matrix(b, n, 1, n);
        printf("\n");
    }

    /*er = make_x_k(A, x, n, k);
    //A[(n - 1) * n + (n - 1)] = diagonal_elem;
    if (er == ERROR)
    {
        return ERROR;
    }*/

    er = gauss_up_diagonal_method(A, b, x, n);

    if (er == ERROR)
    {
        return ERROR;
    }

    return SUCCESS;
}

