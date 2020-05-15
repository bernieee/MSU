#include "hw19.h"


int main(int argc, char *argv[])
{
    double a;
    double b;
    double t;
    double res;
    int n;
    int k;
    int count;

    count = 0;

    if (argc != 5)
    {
        printf("Usage %s a b n k\n", argv[0]);
    }

    sscanf(argv[1], "%lf", &a);
    sscanf(argv[2], "%lf", &b);
    n = atoi(argv[3]);
    //k = atoi(argv[4]);
    sscanf(argv[4], "%d", &k);

    if (k < 0 || k > 6)
    {
        printf("ERROR\n");
        return -1;
    }

    t = clock();
    res = simpson_sqrt_integral(a, b, n, k, &count, &func);
    t = clock() - t;

    printf("Answer = %10.3e  %d  %.2f\n", res, count, t / CLOCKS_PER_SEC);

    return 0;
}

