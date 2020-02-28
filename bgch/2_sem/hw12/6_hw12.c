#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hw12.h"


int main(int argc, char **argv)
{
    double result_eps;
    double result_real;
    clock_t time_eps;
    clock_t time_real;
    double x;
    double eps;

    while ((scanf("%lf%lf", &x, &eps)) && (eps >= 0.))
    {
        time_eps = clock();
        result_eps = cos_eps_x(x, eps);
        time_eps = clock() - time_eps;

        time_real = clock();
        result_real = cos(x);
        time_real = clock() - time_real;

        printf("Eps = %.20lf\n", result_eps);
        printf("Time = %lf\n", (double)time_eps / CLOCKS_PER_SEC);

        printf("Real = %.20lf\n", result_real);
        printf("Time = %lf\n", (double)time_real / CLOCKS_PER_SEC);

        printf("Error = %.40lf\n", fabs(result_real - result_eps));
    }

    return 0;
}
