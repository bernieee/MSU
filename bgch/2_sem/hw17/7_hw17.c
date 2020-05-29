#include "hw17.h"


int main(int argc, char *argv[])
{
    int i;
    int n;
    int m;
    int ans;
    double eps = 1e-17;
    double *A;
    double *x0;
    double *b;
    double *x;
    double *r;
    double T;
    double t;
    double error1;
    double error2;
    const char *fname_a = 0;
    const char *fname_x = 0;

    if (!((argc == 4 || argc == 6) && (m = atoi(argv[1])) > 0 && (n = atoi(argv[2])) > 0 
        && (sscanf(argv[3], "%lf", &t))))
    {
        printf("Usage %s m n t [file] [file]\n", argv[0]);
        return 1;
    }

    if (argc == 6)
    {
        fname_a = argv[4];
        fname_x = argv[5];
    }

    if (fabs(t) >= eps && fabs(t) <= eps)
    {
        printf("t == 0\n");
        return 3;
    }

    if (!(A = (double *) malloc(n * n * sizeof(double))))
    {
        printf("Not enough memory!\n");
        return 2;
    }

    if (!(x = (double *) malloc(n * sizeof(double))))
    {
        printf("Not enough memory!\n");
        free(A);
        return 2;
    }

    if (!(x0 = (double *) malloc(n * sizeof(double))))
    {
        printf("Not enough memory!\n");
        free(A);
        free(x);
        return 2;
    }

    if (!(b = (double *) malloc(n * sizeof(double))))
    {
        printf("Not enough memory!\n");
        free(A);
        free(x);
        free(x0);
        return 2;
    }

    if (!(r = (double *) malloc(n * sizeof(double))))
    {
        printf("Not enough memory!\n");
        free(A);
        free(x);
        free(x0);
        free(b);
        return 2;
    }

    if (fname_a && fname_x)
    {
        int ret_a;
        int ret_x;
        ret_a = read_matrix(A, n, n, fname_a);
        ret_x = read_matrix(x0, n, 1, fname_x);

        if (ret_a != SUCCESS)
        {
            switch(ret_a)
            {
                case ERROR_OPEN:
                    printf("Can not open file!\n");
                    break;
                case ERROR_READ:
                    printf("Can not read an element!\n");
                    break;
                default:
                    printf("Unknown error!\n");

            }
            free(A);
            free(x);
            free(x0);
            free(b);
            free(r);
            return 2;
        }

        if (ret_x != SUCCESS)
        {
            switch(ret_x)
            {
                case ERROR_OPEN:
                    printf("Can not open file!\n");
                    break;
                case ERROR_READ:
                    printf("Can not read an element!\n");
                    break;
                default:
                    printf("Unknown error!\n");

            }
            free(A);
            free(x);
            free(x0);
            free(b);
            free(r);
            return 2;
        }
    }
    else
    {
        init_matrix(A, n, n);

        for (i = 0; i < n; i++)
        {
            x0[i] = 1;
        }
    }

    for (i = 0; i < n; i++)
    {
        if (!(fabs(A[i * n + i]) > eps))
        {
            printf("There are zeros on diagonal\n");
            return 3;
        }
    }

    //print_matrix(A, n, n);
    //printf("\n");

    //print_matrix(x0, n, 1);
    //printf("\n");

    T = clock();
    ans = sequence_7(A, x0, b, x, r, n, m, t, &error1, &error2);
    T = clock() - T;

    printf("\n");
    print_matrix(x, 1, n);
    printf("\n");

    if (ans == 0)
    {
        printf("Residual_b = %e\nResidual_x = %e\n", error1, error2);
    }
    else
    {
        printf("Error\n");
    }
    printf("Elapsed = %.2f\n\n", T / CLOCKS_PER_SEC);

    free(A);
    free(x);
    free(x0);
    free(b);
    free(r);
    return 0;
}


