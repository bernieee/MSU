#include "hw6.h"


int InitArray(const char *fname, double *array, int n)
{
    FILE *f;
    int i = 0;
    double x;

    f = fopen(fname, "r");
    if (!f)
    {
        return -1;
    }
    if (!array)
    {
        fclose(f);
        return -2;
    }
    while((fscanf(f, "%lf", &x) == 1) && (i < n))
    {
        array[i] = x;
        i++;
    }
    if (i != n)
    {
        fclose(f);
        return -3;
    }
    fclose(f);
    return n;
}

int PrintArray(double *array, int n)
{
    int i;

    if (!array)
    {
        return -2;
    }

    for (i = 0 ; i < n ; i++)
        printf("%lf\n", array[i]);
    printf("\n");

    return 0;
}


int PrintMistakes(int n)
{
    if (n == -1)
        printf("No file\n");
    else if (n == -2)
        printf("No array\n");
    else if (n == -3)
        printf("Can not read an element\n");
    return n;
}

int BinSearch(double *a, int n, double x)//1
{
    int l = 0;
    int r = n;
    int m;
    while (l < r)
    {
        m = (l + r) / 2;
        if (a[m] < x)
            l = m + 1;
        else
            r = m;
    }
    return l;
}


int Merge(double *a, double *b, double *c, int n, int m)//2
{
    int i = 0;
    int j = 0;
    int k = 0;
    while ((i < n) && (j < m))
    {
        if (a[i] < b[j])
        {
            c[k] = a[i];
            i++;
        }
        else
        {
            c[k] = b[j];
            j++;
        }
        k++;
    }
    while (j < m)
    {
        c[k] = b[j];
        j++;
        k++;
    }
    while (i < n)
    {
        c[k] = a[i];
        i++;
        k++;
    }
    return n + m;
}


int FindX(double *a, int n, double x)//3
{
    int i = 0;
    int j = n - 1;
    double c;
    while (i <= j)
    {
        while ((a[i] < x))
        {
            i++;
        }
        while ((a[j] > x))
        {
            j--;
        }
        if (i <= j)
        {
            c = a[i];
            a[i] = a[j];
            a[j] = c;
            i++;
            j--;
        }
    }
    return i;
}

int BubbleSort(double *a, int n)//4
{
    int i;
    int j;
    int t = 1;
    double c;

    for (i = 0 ; i <= n ; i++)
    {
        t = 0;
        for (j = 0 ; j < n - i - 1 ; j++)
        {
            if (a[j] > a[j + 1])
            {
                c = a[j];
                a[j] = a[j + 1];
                a[j + 1] = c;
                t = 1;
            }
        }
        if (t == 0)
            return 0;
    }
    return 0;
}


int MinSort(double *a, int n)//5
{
    int i;
    int j;
    double c;
    int min;
    for (i = 0 ; i < n ; i++)
    {
        min = i;
        for (j = i + 1 ; j < n ; j++)
        {
            if (a[j] < a[min])
            {
                min = j;
            }
        }
        c = a[i];
        a[i] = a[min];
        a[min] = c;
    }
    return 0;
}

int InsertSort(double *a, int n)//6
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
            if (c < a[j])
                break;
        }
        for (k = i ; k > j ; k--)
        {
            a[k] = a[k - 1];
        }
        a[j] = c;
    }
    return 0;
}

int BinSort(double *a, int n)//7
{
    int i;
    int j;
    double c;
    int change;
    for (i = 1 ; i < n ; i++)
    {
        if (a[i] < a[i - 1])
        {
            change = BinSearch(a, i, a[i]);
            c = a[i];
            for (j = i ; j > change ; j--)//move
            {
                a[j] =a[j - 1];
            }
            a[change] = c;
        }
    }
    return 0;
}


int MergeSort(double *a, double *b, int n)//8
{
    int i;
    int j;
    for (i = 1 ; i < n ; i *= 2)
    {
        for (j = 0 ; j < n - i ; j += 2 * i)
        {
            MergeS(a, b, j, j + i, Min(j + 2 * i, n));
        }
    }
    return 0;
}

double Min(double a, double b)//8
{
    if (a < b)
        return a;
    else
        return b;
}

int MergeS(double *a, double *b, int l, int m, int r)//8
{
    int i = 0;
    int j = 0;
    int c;
    while ((l + i < m) && (m + j < r))
    {
        if (a[l + i] < a[m + j])
        {
            b[i + j] = a[l + i];
            i++;
        }
        else
        {
            b[i + j] = a[m + j];
            j++;
        }
    }
    while (l + i < m)
    {
        b[i + j] = a[l + i];
        i++;
    }
    while (m + j < r)
    {
        b[i + j] = a[m + j];
        j++;
    }
    for (c = 0 ; c < i + j ; c++)
    {
        a[l + c] = b[c];
    }
    return 0;
}


void QuickSort(double *a, int n)//9
{
    int i;
    double x = a[(n - 1) / 2];
    i = FindX(a, n, x);

    if (n <= 1)
    {
        return;
    }
    while (n > 1)
    {
        x = a[(n - 1) / 2];
        i = FindX(a, n, x);
        if (i == 0)
        {
            x = a[0];
            a[0] = a[(n - 1) / 2];
            a[(n - 1) / 2] = x;
            i = 1;
        }
        if (i < n - i)
        {
            QuickSort(a, i);
            a += i;
            n -= i;
        }
        else
        {
            QuickSort(a + i, n - i);
            n = i;
        }
    }
}

/*void QuickSort(double *a, int n) 
{
    int i;
    double x = a[(n - 1) / 2];
    i = FindX(a, n, x);

    if (i - 1 > 0)
    {
        QuickSort(a, i);
    }
    if (i < n)
    {
        QuickSort(a + i, n - i);
    }
}*/




int HeapSort(double *a, int n, int (*Sift) (double x, double y))//10
{
   int i;
   int k;
   int j = 0;
   int c;
   for (i = 1 ; i < n ; i++)
   {
       c = a[i];
       j = i;
       while ((j > 0) && (Sift(c, a[(j - 1) / 2]) > 0))
       {
           j = (j - 1) / 2;
       }
       k = i;
       while (k > j)
       {
           a[k] = a[(k - 1) / 2];
           k = (k - 1) / 2;
       }
       a[j] = c;
   }

   for (i = n - 1 ; i > 0 ; i--)
   {
       c = a[0];
       a[0] = a[i];
       a[i] = c;
       j = 0;
       while (j < i)
       {
           k = j;
           if ((2 * k + 1 < i) && (Sift(a[k], a[2 * k + 1]) < 0))
               j = 2 * k + 1;
           if ((2 * k + 2 < i) && (Sift(a[k], a[2 * k + 2]) < 0) && (Sift(a[2 * k + 2], a[2 * k + 1]) > 0))
               j = 2 * k + 2;
           if (j == k)
               break;
           c = a[k];
           a[k] = a[j];
           a[j] = c;
       }
   }
   return 0;
}
