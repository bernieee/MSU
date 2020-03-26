#include "hw15.h"


static double formula(int n, int i, int j)//func for formula
{
    return n - (i > j ? i : j);
}


void init_matrix(double *a, int m, int n)//for formula
{
    int i;
    int j;
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            a[i * n + j] = formula(n, i, j);
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


void print_matrix(double *a, int m, int n)
{
    int i;
    int j;
    int n_max;
    int m_max;

    n_max = (n > N_MAX ? N_MAX : n);
    m_max = (m > M_MAX ? M_MAX : m);

    for (i = 0; i < m_max; i++)
    {
        for (j = 0; j < n_max; j++)
            printf(" %lf", a[i * n + j]);
        printf("\n");
    }
}


static void replace_lines(double *a, int m, int n, int i, int j)
{
    double rem;
    (void) m;

    for (int k = 0; k < n; k++)
    {
        rem = a[k + i * n];
        a[k + i * n] = a[k + j * n];
        a[k + j * n] = rem;
    }
}


static void replace_columns(double *a, int m, int n, int i, int j)
{
    int k;
    double rem;

    for (k = 0; k < m; k++)
    {
        rem = a[i + k * n];
        a[i + k * n] = a[j + k * n];
        a[j + k * n] = rem;
    }
}


static void matrix_multiplied_by_vector_to_vector(double *a, double *b, double *c, int m, int n)
{
    int i;
    int j;
    double rem;

    for (i = 0; i < m; i++)
    {
        rem = 0;
        for (j = 0; j < n; j++)
        {
            rem += a[i * n + j] * b[j];
        }
        c[i] = rem;
    }
}


static void matrix_multiplied_by_matrix_to_matrix_minus_E(double *a, double *b, double *c, int m, int n)
{
    int i;
    int j;
    int t;
    double rem;

    for (t = 0; t < m; t++)
    {
        for (i = 0; i < m; i++)
        {
            rem = 0;
            for (j = 0; j < n; j++)
            {
                rem += a[i * n + j] * b[m * j + t];
            }
            if (t == i)
                rem -= 1;
            c[t + m * i] = rem;
        }
    }
}


double max_sum_lines(double *a, int m, int n)//1
{
    double sum;
    double max_sum;
    double *pi;

    max_sum = -1;

    for (int i = 0; i < m; i++)
    {
        pi = a + i * n;
        sum = 0;
        for (int j = 0; j < n; j++)
        {
            sum += fabs(pi[j]);
        }
        max_sum = fmax(sum, max_sum);
    }

    return max_sum;
}


double max_sum_columns(double *a, int m, int n)//2
{
    double sum;
    double max_sum;
    double *pj;

    max_sum = -1;

    for (int j = 0; j < n; j++)
    {
        pj = a + j;
        sum = 0;
        for (int i = 0; i < m; i++)
        {
            sum += fabs(pj[i * n]);
        }
        max_sum = fmax(sum, max_sum);
    }

    return max_sum;
}


double first_norm(double *A, double *b, double *x, double *r, int m, int n)//3
{
    double res;

    matrix_multiplied_by_vector_to_vector(A, x, r, m, n);
    res = 0;

    for (int i = 0; i < m; i++)
    {
        r[i] -= b[i];
        res += fabs(r[i]);
    }

    return res;
}


double max_norm(double *A, double *b, double *x, double *r, int m, int n)//4
{
    double res;

    matrix_multiplied_by_vector_to_vector(A, x, r, m, n);
    res = -1;

    for (int i = 0; i < m; i++)
    {
        r[i] -= b[i];
        res = fmax(res, fabs(r[i]));
    }

    return res;
}


double max_sum_lines_1_norm(double *A, double *B, double *R, int m, int n)//5
{
    double res;

    matrix_multiplied_by_matrix_to_matrix_minus_E(A, B, R, m, n);
    res = max_sum_lines(R, m, m);

    return res;
}


double max_sum_columns_1_norm(double *A, double *B, double *R, int m, int n)//6
{
    double res;

    matrix_multiplied_by_matrix_to_matrix_minus_E(A, B, R, m, n);
    res = max_sum_columns(R, m, m);

    return res;
}


void make_b_formula_1(double *a, int m, int n)//7
{
    for (int i = n + 1; i < n * (m - 1); i++)
    {
        if (i % n == 0 || i % n == n - 1)
            continue;

        a[i] = (a[i - 1] + a[i + 1] + a[i - n] + a[i + n]) / 5;
    }
}


void make_b_formula_2(double *a, int m, int n)//8
{
    for (int i = n * (m - 1) - 1; i >= n + 1; i--)
    {
        if (i % n == 0 || i % n == n - 1)
            continue;

        a[i] = (a[i - 1] + a[i + 1] + a[i - n] + a[i + n]) / 5;
    }
}


void make_b_formula_3(double *a, int m, int n)//9
{
    for (int i = 2 * n - 2; i >= n + 1; i--)
    {
        for (int j = 0; j < m - 2; j++)
        {
            a[i + j * n] = (a[i + j * n - 1] + a[i + j * n + 1] + a[i + j * n - n] + a[i + j * n + n]) / 5;
        }
    }
}


void make_b_formula_4(double *a, int m, int n)//10
{
    for (int i = n * (m - 2) + 1; i <= n * (m - 2) + (n - 2); i++)
    {
        for (int j = 0; j < m - 2; j++)
        {
            a[i - j * n] = (a[i - j * n - 1] + a[i - j * n + 1] + a[i - j * n - n] + a[i - j * n + n]) / 5;
        }
    }
}


void replace_max_to_1(double *a, int m, int n)//11
{
    int res_i;
    int res_j;

    res_i = 0;
    res_j = 0;

    for (int i = 0; i < m; i++)
    {
        for (int j = 1; j < n; j++)
        {
            if (a[i * n + j] > a[i * n + j - 1])
            {
                res_i = i;
                res_j = j;
            }
        }
    }

    replace_lines(a, m, n, res_i, 0);
    replace_columns(a, m, n, res_j, 0);
}
