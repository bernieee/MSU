#include "hw7.h"

int main(int argc, char *argv[])
{
    char const *fname = 0;
    int n;
    int i;
    int c;
    clock_t time;
    double *a;

    if (argc < 2)
    {
        printf("Usage %s file\n", argv[0]);
        return 1;
    }
    else if (argc == 3)
    {
        fname = argv[2];
    }
    n = atoi(argv[1]);
    //fname = argv[2];

    a = (double *) malloc(n * sizeof(double));
    c = InitArray(fname, a, n);
    //printf("%d\n", c);
    PrintMistakes(c);
    if (c != n)
    {
        if (c == -1)
        {
            for (i = 0 ; i < n ; i++)
                a[i] = rand();
        }
        else
        {
            free(a);
            return -1;
        }
    }
    if (n > 20)
        PrintArray(a, 20);
    else
        PrintArray(a, n);
    printf("\n");
    time = clock();
    QuickSort(a, n, SiftUp);
    time = clock() - time;
    printf("Time = %lf\n", (double)time / CLOCKS_PER_SEC);
    if (n > 20)
        PrintArray(a, 20);
    else
        PrintArray(a, n);
    free(a);
    return 0;
}
