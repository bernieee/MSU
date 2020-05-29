#include "hw19.h"


int main(int argc, char *argv[])
{
    double x;
    double h;
    double t;
    double res;
    int k;

    if (argc != 4)
    {
        printf("Usage %s x h k\n", argv[0]);
        return -1;
    }

    sscanf(argv[1], "%lf", &x);
    sscanf(argv[2], "%lf", &h);
    sscanf(argv[3], "%d", &k);
    //k = atoi(argv[3]);

    if (k < 0 || k > 6)
    {
        printf("Wrong k input\n");
        return -1;
    }

    t = clock();
    res = first_derivative_h(x, h, k, &func);
    t = clock() - t;

    printf("Answer = %10.3e  %.2f\n", res, t / CLOCKS_PER_SEC);

    return 0;
}

