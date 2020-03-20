#include "hw14.h"


int main(int argc, char *argv[])
{
    int n;
    int m;
    int i;
    int j;
    double b;
    double *a;
    double t;
    const char *fname = 0;

    if (!((argc == 6 || argc == 7) && (m = atoi(argv[1])) > 0 && (n = atoi(argv[2])) > 0
        && (sscanf(argv[3], "%d", &i)) && (sscanf(argv[4], "%d", &j)) && (sscanf(argv[5], "%lf", &b))))
    {
        printf("Usage %s n m [file]\n", argv[0]);
        return 1;
    }

    if (argc == 7)
    {
        fname = argv[6];
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
    sum_lines_multiplied_by_b(a, b, m, n, i, j);
    t = clock() - t;

    print_matrix(a, m, n);

    printf("Elapsed = %.2f\n", t / CLOCKS_PER_SEC);

    free(a);
    return 0;
}


