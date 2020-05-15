#include "hw19.h"


int main(int argc, char *argv[])
{
    double a;
    double b;
    double t;
    double res;
    double eps;
    int n;
    int k;
    int count;

    count = 0;

    if (argc != 5)
    {
        printf("Usage %s a b eps k\n", argv[0]);
    }

    sscanf(argv[1], "%lf", &a);
    sscanf(argv[2], "%lf", &b);
    sscanf(argv[3], "%lf", &eps);
    sscanf(argv[4], "%d", &k);
    //k = atoi(argv[4]);

    if (k < 0 || k > 6)
    {
        printf("ERROR\n");
        return -1;
    }

    t = clock();
    n = simpson_eps_integral(a, b, eps, &res, k, &count, &func);
    t = clock() - t;

    if (n == ERROR)
    {
        printf("ERROR\n");
        return -1;
    }

    printf("Answer = %10.3e  %d  %d  %.2f\n", res, n, count, t / CLOCKS_PER_SEC);

    return 0;
}

