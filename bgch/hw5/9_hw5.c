#include "hw5.h"

int main(int argc, char *argv[])
{
    char const *fname = 0;
    int n;
    double x;
    int c;
    int ans;
    double *a;

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
    PrintMistakes(c);
    if (c != n)
    {
        free(a);
        return -1;
    }
    PrintArray(a, n);
    printf("\n");
    ans = DeleteX(a, n, x);
    PrintArray(a, ans);
    printf("%d\n", ans);
    free(a);
    return 0;
}
