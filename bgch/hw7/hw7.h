#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


int SiftUp(double x, double y);
int SiftDown(double x, double y);
int InitArray(const char *fname, double *array, int n);
int PrintArray(double *array, int n);
int PrintMistakes(int n);
int BinSearch(double *a, int n, double x, int (*Sift) (double x, double y));//1
int Merge(double *a, double *b, double *c, int n, int m);//2
int FindX(double *a, int n, double x, int (*Sift) (double x, double y));//3
int BubbleSort(double *a, int n, int (*Sift) (double x, double y));//4
int MinSort(double *a, int n, int (*Sift) (double x, double y));//5
int InsertSort(double *a, int n, int (*Sift) (double x, double y));//6
int BinSort(double *a, int n, int (*Sift) (double x, double y));//7
int MergeSort(double *a, double *b, int n, int (*Sift) (double x, double y));//8
double Min(double a, double b);//8
int MergeS(double *a, double *b, int l, int m, int r, int (*Sift) (double x, double y));//8
void QuickSort(double *a, int n, int (*Sift) (double x, double y));//9
int HeapSort(double *a, int n, int (*Sift) (double x, double y));//10


int SiftUp(double x, double y)
{
    if (x > y)
        return 1;
    else if (x < y)
        return -1;
    else
        return 0;
}


int SiftDown(double x, double y)
{
    if (x < y)
        return 1;
    else if (x > y)
        return -1;
    else
        return 0;
}


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


int BinSearch(double *a, int n, double x, int (*Sift) (double x, double y))//1
{
    int l = 0;
    int r = n;
    int m;
    while (l < r)
    {
        m = (l + r) / 2;
        if ((*Sift)(a[m], x) > 0)
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


int FindX(double *a, int n, double x, int (*Sift) (double x, double y))//3
{
    int i = 0;
    int j = n - 1;
    double c;
    while (i <= j)
    {
        while ((i < n) && ((*Sift)(a[i], x) < 0))
        {
            i++;
        }
        while ((j >= 0) && ((*Sift)(a[j], x) >= 0))
        {
            j--;
        }
        if (i < j)
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


int BubbleSort(double *a, int n, int (*Sift) (double x, double y))//4
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
            if ((*Sift)(a[j], a[j + 1]) > 0)
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


int MinSort(double *a, int n, int (*Sift) (double x, double y))//5
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
            if ((*Sift)(a[j], a[min]) < 0)
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
        for (k = i ; k > j ; k--)
        {
            a[k] = a[k - 1];
        }
        a[j] = c;
    }
    return 0;
}


int BinSort(double *a, int n, int (*Sift) (double x, double y))//7
{
    int i;
    int j;
    double c;
    int change;
    for (i = 1 ; i < n ; i++)
    {
        if ((*Sift)(a[i], a[i - 1]) < 0)
        {
            change = BinSearch(a, i, a[i], Sift);
            c = a[i];
            for (j = i ; j > change ; j--)//move
            {
                a[j] = a[j - 1];
            }
            a[change] = c;
        }
    }
    return 0;
}


/*int MergeSort(double *a, double *b, int n, int (*Sift) (double x, double y))//8
{
    int i;
    int j;
    for (i = 1 ; i < n ; i *= 2)
    {
        for (j = 0 ; j < n - i ; j += 2 * i)
        {
            MergeS(a, b, j, j + i, Min(j + 2 * i, n), Sift);
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


int MergeS(double *a, double *b, int l, int m, int r, int (*Sift) (double x, double y))//8
{
    int i = 0;
    int j = 0;
    int c;
    double *tmp;

    while ((l + i < m) && (m + j < r))
    {
        if ((*Sift)(a[l + i], a[m + j]) < 0)
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
    
    //tmp = (a + l);
    //tmp = b;
    //*b = tmp;
    for (c = 0 ; c < i + j ; c++)
    {
        a[l + c] = b[c];
    }
    return 0;
}*/


int MergeSort(double *a, double *b, int n, int (*Sift) (double x, double y))//8

{
double *A; double *buf;
A=a;
int shag = 1; // шаг разбиения последовательности
//double *b = (int*)malloc(n * sizeof(b)); // дополнительный массив
while (shag < n) // пока шаг меньше длины массива
{
int j= 0; // индекс результирующего массива
int left = 0; // левая граница участка
int seredina = left + shag; // середина участка
int right = left + shag * 2; // правая граница участка
while (left <=n)
{
if (seredina>=n)
seredina=n;

if (right>=n)
right=n;

int i1 = left, i2 = seredina; // индексы сравниваемых элементов

for (; i1 < seredina && i2 < right; ) // пока i1 не дошёл до середины и i2 не дошёл до конца
{
if (a[i1] < a[i2]) { b[j++] = a[i1++]; } // заполняем участок результирующей последовательности
else { b[j++] = a[i2++]; }
}
// Или i1 < m или i2 < r - только один из операторов while может выполниться


while (i1 < seredina)
{
b[j] = a[i1];
j++;i1++;
}// заносим оставшиеся элементы сортируемых участков


while (i2 < right)
{
b[j] = a[i2];
j++;i2++;
} // в результирующий массив


left = left+shag * 2; // перемещаемся на следующий сортируемый участок
seredina = seredina + shag * 2;
right = right + shag * 2;
}
buf=a;
a=b;
b=buf;
shag = shag*2; // увеличиваем в 2 раза шаг разбиения
}
if (A!=a)
for (int i = 0; i < n; i++)
{
a[i] = b[i];
}
return 0;
}


void QuickSort(double *a, int n, int (*Sift) (double x, double y))//9
{
    int i;
    double x = a[(n - 1) / 2];
    i = FindX(a, n, x, Sift);

    if (n <= 1)
    {
        return;
    }
    while (n > 1)
    {
        x = a[(n - 1) / 2];
        i = FindX(a, n, x, Sift);
        if (i == 0)
        {
            x = a[0];
            a[0] = a[(n - 1) / 2];
            a[(n - 1) / 2] = x;
            i = 1;
        }
        if (i < n - i)
        {
            QuickSort(a, i, Sift);
            a += i;
            n -= i;
        }
        else
        {
            QuickSort(a + i, n - i, Sift);
            n = i;
        }
    }
}


/*void QuickSort(double *a, int n, int (*Sift) (double x, double y))//9
{
    int i;
    double x = a[(n - 1) / 2];
    i = FindX(a, n, x, Sift);

    if (i - 1 > 0)
    {
        QuickSort(a, i, Sift);
    }
    if (i < n)
    {
        QuickSort(a + i, n - i, Sift);
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
