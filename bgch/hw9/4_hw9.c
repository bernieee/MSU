#include "hw9.h"


int main(int argc, char *argv[])
{
    char const *fname = 0;
    int n;
    int i;
    int c;
    clock_t time;
    char **a;

    if (argc != 3)
    {
        printf("Usage %s file\n", argv[0]);
        return 1;
    }
    n = atoi(argv[1]);
    fname = argv[2];

    a = (char **) malloc(n * sizeof(char *));
    c = InitArray(fname, a, n);

    PrintMistakes(c);
    if (c != n)
    {
        for (i = 0; i < n; i++)
            free(a[i]);
        free(a);
        return -1;
    }
    if (n > 20)
        PrintArray(a, 20);
    else
        PrintArray(a, n);
    printf("\n");
    time = clock();
    BubbleSort(a, n, SiftDown);
    time = clock() - time;
    printf("Time = %lf\n", (double)time / CLOCKS_PER_SEC);
    if (n > 20)
        PrintArray(a, 20);
    else
        PrintArray(a, n);

    for (i = 0; i < n; i++)
        free(a[i]);
    free(a);
    return 0;
}
