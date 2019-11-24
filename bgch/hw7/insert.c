int InsertSort(double *a, int n, int (*Sift) (double x, double y))//6
{
    int i;
    int j;
    int k;
    double c;
    for (i = 1 ; i < n ; i++)
    {
        c = a[i];
        for (j = 0 ; j < i ; j++)
        {
            if ((*Sift)(c, a[j]) < 0)
                break;
        }
        //printf("%d\n", j);
        for (k = i ; k > j ; k--)
        {
            a[k] = a[k - 1];
        }
        a[j] = c;
        //PrintArray(a, n);
    }
    return 0;
}