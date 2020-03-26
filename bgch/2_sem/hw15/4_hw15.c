#include "hw15.h"


int main(int argc, char *argv[])
{
    int n;
    int m;
    double *A;
    double *b;
    double *x;
    double *r;
    double res;
    double t;
    const char *fname_a = 0;
    const char *fname_b = 0;
    const char *fname_x = 0;

    if (!((argc == 3 || argc == 6) && (m = atoi(argv[1])) > 0 && (n = atoi(argv[2])) > 0))
    {
        printf("Usage %s n m [file] [file] [file]\n", argv[0]);
        return 1;
    }

    if (argc == 6)
    {
        fname_a = argv[3];
        fname_b = argv[4];
        fname_x = argv[5];
    }

    if (!(A = (double *) malloc(n * m * sizeof(double))))
    {
        printf("Not enough memory!\n");
        return 2;
    }

    if (!(b = (double *) malloc(m * sizeof(double))))
    {
        printf("Not enough memory!\n");
        free(A);
        return 2;
    }

    if (!(x = (double *) malloc(n * sizeof(double))))
    {
        printf("Not enough memory!\n");
        free(A);
        free(b);
        return 2;
    }

    if (!(r = (double *) malloc(m * sizeof(double))))
    {
        printf("Not enough memory!\n");
        free(A);
        free(b);
        free(x);
        return 2;
    }

    if (fname_a && fname_b && fname_x)
    {
        int ret_a;
        int ret_b;
        int ret_x;
        ret_a = read_matrix(A, m, n, fname_a);
        ret_b = read_matrix(b, m, 1, fname_b);
        ret_x = read_matrix(x, n, 1, fname_x);

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
            free(b);
            free(x);
            free(r);
            return 2;
        }
        else if (ret_b != SUCCESS)
        {
            switch(ret_b)
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
            free(b);
            free(x);
            free(r);
            return 2;
        }
        else if (ret_x != SUCCESS)
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
            free(b);
            free(x);
            free(r);
            return 2;
        }
    }
    else
    {
        init_matrix(A, m, n);
        init_matrix(b, m, 1);
        init_matrix(x, n, 1);
    }

    print_matrix(A, m, n);
    printf("\n");
    print_matrix(b, m, 1);
    printf("\n");
    print_matrix(x, n, 1);
    printf("\n");

    t = clock();
    res = max_norm(A, b, x, r, m, n);
    t = clock() - t;

    printf("Result = %lf\n", res);
    printf("Elapsed = %.2f\n", t / CLOCKS_PER_SEC);

    free(A);
    free(b);
    free(x);
    free(r);
    return 0;
}
