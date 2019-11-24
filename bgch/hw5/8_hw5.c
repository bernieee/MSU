#include "hw5.h"

int main(int argc, char *argv[])
{
    char const *fname1 = 0;
    char const *fname2 = 0;
    int n;
    int c;
    int ans;
    double *a;

    if (argc != 4)
    {
        printf("Usage %s file\n", argv[0]);
        return 1;
    }
    n = atoi(argv[1]);
    fname1 = argv[2];
    fname2 = argv[3];

    a = (double *) malloc(n * sizeof(double));
    c = InitArray(fname1, a, n);
    PrintMistakes(c);
    if (c != n)
    {
        free(a);
        return -1;
    }
    PrintArray(a, n);
    ans = SequenceIn(fname2, a, n);
    printf("%d\n", ans);
    free(a);
    return 0;
}
