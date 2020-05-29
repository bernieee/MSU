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


static double euclid_norm(double *b, int n)
{
    int i;
    double res;

    res = 0;

    for (i = 0; i < n; i++)
    {
        res += b[i] * b[i];
    }

    return res;
}


double lambda_sequence(double *A, double *x0, double *x, int n, int m)//1
{
    int i;
    int j;
    int k;
    double sum;
    double rem1;
    double rem2;
    double res;
    double eps = 1e-17;

    for (k = 0; k < m; k++)
    {
        rem1 = 0;

        for (i = 0; i < n; i++)
        {
            sum = 0;

            for (j = 0; j < n; j++)
            {
                sum += A[i * n + j] * x0[j];
            }

            x[i] = sum;
            rem1 += x0[i] * x0[i];
        }

        if (fabs(rem1) > eps)
        {
            for (i = 0; i < n; i++)
            {
                x0[i] = x[i];
            }
        }
        else
        {
            return 0;
        }
    }

    rem1 = 0;
    rem2 = 0;

    for (i = 0; i < n; i++)
    {
        sum = 0;

        for (j = 0; j < n; j++)
        {
            sum += A[i * n + j] * x0[j];
        }

        x[i] = sum;
        rem1 += x0[i] * x0[i];
        rem2 += sum * x0[i];
    }

    res = rem2 / rem1;

    for (i = 0; i < n; i++)
    {
        x[i] = x0[i];
    }

    return res;
}


int sequence_2(double *A, double *x0, double *b, double *x, int n, int m, double t, double *error1, double *error2)//2
{
    int i;
    int j;
    int k;
    double sum;

    make_b(A, b, n);

    for (k = 0; k < m; k++)
    {
        for (i = 0; i < n; i++)
        {
            sum = 0;

            for (j = 0; j < n; j++)
            {
                sum += A[i * n + j] * x0[j];
            }

            x[i] = (b[i] - sum) * t + x0[i];
        }
        for (i = 0; i < n; i++)
        {
            x0[i] = x[i];
        }
    }

    *error1 = residual_1(A, b, x, n);
    *error2 = residual_2(x, n);

    return 0;
}


int sequence_3(double *A, double *x0, double *b, double *x, double *r, int n, int m, double *error1, double *error2)//3
{
    int i;
    int j;
    int k;
    double sum;
    double rem1;
    double rem2;
    double eps;

    make_b(A, b, n);
    eps = euclid_norm(b, n); // TODO aff a flag to square root

    eps = eps * 1e-17 * 1e-17;

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

        if (fabs(rem2) > eps)
        {
            for (i = 0; i < n; i++)
            {
                x0[i] -= r[i] * rem1 / rem2;
            }
        }
        else
        {
            for (i = 0; i < n; i++)
            {
                x[i] = x0[i];
            }

            *error1 = residual_1(A, b, x, n);
            *error2 = residual_2(x, n);

            printf("%d\n", i);

            return 0;
        }

        for (i = 0; i < n; i++)
        {
            r[i] = r[i] - x[i] * rem1 / rem2;
        }
    }

    for (i = 0; i < n; i++)
    {
        x[i] = x0[i];
    }

    *error1 = residual_1(A, b, x, n);
    *error2 = residual_2(x, n);

    return 0;
}


int sequence_4(double *A, double *x0, double *b, double *x, double *r, int n, int m, double *error1, double *error2)//4
{
    int i;
    int j;
    int k;
    double sum;
    double rem1;
    double rem2;
    double eps;

    make_b(A, b, n);
    eps = euclid_norm(b, n);

    eps = eps * 1e-17 * 1e-17;

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

        if (fabs(rem2) > eps)
        {
            for (i = 0; i < n; i++)
            {
                x0[i] -= r[i] * rem1 / rem2;
            }
        }
        else
        {
            for (i = 0; i < n; i++)
            {
                x[i] = x0[i];
            }

            *error1 = residual_1(A, b, x, n);
            *error2 = residual_2(x, n);

            return 0;
        }

        for (i = 0; i < n; i++)
        {
            r[i] = r[i] - x[i] * rem1 / rem2;
        }
    }

    for (i = 0; i < n; i++)
    {
        x[i] = x0[i];
    }

    *error1 = residual_1(A, b, x, n);
    *error2 = residual_2(x, n);

    return 0;
}


int sequence_5(double *A, double *x0, double *b, double *x, double *r, int n, int m, double *error1, double *error2)//5
{
    int i;
    int j;
    int k;
    double sum1;
    double sum2;
    double rem1;
    double rem2;
    double eps;

    make_b(A, b, n);
    eps = euclid_norm(b, n);

    eps = eps * 1e-17 * 1e-17;

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

        if (fabs(rem2) > 0)
        {
            for (i = 0; i < n; i++)
            {
                x0[i] -= r[i] * rem1 / rem2;
            }
        }
        else
        {
            for (i = 0; i < n; i++)
            {
                x[i] = x0[i];
            }

            *error1 = residual_1(A, b, x, n);
            *error2 = residual_2(x, n);

            return 0;
        }

        for (i = 0; i < n; i++)
        {
            r[i] = r[i] - x[i] * rem1 / rem2;
        }

        //r = x;
    }

    for (i = 0; i < n; i++)
    {
        x[i] = x0[i];
    }

    *error1 = residual_1(A, b, x, n);
    *error2 = residual_2(x, n);

    return 0;
}


int sequence_6(double *A, double *x0, double *b, double *x, double *r, int n, int m, double *error1, double *error2)//6
{
    int i;
    int j;
    int k;
    double sum1;
    double sum2;
    double rem1;
    double rem2;
    double eps;

    make_b(A, b, n);
    eps = euclid_norm(b, n);

    eps = eps * 1e-17 * 1e-17;

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

        if (fabs(rem2) > 0)
        {
            for (i = 0; i < n; i++)
            {
                x0[i] -= r[i] * rem1 / rem2;
            }
        }
        else
        {
            for (i = 0; i < n; i++)
            {
                x[i] = x0[i];
            }

            *error1 = residual_1(A, b, x, n);
            *error2 = residual_2(x, n);

            return 0;
        }

        for (i = 0; i < n; i++)
        {
            r[i] = r[i] - x[i] * rem1 / rem2;
        }
    }

    for (i = 0; i < n; i++)
    {
        x[i] = x0[i];
    }

    *error1 = residual_1(A, b, x, n);
    *error2 = residual_2(x, n);

    return 0;
}


int sequence_7(double *A, double *x0, double *b, double *x, double *r, int n, int m, double t, double *error1, double *error2)//7
{
    int i;
    int j;
    int k;
    double rem;

    (void) r;

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

            x[i] = (b[i] - rem) * t / A[i * n + i] + x0[i];
        }

        for (i = 0; i < n; i++)
        {
            x0[i] = x[i];
        }

    }

    *error1 = residual_1(A, b, x, n);
    *error2 = residual_2(x, n);

    return 0;
}


int sequence_8(double *A, double *x0, double *b, double *x, double *r, double *w, int n, int m, double t, double *error1, double *error2)//8
{
    int i;
    int j;
    int k;
    double rem;

    (void) r;
    (void) w;

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

            x[i] = (b[i] - rem) * t;

            for (j = 0; j <= i; j++)//solving system
            {
                x[i] += x0[j] * A[i * n + j];

                if (j > 0)
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

    return 0;
}


int sequence_9(double *A, double *x0, double *b, double *x, double *r, double *w, int n, int m, double t, double *error1, double *error2)//9
{
    int i;
    int j;
    int k;
    double rem;

    (void) r;
    (void) w;

    make_b(A, b, n);

    for (k = 0; k < m; k++)
    {
        for (i = n - 1; i >= 0; i--)
        {
            rem = 0;

            for (j = 0; j < n; j++)
            {
                rem += A[i * n + j] * x0[j];
            }

            x[i] = (b[i] - rem) * t;

            for (j = n - 1; j >= i; j--)//solving system
            {
                x[i] += x0[j] * A[i * n + j];

                if (j < n - 1)
                {
                    x[i] -= x[j + 1] * A[i * n + j + 1];
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

    return 0;
}


int sequence_10(double *A, double *x0, double *b, double *x, double *r, double *w, int n, int m, double t, double *error1, double *error2)//10
{
    int i;
    int j;
    int k;
    double rem;

    (void) r;
    (void) w;

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

            x[i] = (b[i] - rem) * t;

            for (j = 1; j <= i; j++)//solving system
            {
                x[i] -= x[j - 1] * A[i * n + j - 1] / A[(j - 1) * n + j - 1];
            }
        }

        for (i = n - 1; i >= 0; i--)
        {
            for (j = n - 1; j >= i; j--)//solving system
            {
                x[i] += x0[j] * A[i * n + j];

                if (j < n - 1)
                {
                    x[i] -= x[j + 1] * A[i * n + j + 1];
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

    return 0;
}
