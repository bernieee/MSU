#include "hw17.h"


int main(int argc, char *argv[])
{
    int i;
    int n;
    int m;
    //double eps = 1e-17;
    double *A;
    double *x0;
    double *x;
    double T;
    double lambda;
    const char *fname_a = 0;
    const char *fname_x = 0;

    if (!((argc == 3 || argc == 5) && (m = atoi(argv[1])) > 0 && (n = atoi(argv[2])) > 0))
    {
        printf("Usage %s m n [file] [file]\n", argv[0]);
        return 1;
    }

    if (argc == 5)
    {
        fname_a = argv[3];
        fname_x = argv[4];
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

    //print_matrix(A, n, n);
    //printf("\n");

    //print_matrix(x0, n, 1);
    //printf("\n");

    T = clock();
    lambda = lambda_sequence(A, x0, x, n, m);
    T = clock() - T;

    if (fabs(lambda) > 0)
    {
        printf("\n");
        print_matrix(x, 1, n);
        printf("\n");

        printf("Lambda = %lf\n", lambda);
    }
    else
    {
        printf("Error\n");
    }

    printf("Elapsed = %.2f\n\n", T / CLOCKS_PER_SEC);

    free(A);
    free(x);
    free(x0);
    return 0;
}


