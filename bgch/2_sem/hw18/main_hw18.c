#include "io_hw18.h"
#include "solve_hw18.h"


int main(int argc, char *argv[])
{
    int n;
    int m;
    int k;
    int er;
    double *A;
    double *b;
    double *x;
    double error1;
    double error2;
    double T;
    const char *fname = 0;

    if (!((argc == 4 || argc == 5) && (n = atoi(argv[1])) > 0 && (m = atoi(argv[2])) > 0))
    {
        printf("Usage %s n m k [file]\n", argv[0]);
        return 1;
    }

    k = atoi(argv[3]);

    if (argc == 4 && (k < 1 || k > 4))
    {
        printf("Wrong Input!\n");
        return 2;
    }

    if (k == 0 && argc == 5)
    {
        fname = argv[4];
    }

    if (k != 0 && argc == 5)
    {
        printf("Wrong Input!\n");
        return 2;
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

    if (!(b = (double *) malloc(n * sizeof(double))))
    {
        printf("Not enough memory!\n");
        free(A);
        free(x);
        return 2;
    }

    if (fname)
    {
        int ret;
        ret = read_matrix(A, n, n, fname);

        if (ret != SUCCESS)
        {
            switch(ret)
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
            free(b);
            return 2;
        }
    }
    else
    {
        init_matrix(A, n, n, k);
    }

    make_b(A, b, n);

    print_matrix(A, n, n, m);
    printf("\n");

    //print_matrix(b, n, 1, m);
    //printf("\n");

    T = clock();
    er = reflection_method_24(A, b, x, n);
    T = clock() - T;

    if (er == ERROR)
    {
        printf("Division by zero!\n");
        return 2;
    }

    print_matrix(x, 1, n, m);
    printf("\n");

    if (fname)
    {
        read_matrix(A, n, n, fname);
    }
    else
    {
        init_matrix(A, n, n, k);
    }

    make_b(A, b, n);

    error1 = residual_1(A, b, x, n);
    error2 = residual_2(x, n);

    printf("Residual b = %10.10e\n", error1);
    printf("Residual x = %10.10e\n\n", error2);
    printf("Elapsed = %.2f\n\n", T / CLOCKS_PER_SEC);

    free(A);
    free(x);
    free(b);
    return 0;
}


