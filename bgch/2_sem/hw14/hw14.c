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


int symmetry(double *a, int n)//1
{
    int i;
    int j;
    int step;

    step = n;

    for (i = 0; i < n - 1; i++)
    {
        double *a_rem = a + i * (n + 1);
        for (j = 1; j < step; j++)
        {
            //if (fabs(a[j + (n + 1) * i] - a[j + (n + 1) * i + (n - 1) * j]) > 0)
            if (fabs(a_rem[j] - a_rem[n * j]) > 0)
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

    for (i = 0; i < n - 1; i++)
    {
        for (j = 1; j < step; j++)
        {
            rem = a[j + (n + 1) * i];
            a[j + (n + 1) * i] = a[j + (n + 1) * i + (n - 1) * j];
            a[j + (n + 1) * i + (n - 1) * j] = rem;
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

    for (i = 0; i < n - 1; i++)
    {
        for (j = 1; j < step; j++)
        {
            res = (a[j + (n + 1) * i] + a[j + (n + 1) * i + (n - 1) * j]) / 2;
            a[j + (n + 1) * i] = res;
            a[j + (n + 1) * i + (n - 1) * j] = res;
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

    for (i = 0; i < n - 1; i++)
    {
        a[(n + 1) * i] = 0;
        for (j = 1; j < step; j++)
        {
            res = (a[j + (n + 1) * i] - a[j + (n + 1) * i + (n - 1) * j]) / 2;
            a[j + (n + 1) * i] = res;
            if (fabs(res) > 0)
                a[j + (n + 1) * i + (n - 1) * j] = -res;
            else
                a[j + (n + 1) * i + (n - 1) * j] = 0;
        }
        step--;
    }
    a[(n + 1) * i] = 0;
}


void replace_lines(double *a, int m, int n, int i, int j)//6
{
    (void) m;
    int k;
    double rem;

    for (k = 0; k < n; k++)
    {
        rem = a[k + i * n];
        a[k + i * n] = a[k + j * n];
        a[k + j * n] = rem;
    }
}


void replace_columns(double *a, int m, int n, int i, int j)//7
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


void sum_lines_multiplied_by_b(double *a, double b, int m, int n, int i, int j)//8
{
    (void) m;
    int k;
    double rem;

    for (k = 0; k < n; k++)
    {
        rem = a[k + j * n] + a[k + i * n] * b;
        a[k + j * n] = rem;
    }
}

void matrix_multiplied_by_vector_to_vector(double *a, double *b, double *c, int m, int n)//9
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


void matrix_multiplied_by_matrix_to_matrix(double *a, double *b, double *c, int m, int n, int k)//10
{
    int i;
    int j;
    int t;
    double rem;

    for (t = 0; t < k; t++)
    {
        for (i = 0; i < m; i++)
        {
            rem = 0;
            for (j = 0; j < n; j++)
            {
                rem += a[i * n + j] * b[k * j + t];
            }
            c[t + k * i] = rem;
        }
    }
}
