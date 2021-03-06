#include "hw19.h"


int main(int argc, char *argv[])
{
    double a;
    double b;
    double t;
    double res;
    double eps;
    int k;
    int n;
    int count_x;
    int count_y;

    count_x = 0;
    count_y = 0;

    if (argc != 5)
    {
        printf("Usage %s a b eps k\n", argv[0]);
        return -1;
    }

    sscanf(argv[1], "%lf", &a);
    sscanf(argv[2], "%lf", &b);
    sscanf(argv[3], "%lf", &eps);
    sscanf(argv[4], "%d", &k);

    if (k < 0 || k > 6)
    {
        printf("Wrong k input\n");
        return -1;
    }

    t = clock();
    n = curve_lengh(a, b, eps, &res, k, &count_x, &count_y, &func_x, &func);
    t = clock() - t;

    if (n == ERROR)
    {
        printf("Answer = %d  %d  %d  %.2f\n", n, count_x, count_y, t / CLOCKS_PER_SEC);
        return -1;
    }

    printf("Answer = %10.3e  %d  %d  %d  %.2f\n", res, n, count_x, count_y, t / CLOCKS_PER_SEC);

    return 0;
}

