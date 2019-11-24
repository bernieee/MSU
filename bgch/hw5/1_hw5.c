#include "hw5.h"

int main(int argc, char *argv[])
{
    char const *fname = 0;
    int n;
    int c;
    int ans;
    double *a;

    if (argc != 3)
    {
        printf("Usage %s file\n", argv[0]);
        return 1;
    }
    n = atoi(argv[1]);
    fname = argv[2];

    a = (double *) malloc(n * sizeof(double));
    c = InitArray(fname, a, n);
    printf("%d\n", c);
    PrintMistakes(c);
    if (c != n)
    {
        free(a);
        return -1;
    }
    PrintArray(a, n);
    ans = Symetry(a, n);
    printf("%d\n", ans);
    free(a);
    return 0;
}
