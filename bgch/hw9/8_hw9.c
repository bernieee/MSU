#include "hw9.h"

int main(int argc, char *argv[])
{
    char const *fname = 0;
    int n;
    int i;
    int c;
    clock_t time;
    char **a;
    char **b;

    if (argc != 3)
    {
        printf("Usage %s file\n", argv[0]);
        return 1;
    }
    n = atoi(argv[1]);
    fname = argv[2];

    a = (char **) malloc(n * sizeof(char *));
    b = (char **) malloc(n * sizeof(char *));
    c = InitArray(fname, a, n);
    //printf("%d\n", c);
    PrintMistakes(c);
    if (c != n)
    {
        free(a);
        free(b);
        return -1;
    }
    if (n > 20)
        PrintArray(a, 20);
    else
        PrintArray(a, n);
    printf("\n");
    time = clock();
    MergeSort(a, b, n, SiftDown);
    time = clock() - time;
    printf("Time = %lf\n", (double)time / CLOCKS_PER_SEC);
    if (n > 20)
        PrintArray(a, 20);
    else
        PrintArray(a, n);
    free(a);
    free(b);
    return 0;
}
