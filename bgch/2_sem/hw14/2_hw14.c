#include "hw14.h"


int main(int argc, char *argv[])
{
    int n;
    int res;
    double *a;
    double t;
    const char *fname = 0;

    if (!((argc == 2 || argc == 3) && (n = atoi(argv[1])) > 0))
    {
        printf("Usage %s n [file]\n", argv[0]);
        return 1;
    }

    if (argc == 3)
    {
        fname = argv[2];
    }

    if (!(a = (double *) malloc(n * n * sizeof(double))))
    {
        printf("Not enough memory!\n");
        return 2;
    }

    if (fname)
    {
        int ret;
        ret = read_matrix(a, n, n, fname);

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
        init_matrix(a, n, n);
    }

    print_matrix(a, n, n);

    t = clock();
    res = trace(a, n);
    t = clock() - t;

    printf("Elapsed = %.2f\n", t / CLOCKS_PER_SEC);
    printf("Result = %d\n", res);

    free(a);
    return 0;
}


