#include "hw16.h"


int main(int argc, char *argv[])
{
    int n;
    int m;
    double *a;
    double t;
    const char *fname = 0;

    if (!((argc == 3 || argc == 4) && (m = atoi(argv[1])) > 0 && (n = atoi(argv[2])) > 0))
    {
        printf("Usage %s n m [file]\n", argv[0]);
        return 1;
    }

    if (argc == 4)
    {
        fname = argv[3];
    }

    if (!(a = (double *) malloc(n * m * sizeof(double))))
    {
        printf("Not enough memory!\n");
        return 2;
    }

    if (fname)
    {
        int ret;
        ret = read_matrix(a, m, n, fname);

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
            free(a);
            return 2;
        }
    }
    else
    {
        init_matrix(a, m, n);
    }

    print_matrix(a, m, n);
    printf("\n");

    t = clock();
    delete_column_and_line_with_min_dispersion(a, m, n);
    t = clock() - t;

    print_matrix(a, m - 1, n - 1);
    printf("\n");

    printf("Elapsed = %.2f\n", t / CLOCKS_PER_SEC);

    free(a);
    return 0;
}


