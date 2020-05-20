#include "io_hw18.h"

static double formula(int n, int i, int j, int k)//func for formula
{
    if (k == 1)
    {
        return (n - fmax(i, j) + 1);
    }

    if (k == 2)
    {
        return fmax(i, j);
    }

    if (k == 3)
    {
        return abs(i - j);
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
    {
        for (j = 0; j < n; j++)
        {
            a[i * n + j] = formula(n, i + 1, j + 1, k);
        }
    }
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
        {
            printf("%11.3e", a[i * n + j]);
        }
        printf("\n");
    }
}

