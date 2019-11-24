#include "hw5.h"

int main(int argc, char *argv[])
{
    char const *fname1 = 0;
    char const *fname2 = 0;
    int n;
    int m;
    int ans;
    int c1;
    int c2;
    double *a;
    double *b;
    double *c;

    if (argc != 5)
    {
        printf("Usage %s file\n", argv[0]);
        return 1;
    }
    n = atoi(argv[1]);
    m = atoi(argv[2]);
    fname1 = argv[3];
    fname2 = argv[4];

    a = (double *) malloc(n * sizeof(double));
    b = (double *) malloc(m * sizeof(double));
    c = (double *) malloc(m + n * sizeof(double));
    c1 = InitArray(fname1, a, n);
    c2 = InitArray(fname2, b, m);
    PrintMistakes(c1);
    PrintMistakes(c2);
    if (c1 != n)
    {
        free(a);
        free(b);
        return -1;
    }
    if (c2 != m)
    {
        free(a);
        free(b);
        return -1;
    }

    PrintArray(a, n);
    PrintArray(b, m);
    ans = Merge(a, b, c, n, m);
    printf("%d\n", ans);
    PrintArray(c, ans);
    free(a);
    free(b);
    return 0;
}
