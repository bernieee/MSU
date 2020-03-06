#include <stdio.h>
#include <math.h>
#include "hw13.h"


double parabol(double x)
{
    return 0.4 * x * x * x * x * x - 3 * x * x * x - 5;
}
double line(double x)
{
    return x - 1;
}
double sin_deriv(double x)
{
    return cos(x);
}
double parabol_deriv(double x)
{
    return 2 * x * x * x * x - 9 * x * x;
}
double line_deriv(double x)
{
    return 1;
}
//double parabol(double x)
//double parabol(double x)
