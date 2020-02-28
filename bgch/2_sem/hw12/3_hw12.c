#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hw12.h"


int main(int argc, char **argv)
{
    const char *a;
    int n;
    double x0;
    double result;
    clock_t time;
    double *x;
    double *y;

    if (argc != 4)
    {
        printf("You have only <%d> args instead of <4>\n", argc);
        return -1;
    }

    a = argv[1];      // filename1 to read
    n = atoi(argv[2]);
    x0 = atof(argv[3]);

    x = malloc(n * sizeof(double));
    y = malloc(n * sizeof(double));

    init_array123(a, n, x, y);

    time = clock();
    result = aitken(n, x0, x, y);
    time = clock() - time;
    printf("%lf\n", result);
    printf("Time = %lf\n", (double)time / CLOCKS_PER_SEC);

    return 0;
}
