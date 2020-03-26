#include "hw15.h"


int main(int argc, char *argv[])
{
    int n;
    int m;
    double *A;
    double *B;
    double *R;
    double res;
    double t;
    const char *fname_a = 0;
    const char *fname_b = 0;

    if (!((argc == 3 || argc == 5) && (m = atoi(argv[1])) > 0 && (n = atoi(argv[2])) > 0))
    {
        printf("Usage %s n m [file] [file]\n", argv[0]);
        return 1;
    }

    if (argc == 5)
    {
        fname_a = argv[3];
        fname_b = argv[4];
    }

    if (!(A = (double *) malloc(n * m * sizeof(double))))
    {
        printf("Not enough memory!\n");
        return 2;
    }

    if (!(B = (double *) malloc(n * m * sizeof(double))))
    {
        printf("Not enough memory!\n");
        free(A);
        return 2;
    }

    if (!(R = (double *) malloc(n * m * sizeof(double))))
    {
        printf("Not enough memory!\n");
        free(A);
        free(B);
        return 2;
    }

    if (fname_a && fname_b)
    {
        int ret_a;
        int ret_b;
        ret_a = read_matrix(A, m, n, fname_a);
        ret_b = read_matrix(B, n, m, fname_b);

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
            free(B);
            free(R);
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
            free(B);
            free(R);
            return 2;
        }
    }
    else
    {
        init_matrix(A, m, n);
        init_matrix(B, n, m);
    }

    print_matrix(A, m, n);
    print_matrix(B, n, m);
    printf("\n");

    t = clock();
    res = max_sum_lines_1_norm(A, B, R, m, n);
    t = clock() - t;

    printf("Result = %lf\n", res);
    printf("Elapsed = %.2f\n", t / CLOCKS_PER_SEC);

    free(A);
    free(B);
    free(R);
    return 0;
}
