#include "hw19.h"


int main(int argc, char *argv[])
{
    double a;
    double b;
    double t;
    double res;
    double eps;
    int k;
    int count;

    count = 0;

    if (argc != 4)
    {
        printf("Usage %s a eps k\n", argv[0]);
    }

    sscanf(argv[1], "%lf", &a);
    sscanf(argv[2], "%lf", &eps);
    sscanf(argv[3], "%d", &k);
    //k = atoi(argv[4]);

    if (k < 0 || k > 6)
    {
        printf("ERROR\n");
        return -1;
    }

    t = clock();
    b = trapeze_area_eps_integral(a, eps, &res, k, &count, &func);
    t = clock() - t;

    if (!(fabs(b - ERROR) > 0))
    {
        printf("ERROR\n");
        return -1;
    }

    printf("Answer = %10.3e  %10.3e  %d  %.2f\n", res, b, count, t / CLOCKS_PER_SEC);

    return 0;
}

