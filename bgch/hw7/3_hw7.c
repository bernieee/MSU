#include "hw7.h"

int main(int argc, char *argv[])
{
    char const *fname = 0;
    int n;
    int c;
    int ans;
    double *a;
    double x;

    if (argc != 4)
    {
        printf("Usage %s file\n", argv[0]);
        return 1;
    }
    n = atoi(argv[1]);
    x = atof(argv[2]);
    fname = argv[3];

    a = (double *) malloc(n * sizeof(double));
    c = InitArray(fname, a, n);
    //printf("%d\n", c);
    PrintMistakes(c);
    if (c != n)
    {
        free(a);
        return -1;
    }
    if (n > 20)
        PrintArray(a, 20);
    else
        PrintArray(a, n);
    ans = FindX1(a, n, x);
    printf("%d\n", ans);
    if (n > 20)
        PrintArray(a, 20);
    else
        PrintArray(a, n);
    free(a);
    return 0;
}
