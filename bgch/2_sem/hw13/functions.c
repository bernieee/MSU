#include <stdio.h>
#include <math.h>
#include "hw13.h"


double parabol(double x)
{
    return -x * x - 5 * x + 6;
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
    return 4 * x;
}
double line_deriv(double x)
{
    return 1;
}
//double parabol(double x)
//double parabol(double x)
