#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hw13.h"


int main(int argc, char **argv)
{
    double a;
    double b;
    double eps;
    double x;
    int result;
    clock_t time;

    if (argc != 4)
    {
        printf("You have only <%d> args instead of <4>\n", argc);
        return -1;
    }

    a = atof(argv[1]);      // filename1 to read
    b = atof(argv[2]);
    eps = atof(argv[3]);

    time = clock();
    result = interpolation_2_method_root(a, b, eps, &x, &func);
    time = clock() - time;

    printf("Iterations = %d\n", result);
    if (result != -1)
        printf("Root = %lf\n", x);
    printf("Time = %lf\n", (double)time / CLOCKS_PER_SEC);

    return 0;
}
