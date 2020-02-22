#include "hw5.h"

int main(int argc, char *argv[])
{
    char const *fname = 0;
    int n;
    int k;
    int c;
    double *a;

    if (argc != 4)
    {
        printf("Usage %s file\n", argv[0]);
        return 1;
    }
    n = atoi(argv[1]);
    k = atoi(argv[2]);
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
    PrintArray(a, n);
    Cycle(a, n, k);
    PrintArray(a, n);
    free(a);
    return 0;
}
