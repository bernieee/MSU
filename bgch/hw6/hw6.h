#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int InitArray(const char *fname, double *array, int n);
int PrintArray(double *array, int n);
int PrintMistakes(int n);
int BinSearch(double *a, int n, double x);//1
int Merge(double *a, double *b, double *c, int n, int m);//2
int FindX(double *a, int n, double x);//3
int BubbleSort(double *a, int n);//4
int MinSort(double *a, int n);//5
int InsertSort(double *a, int n);//6
int BinSort(double *a, int n);//7
int MergeSort(double *a, double *b, int n);//8
double Min(double a, double b);//8
int MergeS(double *a, double *b, int n, int l, int m, int r);//8
void QuickSort(double *a, int n);//9
int Part(double *a, int n);//9
int Sink(double *a, int l, int r);//10
int BuildHeap(double *a, int n);//10
int HeapSort(double *a, int n);//10

int InitArray(const char *fname, double *array, int n)
{
    FILE *f;
    int i = 0;
    double x;
    //array = (double*) malloc(n * sizeof(double));

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


/*int FindX(double *a, int n, double x)//3
{
    int i = 0;
    int j = n - 1;
    double c;
    double eps = 1e-7;
    while (i <= j)
    {
        for (i = 0 ; i < n ; i++)
        {
            if ((a[i] > x))// || (fabs(a[i] - x) < eps))
                break;
        }
        printf("%d\n", i);
        for (j = n - 1 ; j > 0 ; j--)
        {
            if ((a[j] < x))// || (fabs(a[j] - x) < eps))
                break;
        }
        printf("%d\n", j);
        if ((i == 0) && (j == 0))
        {
             j = n - 2;
        }
        if ((i == n - 1) && (j == n - 1))
        {
            i = 1;
        }
        if (i <= j)
        {
            //if (a[i] > a[j])
            //{
            c = a[i];
            a[i] = a[j];
            a[j] = c;
            //}
            i++;
            j--;
        }
    }
    return i;
}*/


int FindX(double *a, int n, double x)//3
{
    int i = 0;
    int j = n - 1;
    double c;
    double eps = 1e-7;
    while (i <= j)
    {
        while ((a[i] < x))
        {
            i++;
        }
        //printf("%d\n", i);
        while ((a[j] > x))
        {
            j--;
        }
        //printf("%d\n", j);
        if (i < j)
        {
            c = a[i];
            a[i] = a[j];
            a[j] = c;
            i++;
            j--;
        }
    }
    return j;
}

int BubbleSort(double *a, int n)//4
{
    int i;
    int j;
    double c;
    for (i = 0 ; i <= n ; i++)
        for (j = 0 ; j < n - i - 1 ; j++)
        {
            if (a[j] > a[j + 1])
            {
                c = a[j];
                a[j] = a[j + 1];
                a[j + 1] = c;
            }
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
    double c;
    for (i = 1 ; i < n ; i++)
    {
        j = i - 1;
        while ((j >= 0) && (a[j] > a[j + 1]))
        {
            c = a[j];
            a[j] = a[j + 1];
            a[j + 1] = c;
            j--;
        }
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
            MergeS(a, b, n, j, j + i, Min(j + 2 * i, n));
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

int MergeS(double *a, double *b, int n, int l, int m, int r)//8
{
    int i = 0;
    int j = 0;
    //int k = 0;
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
    int m;
    double x;
    int k = n / 2;
    //x = a[k];
    //printf("%d\n", n);
    if (n <= 1)
        return;
    while (n > 1)
    {
        x = a[k];
        m = FindX(a, n, x) - 1;
        //printf("%d %d %lf\n", n, m, x);
        if (m <= n - m)
        {
            QuickSort(a, m);
            a += m;
            n -= m;
            //printf("1\n");
        }
        else
        {
            QuickSort(a + m, n - m);
            n -= m;
            //printf("2\n");
        }
    }
    return;
}

int Part(double *a, int n)//9
{
    double x = a[n / 2];
    int i = 0;
    int j = n - 1;
    double c;
    double eps = 1e-7;
    while (i <= j)
    {
        while (a[i] < x)
        {
            i++;
        }
        while ((a[j] > x) || (fabs(a[j] - x) < eps))
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

int Sink(double *a, int l, int r)//10
{
   int big_index;
   int childl;
   int childr;
   int c;
   while(l < r) 
   {
     big_index = l;
     childl = 2 * l + 1;
     childr = childl + 1;
     if ((childl < r) && (a[childl] > a[big_index]))
     {
         big_index = childl;
     }
     if ((childr < r) && (a[childr] > a[big_index]))
     {
         big_index = childr;
     }
     if (big_index == l) 
         return 0;
      c = a[l];
      a[l] = a[big_index];
      a[big_index] = c;

      l = big_index;
   }
   return 0;
}

int BuildHeap(double *a, int n)//10
{
   int index = n / 2 - 1;
   while ( index >= 0 )
   {
       Sink(a, n, index);
       index --;
   }
   return 0;
}


int HeapSort(double *a, int n)//10
{
   int i;
   int c;
   BuildHeap(a, n);
   for (i = n - 1 ; i >= 0 ; i--)
   {
       c = a[0];
       a[0] = a[i];
       a[i] = c;
       Sink(a, 0, i);
   }
   return 0;
}
