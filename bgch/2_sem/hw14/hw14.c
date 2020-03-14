#include "hw14.h"


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
    int j;
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
        for (j = 0; j < n_max; j++)
            printf(" %lf", a[i * n + m * j]);
        printf("\n");
}


int symmetry(double *a, int n)//1
{
    int i;
    int j;
    int step;

    step = n;

    for (i = 1; i < n; i++)
    {
        for (j = 1; j < step; j++)
        {
            if (fabs(a[j] - a[j + (n - 1) * j]) > 0)
                return 0;
        }
        step--;
    }

    return 1;
}


double trace(double *a, int n)//2
{
    int i;
    double tr;

    tr = 0;

    for (i = 0; i < n; i++)
    {
        tr += a[(n + 1) * i];
    }

    return tr;
}


void transponent(double *a, int n)//3
{
    int i;
    int j;
    int step;
    double rem;

    step = n;

    for (i = 1; i < n; i++)
    {
        for (j = 1; j < step; j++)
        {
            rem = a[j];
            a[j] = a[j + (n - 1) * j];
            a[j + (n - 1) * j] = a[j];
        }
        step--;
    }
}


void matrix_plus_transponent(double *a, int n)//4
{
    int i;
    int j;
    int step;
    double res;

    step = n;

    for (i = 1; i < n; i++)
    {
        for (j = 1; j < step; j++)
        {
            res = (a[j] + a[j + (n - 1) * j]) / 2;
            a[i] = res;
            a[j + (n - 1) * j] = res;
        }
        step--;
    }
}


void matrix_minus_transponent(double *a, int n)//5
{
    int i;
    int j;
    int step;
    double res;

    step = n;

    for (i = 1; i < n; i++)
    {
        for (j = 1; j < step; j++)
        {
            res = (a[j] - a[j + (n - 1) * j]) / 2;
            a[i] = res;
            a[j + (n - 1) * j] = res;
        }
        step--;
    }
}


void replace_lines(double *a, int m, int n, int i, int j)//6
{
    int k;
    double rem;

    for (k = 0; k < n; k++)
    {
        rem = a[k + (i - 1) * n];
        a[k + (i - 1) * n] = a[k + (j - 1) * n];
        a[k + (j - 1) * n] = rem;
    }
}


void replace_columns(double *a, int m, int n, int i, int j)//7
{
    int k;
    double rem;

    for (k = 0; k < m; k++)
    {
        rem = a[(i - 1) + k * n];
        a[(i - 1) + k * n] = a[(j - 1) + k * n];
        a[(j - 1) + k * n] = rem;
    }
}


void sum_lines_multiplied_by_b(double *a, double b, int m, int n, int i, int j)//8
{
    int k;
    double rem;

    for (k = 0; k < n; k++)
    {
        rem = a[k + (j - 1) * n] + a[k + (i - 1) * n] * b;
        a[k + (j - 1) * n] = rem;
    }
}


void matrix_multipied_by_vector_to_vector(double *a, double *b, double *c, int m, int n)//9
{
    int i;
    int j;
    double rem;

    rem = 0;

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            rem += a[i * n + j] * b[j];
        }
        c[i] = rem;
    }
}


void matrix_multipied_by_matrix_to_matrix(double *a, double *b, double *c, int m, int n, int k)//10
{
    int i;
    int j;
    int t;
    double rem;

    for (t = 0; t < k; t++)
    {
        for (i = 0; i < m; i++)
        {
            for (j = 0; j < n; j++)
            {
                rem += a[i * n + j] * b[j];
            }
            c[t + k * i] = rem;
        }
    }
}

