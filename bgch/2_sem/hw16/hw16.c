#include "hw16.h"


static double formula(int m, int n, int i, int j)//func for formula
{
    return fmax(m, n) - fmax(i, j);
}


void init_matrix(double *a, int m, int n)//for formula
{
    int i;
    int j;
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            a[i * n + j] = formula(m, n, i, j);
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
            printf("%10lf", a[i * n + j]);
        printf("\n");
    }
}


static int min_sum_lines(double *a, int m, int n)
{
    int i;
    int j;
    int index;
    double sum;
    double min_sum;
    double *pi;

    index = 0;
    min_sum = -1;

    for (i = 0; i < m; i++)
    {
        pi = a + i * n;
        sum = 0;

        for (j = 0; j < n; j++)
        {
            sum += fabs(pi[j]);
        }

        if (i == 0)
            min_sum = sum;
        else if (sum < min_sum)
        {
            min_sum = sum;
            index = i;
        }
    }

    return index;
}


static int min_sum_columns(double *a, int m, int n)
{
    int i;
    int j;
    int index;
    double sum;
    double min_sum;
    double *pj;

    index = 0;
    min_sum = -1;

    for (j = 0; j < n; j++)
    {
        pj = a + j;
        sum = 0;

        for (i = 0; i < m; i++)
        {
            sum += fabs(pj[i * n]);
        }

        if (j == 0)
            min_sum = sum;
        else if (sum < min_sum)
        {
            min_sum = sum;
            index = j;
        }
    }

    return index;
}


static int max_sum_columns(double *a, int m, int n)
{
    int i;
    int j;
    int index;
    double sum;
    double max_sum;
    double *pj;

    index = 0;
    max_sum = -1;

    for (j = 0; j < n; j++)
    {
        pj = a + j;
        sum = 0;

        for (i = 0; i < m; i++)
        {
            if (i != j)
                sum += fabs(pj[i * n]);
        }

        if (sum > max_sum)
        {
            max_sum = sum;
            index = j;
        }
    }

    return index;
}


static int max_sum_columns_minus_main_elem(double *a, int m, int n)
{
    int i;
    int j;
    int index;
    double rem;
    double sum;
    double max_sum;
    double *pj;

    index = 0;
    max_sum = -1;

    for (j = 0; j < n; j++)
    {
        pj = a + j;
        rem = pj[j * n];
        sum = 0;

        for (i = 0; i < m; i++)
        {
            sum += fabs(pj[i * n] - rem);
        }

        if (sum > max_sum)
        {
            max_sum = fmax(sum, max_sum);
            index = j;
        }
    }

    return index;
}


static int min_dispersion_line(double *a, int m, int n)
{
    int i;
    int j;
    int index;
    double sum_q;
    double sum;
    double d;
    double min_d;
    double *pi;

    index = 0;
    min_d = -1;

    for (i = 0; i < m; i++)
    {
        pi = a + i * n;
        sum = 0;
        sum_q = 0;
        d = 0;

        for (j = 0; j < n; j++)
        {
            sum += pi[j];
            sum_q += pi[j] * pi[j];
        }

        d = sum_q - sum * sum / m;

        if (i == 0)
            min_d = d;
        else if (d < min_d)
        {
            min_d = fmin(d, min_d);
            index = i;
        }
        printf("%d  %d\n", index, i);
    }

    return index;
}



static int min_dispersion_column(double *a, int m, int n)
{
    int i;
    int j;
    int index;
    double sum_q;
    double sum;
    double d;
    double min_d;
    double *pj;

    index = 0;
    min_d = -1;

    for (j = 0; j < n; j++)
    {
        pj = a + j;
        sum = 0;
        sum_q = 0;
        d = 0;

        for (i = 0; i < m; i++)
        {
            sum += pj[i * n];
            sum_q += pj[i * n] * pj[i * n];
        }

        d = sum_q - sum * sum / m;

        if (j == 0)
            min_d = d;
        else if (d < min_d)
        {
            min_d = fmin(d, min_d);
            index = j;
        }
    }

    return index;
}


static void find_min_elem(double *a, int m, int n, int *res_i, int *res_j)
{
    int i;
    int j;
    double res;

    res = fabs(a[0]);

    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (fabs(a[i * n + j]) < res)
            {
                res = fabs(a[i * n + j]);
                *res_i = i;
                *res_j = j;
            }
        }
    }
}


static void max_sum_line_and_column(double *a, int m, int n, int *res_i, int *res_j)
{
    int i;
    int j;
    int k;
    double sum_i;
    double sum_j;
    double sum;
    double max_sum;
    double *pi;
    double *pj;

    max_sum = -1;

    for (i = 0; i < m; i++)
    {
        pi = a + i * n;
        sum_i = 0;

        for (j = 0; j < n; j++)
        {
            sum_i += fabs(pi[j]);
        }

        for (j = 0; j < n; j++)
        {
            pj = a + j;
            sum_j = 0;

            for (k = 0; k < m; k++)
            {
                sum_j += fabs(pj[k * n]);
            }

            sum = sum_i + sum_j - 2 * fabs(pi[j]);

            if (sum > max_sum)
            {
                max_sum = fmax(sum, max_sum);
                *res_i = i;
                *res_j = j;
            }
        }
    }
}


static void max_sum_line_and_column_minus_intersection(double *a, int m, int n, int *res_i, int *res_j)
{
    int i;
    int j;
    int k;
    int l;
    double rem;
    double sum_i;
    double sum_j;
    double sum;
    double max_sum;
    double *pi;
    double *pj;

    max_sum = -1;

    for (i = 0; i < m; i++)
    {
        pi = a + i * n;

        for (j = 0; j < n; j++)
        {
            pj = a + j;
            rem = pi[j];
            sum_i = 0;
            sum_j = 0;

            for (k = 0; k < n; k++)
            {
                sum_i += fabs(pi[k] - rem);
            }

            for (l = 0; l < m; l++)
            {
                sum_j += fabs(pj[l * n] - rem);
            }

            sum = sum_i + sum_j;
            if (sum > max_sum)
            {
                max_sum = fmax(sum, max_sum);
                *res_i = i;
                *res_j = j;
            }
        }
    }
}


//if delete only column : res_i == -1
static void delete_(double *a, int m, int n, int res_i, int res_j)
{
    int i;
    int j;
    int move;
    double *pi;

    move = 0;

    for (i = 0; i < m; i++)
    {
        pi = a + i * n;

        if (i == res_i)
        {
            move += n;
            continue;
        }

        for (j = 0; j < n; j++)
        {
            if (j == res_j)
            {
                move++;
                continue;
            }

            pi[j - move] = pi[j];
        }
    }
}


void delete_column_with_min_elem(double *a, int m, int n)//1
{
    int res_i;
    int res_j;

    res_i = 0;
    res_j = 0;

    find_min_elem(a, m, n, &res_i, &res_j);
    delete_(a, m, n, -1, res_j);
}


void delete_column_and_line_with_min_elem(double *a, int m, int n)//2
{
    int res_i;
    int res_j;

    res_i = 0;
    res_j = 0;

    find_min_elem(a, m, n, &res_i, &res_j);
    delete_(a, m, n, res_i, res_j);
}


void delete_column_with_min_sum(double *a, int m, int n)//3
{
    int res_j;

    res_j = min_sum_columns(a, m, n);
    delete_(a, m, n, -1, res_j);
}


void delete_column_and_line_with_min_sum(double *a, int m, int n)//4
{
    int res_i;
    int res_j;

    res_i = min_sum_lines(a, m, n);
    res_j = min_sum_columns(a, m, n);
    delete_(a, m, n, res_i, res_j);
}


void delete_column_with_max_sum(double *a, int m, int n)//5
{
    int res_j;

    res_j = max_sum_columns(a, m, n);
    delete_(a, m, n, -1, res_j);
}


void delete_column_with_max_sum_minus_main_elem(double *a, int m, int n)//6
{
    int res_j;

    res_j = max_sum_columns_minus_main_elem(a, m, n);
    delete_(a, m, n, -1, res_j);
}


void delete_column_with_min_dispersion(double *a, int m, int n)//7
{
    int res_j;

    res_j = min_dispersion_column(a, m, n);
    delete_(a, m, n, -1, res_j);
}


void delete_column_and_line_with_max_sum(double *a, int m, int n)//8
{
    int res_i;
    int res_j;

    res_i = 0;
    res_j = 0;

    max_sum_line_and_column(a, m, n, &res_i, &res_j);
    delete_(a, m, n, res_i, res_j);
}


void delete_column_and_line_with_max_sum_minus_intersection(double *a, int m, int n)//9
{
    int res_i;
    int res_j;

    res_i = 0;
    res_j = 0;

    max_sum_line_and_column_minus_intersection(a, m, n, &res_i, &res_j);
    delete_(a, m, n, res_i, res_j);
}


void delete_column_and_line_with_min_dispersion(double *a, int m, int n)//10
{
    int res_i;
    int res_j;

    res_i = min_dispersion_line(a, m, n);
    res_j = min_dispersion_column(a, m, n);
    delete_(a, m, n, res_i, res_j);
}
