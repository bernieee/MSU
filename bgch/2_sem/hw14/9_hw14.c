#include "hw14.h"


int main(int argc, char *argv[])
{
    int n;
    int m;
    double *a;
    double *b;
    double *c;
    double t;
    const char *fname_a = 0;
    const char *fname_b = 0;

    if (!((argc == 3 || argc == 5) && (m = atoi(argv[1])) > 0 && (n = atoi(argv[2])) > 0))
    {
        printf("Usage %s n m [file]\n", argv[0]);
        return 1;
    }

    if (argc == 5)
    {
        fname_a = argv[3];
        fname_b = argv[4];
    }

    if (!(a = (double *) malloc(n * m * sizeof(double))))
    {
        printf("Not enough memory!\n");
        return 2;
    }

    if (!(b = (double *) malloc(n * sizeof(double))))
    {
        printf("Not enough memory!\n");
        return 2;
    }

    if (!(c = (double *) malloc(m * sizeof(double))))
    {
        printf("Not enough memory!\n");
        return 2;
    }

    if (fname_a && fname_b)
    {
        int ret_a;
        int ret_b;
        ret_a = read_matrix(a, m, n, fname_a);
        ret_b = read_matrix(b, n, 1, fname_b);

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
            free(a);
            free(b);
            free(c);
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
            free(a);
            free(b);
            free(c);
            return 2;
        }
    }
    else
    {
        init_matrix(a, m, n);
        init_matrix(b, n, 1);
    }

    print_matrix(a, m, n);
    printf("\n");
    print_matrix(b, n, 1);
    printf("\n");

    t = clock();
    matrix_multiplied_by_vector_to_vector(a, b, c, m, n);
    t = clock() - t;

    print_matrix(c, m, 1);

    printf("Elapsed = %.2f\n", t / CLOCKS_PER_SEC);

    free(a);
    free(b);
    free(c);
    return 0;
}


