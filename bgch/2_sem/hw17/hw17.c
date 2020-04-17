#include "hw17.h"


static double formula(int n, int i, int j)//func for formula
{
    return n - fmax(i, j);
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


static void matrix_multiplied_by_matrix_to_matrix(double *a, double *b, double *c, int m, int n, int k)
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


static double residual_1(double *A, double *b, double *x, int n)
{
    int i;
    int j;
    double rem;
    double res;

    res = 0;

    for (i = 0; i < n; i++)
    {
        rem = 0;

        for (j = 0; j < n; j++)
        {
            rem += A[i * n + j] * x[j];
        }

        res += fabs(rem - b[i]);
    }

    return res;
}


static double residual_2(double *x, int n)
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


static void make_b(double *A, double *b, int n)
{
    int i;
    int j;
    double sum;
    double *pi;

    sum = 0;

    for (i = 0; i < n; i++)
    {
        pi = A + i * n;

        for (j = 0; j < (n + 1) / 2; j++)
        {
            sum += pi[2 * j];
        }

        b[i] = sum;
    }
}


/*static void make_b(double *A, double *b, int n)
{
    int i;
    double *x;

    x = malloc(n * sizeof(double));

    for (i = 0; i < n; i++)
    {
        x[i] = (i + 1) % 2;
    }

    matrix_multiplied_by_vector_to_vector(A, x, b, n, n);
}


static double scalar_product(double *x, double *y, int n)
{
    int i;
    double res;

    res = 0;

    for (i = 0; i < n; i++)
    {
        res += x[i] * y[i];
    }

    return res;
}


static void multiplication_vector(double *x, double t, int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        x[i] = x[i] * t;
    }
}

static void sum_vectors(double *x, double *y, double *z, int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        z[i] = x[i] + y[i];
    }
}


static void difference_vectors(double *x, double *y, double *z, int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        z[i] = x[i] - y[i];
    }
}*/


double lambda_sequence(double *A, double *x0, double *x, int n, int m)//1
{
    int i;
    double res;

    for (i = 0; i < m; i++)
    {
        matrix_multiplied_by_vector_to_vector(A, x0, x0, n, n);//here is xm
    }

    matrix_multiplied_by_vector_to_vector(A, x0, x, n, n);

    res = scalar_product(x, x0, n) / scalar_product(x0, x0, n);

    for (i = 0; i < n; i++)
    {
        x[i] = x0[i];
    }

    return res;
}


void sequence_2(double *A, double *x0, double *b, double *x, int n, int m, double t, double *error1, double *error2)//2
{
    int i;
    int j;
    int k;
    double rem;

    make_b(A, b, n);

    /*for (i = 0; i < m; i++)
    {
        matrix_multiplied_by_vector_to_vector(A, x0, x, n, n);
        difference_vectors(b, x, x, n);
        multiplication_vector(x, t, n);
        sum_vectors(x, x0, x0, n);
    }*/


    for (k = 0; k < m; k++)
    {
        for (i = 0; i < n; i++)
        {
            rem = 0;

            for (j = 0; j < n; j++)
            {
                rem += A[i * n + j] * x0[j];
            }

            x0[i] = (b[i] - rem) * t + x0[i];
        }
    }

    for (i = 0; i < n; i++)
    {
        x[i] = x0[i];
    }

    *error1 = residual_1(A, b, x, n);
    *error2 = residual_2(x, n);
}




void sequence_3(double *A, double *x0, double *b, double *x, double *r, int n, int m, double *error1, double *error2)//3
{
    int i;
    int j;
    int k;
    double sum;
    double rem1;
    double rem2;

    make_b(A, b, n);

    for (i = 0; i < n; i++)
    {
        sum = 0;

        for (j = 0; j < n; j++)
        {
            sum += A[i * n + j] * x0[j];
        }

        r[i] = sum - b[i];
    }

    for (k = 0; k < m; k++)
    {
        rem1 = 0;
        rem2 = 0;

        for (i = 0; i < n; i++)
        {
            sum = 0;
            for (j = 0; j < n; j++)
            {
                sum += A[i * n + j] * r[j];
            }
            rem1 += r[i] * r[i];
            rem2 += r[i] * sum;
            x[i] = sum;
        }

        if (fabs(rem1) > 0)
        {
            for (i = 0; i < n; i++)
            {
                x0[i] -= r[i] * rem2 / rem1;
            }
        }
        else
        {
            return ERROR;
        }

        for (i = 0; i < n; i++)
        {
            x[i] = r[i] - x[i] * rem2 / rem1;
        }

        r = x;
    }

    *error1 = residual_1(A, b, x, n);
    *error2 = residual_2(x, n);
}


void sequence_4(double *A, double *x0, double *b, double *x, double *r, int n, int m, double *error1, double *error2)//4
{
    int i;
    int j;
    int k;
    double sum;
    double rem1;
    double rem2;

    make_b(A, b, n);

    for (i = 0; i < n; i++)
    {
        sum = 0;

        for (j = 0; j < n; j++)
        {
            sum += A[i * n + j] * x0[j];
        }

        r[i] = sum - b[i];
    }

    for (k = 0; k < m; k++)
    {
        rem1 = 0;
        rem2 = 0;

        for (i = 0; i < n; i++)
        {
            sum = 0;
            for (j = 0; j < n; j++)
            {
                sum += A[i * n + j] * r[j];
            }
            rem1 += r[i] * sum;
            rem2 += sum * sum;
            x[i] = sum;
        }

        if (fabs(rem1) > 0)
        {
            for (i = 0; i < n; i++)
            {
                x0[i] -= r[i] * rem2 / rem1;
            }
        }
        else
        {
            return ERROR;
        }

        for (i = 0; i < n; k++)
        {
            x[i] = r[i] - x[i] * rem2 / rem1;
        }

        r = x;
    }

    *error1 = residual_1(A, b, x, n);
    *error2 = residual_2(x, n);
}


void sequence_5(double *A, double *x0, double *b, double *x, double *r, int n, int m, double *error1, double *error2)//5
{
    int i;
    int j;
    int k;
    double sum1;
    double sum2;
    double rem1;
    double rem2;

    make_b(A, b, n);

    for (i = 0; i < n; i++)
    {
        rem1 = 0;

        for (j = 0; j < n; j++)
        {
            rem1 += A[i * n + j] * x0[j];
        }

        r[i] = rem1 - b[i];
    }

    for (k = 0; k < m; k++)
    {
        rem1 = 0;
        rem2 = 0;

        for (i = 0; i < n; i++)
        {
            sum1 = 0;
            sum2 = 0;
            for (j = 0; j < n; j++)
            {
                sum1 += A[i * n + j] * r[j];
                sum2 += A[i * n + j] * r[j] / A[j * n + j];
            }
            rem1 += r[i] * r[i] / A[i * n + i];
            rem2 += sum2 * r[i] / A[i * n + i];
            x[i] = sum1;
        }

        if (fabs(rem1) > 0)
        {
            for (i = 0; i < n; i++)
            {
                x0[i] -= r[i] * rem2 / rem1;
            }
        }
        else
        {
            return ERROR;
        }

        for (i = 0; i < n; i++)
        {
            x[i] = r[i] - x[i] * rem2 / rem1;
        }

        r = x;
    }

    *error1 = residual_1(A, b, x, n);
    *error2 = residual_2(x, n);
}


void sequence_6(double *A, double *x0, double *b, double *x, double *r, int n, int m, double *error1, double *error2)//6
{
    int i;
    int j;
    int k;
    double sum1;
    double sum2;
    double rem1;
    double rem2;

    make_b(A, b, n);

    for (i = 0; i < n; i++)
    {
        rem1 = 0;

        for (j = 0; j < n; j++)
        {
            rem1 += A[i * n + j] * x0[j];
        }

        r[i] = rem1 - b[i];
    }

    for (k = 0; k < m; k++)
    {
        rem1 = 0;
        rem2 = 0;

        for (i = 0; i < n; i++)
        {
            sum1 = 0;
            sum2 = 0;
            for (j = 0; j < n; j++)
            {
                sum1 += A[i * n + j] * r[j];
                sum2 += A[i * n + j] * r[j] / A[j * n + j];
            }
            rem1 += sum2 * r[i];
            rem2 += sum2 * sum2;
            x[i] = sum1;
        }

        if (fabs(rem1) > 0)
        {
            for (i = 0; i < n; i++)
            {
                x0[i] -= r[i] * rem2 / rem1;
            }
        }
        else
        {
            return ERROR;
        }

        for (i = 0; i < n; i++)
        {
            x[i] = r[i] - x[i] * rem2 / rem1;
        }

        r = x;
    }

    *error1 = residual_1(A, b, x, n);
    *error2 = residual_2(x, n);
}


void sequence_7(double *A, double *x0, double *b, double *x, double *r, int n, int m, double t, double *error1, double *error2)//7
{
    int i;
    int j;
    int k;
    double rem;

    make_b(A, b, n);

    for (k = 0; k < m; k++)
    {
        for (i = 0; i < n; i++)
        {
            rem = 0;

            for (j = 0; j < n; j++)
            {
                rem += A[i * n + j] * x0[j];
            }

            x0[i] = (b[i] - rem) * t / A[i * n + i] + x0[i];
        }
    }

    for (i = 0; i < n; i++)
    {
        x[i] = x0[i];
    }

    *error1 = residual_1(A, b, x, n);
    *error2 = residual_2(x, n);
}


void sequence_8(double *A, double *x0, double *b, double *x, double *r, double *w, int n, int m, double t, double *error1, double *error2)//8
{
    int i;
    int j;
    int k;
    double rem;

    make_b(A, b, n);

    for (k = 0; k < m; i++)
    {
        for (i = 0; i < n; i++)
        {
            rem = 0;

            for (j = 0; j < n; j++)
            {
                rem += A[i * n + j] * x0[j];
            }

            x[i] = (b[i] - rem) * t

            for (j = 0; j <= i; j++)//solving system
            {
                x[i] += x0[j] * A[i * n + j];

                if (j > 0)
                {
                    //x[i] -= x[i - j] * A[i * n + i - j];
                    x[i] -= x[j - 1] * A[i * n + j - 1];
                }
            }

            x[i] /= A[i * n + i];
        }
        for (i = 0; i < n; i++)
        {
            x0[i] = x[i];
        }
    }

    *error1 = residual_1(A, b, x, n);
    *error2 = residual_2(x, n);
}


void sequence_9(double *A, double *x0, double *b, double *x, double *r, double *w, int n, int m, double t, double *error1, double *error2)//9
{
    int i;
    int j;
    int k;
    double rem;

    make_b(A, b, n);

    for (k = 0; k < m; i++)
    {
        for (i = n - 1; i <= 0; i--)
        {
            rem = 0;

            for (j = 0; j < n; j++)
            {
                rem += A[i * n + j] * x0[j];
            }

            x[i] = (b[i] - rem) * t

            for (j = n - 1; j >= i; j--)//solving system
            {
                x[i] += x0[j] * A[i * n + j];

                if (j < n - 1)
                {
                    x[i] -= x[j - 1] * A[i * n + j - 1];
                }
            }

            x[i] /= A[i * n + i];
        }

        for (i = 0; i < n; i++)
        {
            x0[i] = x[i];
        }
    }

    *error1 = residual_1(A, b, x, n);
    *error2 = residual_2(x, n);
}