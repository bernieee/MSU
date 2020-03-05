#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hw13.h"


int main(int argc, char **argv)
{
    double x0;
    double eps;
    double x;
    int result;
    clock_t time;

    if (argc != 3)
    {
        printf("You have only <%d> args instead of <3>\n", argc);
        return -1;
    }

    x0 = atof(argv[1]);      // filename1 to read
    eps = atof(argv[2]);

    time = clock();
    result = newton_method_root(x0, eps, &x, &parabol, &parabol_deriv);
    time = clock() - time;

    printf("Iterations = %d\n", result);
    if (result != -1)
        printf("Root = %lf\n", x);
    printf("Time = %lf\n", (double)time / CLOCKS_PER_SEC);

    return 0;
}
