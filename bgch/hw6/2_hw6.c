#include "hw6.h"

int main(int argc, char *argv[])
{
    char const *fname1 = 0;
    char const *fname2 = 0;
    int n;
    int m;
    int i;
    int ans;
    int c1;
    int c2;
    double *a;
    double *b;
    double *c;

    if (argc < 3)
    {
        printf("Usage %s file\n", argv[0]);
        return 1;
    }
    else if (argc == 4)
    {
        fname1 = argv[3];
    }
    else if (argc == 5)
    {
        fname1 = argv[3];
        fname2 = argv[4];
    }
    n = atoi(argv[1]);
    m = atoi(argv[2]);

    a = (double *) malloc(n * sizeof(double));
    b = (double *) malloc(m * sizeof(double));
    c = (double *) malloc((m + n) * sizeof(double));
    c1 = InitArray(fname1, a, n);
    c2 = InitArray(fname2, b, m);
    PrintMistakes(c1);
    PrintMistakes(c2);
    if (c1 != n)
    {
        if (c1 == -1)
        {
            for (i = 0 ; i < n ; i++)
                a[i] = rand();
        }
        else
        {
            free(a);
            free(b);
            free(c);
            return -1;
        }
    }
    if (c2 != m)
    {
        if (c2 == -1)
        {
            for (i = 0 ; i < m ; i++)
                b[i] = rand();
        }
        else
        {
            free(a);
            free(b);
            free(c);
            return -1;
        }
    }

    if (n > 20)
        PrintArray(a, 20);
    else
        PrintArray(a, n);
    if (m > 20)
        PrintArray(b, 20);
    else
        PrintArray(b, m);
    ans = Merge(a, b, c, n, m);
    printf("%d\n", ans);
    if (ans > 20)
        PrintArray(c, 20);
    else
        PrintArray(c, ans);
    free(a);
    free(b);
    free(c);
    return 0;
}
