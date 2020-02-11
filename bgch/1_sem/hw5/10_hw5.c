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
    printf("\n");
    PrintArray(b, m);
    printf("\n");
    ans = DeleteBFromAMove(a, b, n, m);
    PrintArray(a, ans);
    printf("%d\n", ans);
    free(a);
    free(b);
    return 0;
}
