#include "hw5.h"


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
        printf("%lf ", array[i]);
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

int Symetry(double *array, int n)//1
{
    int i;
    double eps = 1e-7;

    for (i = 0 ; i < n / 2 ; i++)
    {
        if (fabs(array[i] - array[n - i - 1]) > eps)
        {
            return 0;
        }
    }

    return 1;
}

int Reverse(double *array, int n)//2
{
    double c;
    int i;
    for (i = 0 ; i < n / 2 ; i++)
    {
        c = array[i];
        array[i] = array[n - i - 1];
        array[n - i - 1] = c;;

    }

    return 1;
}


int SumArray(double *array, int n)//3
{
    int i;
    double c = array[0];

    for (i = 2 ; i < n ; i++)
    {
        array[i - 1] += (c + array[i]);
        c = array[i - 1] - c - array[i];
        array[i - 1] -= c;
    }
    return 0;
}


int DeleteBFromA(double *a, double *b, int n, int m)//4
{
    int i;
    int j;
    double eps = 1e-7;
    for (i = 0 ; i < n ; i++)
    {
        for (j = 0 ; j < m ; j++)
        {
            if (fabs(a[i] - b[j]) < eps)
            {
                a[i] = 0;
                break;
            }
        }
    }
    return 0;
}

int Merge(double *a, double *b, double *c, int n, int m)//5
{
    int i = 0;
    int j = 0;
    int k = 0;
    while ((i < n) || (j < m))
    {
        if (i >= n)
        {
            c[k] = b[j];
            j++;
        }
        else if (j >= m)
        {
            c[k] = a[i];
            i++;
        }
        else if (a[i] < b[j])
        {
            c[k] = a[i];
            i++;
        }
        else if (a[i] > b[j])
        {
            c[k] = b[j];
            j++;
        }
        else
        {
            i++;
        }
        k++;
    }
    return n + m;
}


int Cycle(double *array, int n, int k)//6, 7
{
    int i = 0;
    int f;
    int steps;
    k = (k % n);
    f = GCD(n, abs(k));

    if (f == 1)
    {
        if (k >= 0)
            Move(array, n, k, 0, n);
        else
            Move(array, n, k, n - 1, n);
    }
    else
    {
        steps = n / f;
        while (i < f)
        {
            if (k >= 0) 
                Move(array, n, k, i, steps);
            else
                Move(array, n, k, n - i - 1, steps);
            i++;
        }
    }
    return 0;
}

int Move(double *array, int n, int k, int j, int steps)
{
    int i;
    int rem1 = array[j];
    int rem2;
    for (i = 0 ; i < steps ; i++)
    {
        j = (j + k) % n;
        if (j < 0)
            j = n + j;
        rem2 = array[j];
        array[j] = rem1;
        rem1 = rem2;
    }
    return 0;
}

int GCD(int m, int n)
{
    while (m > 0)
    {
        n %= m;
        n += m;
        m = n - m;
        n -= m;
    }
    return n;
}


int SequenceIn(const char *fname, double *a, int n)//8???str
{
    FILE *f;
    int i = 0;
    int j = 0;
    int num = 0;
    double x;
    double eps = 1e-7;

    f = fopen(fname, "r");
    if (!f)
    {
        return -1;
    }
    if (n == 0)
    {
        fclose(f);
        return num;
    }

    if (fscanf(f, "%lf", &x))
    {
        if (fabs(a[i] - x) < eps)
        {
            i++;
        }
    }
    else
    {
        fclose(f);
        return -3;
    }
    if (i == n)
    {
         num++;
         i = 0;
    }
    while (fscanf(f, "%lf", &x) == 1)
    {
        if (fabs(a[i] - x) < eps)
        {
            i++;
            if (fabs(a[i - 1] - x) < eps)
            {
                j++;
            }
            else
            {
                j = 0;
            }
        }
        else
        {
            i = 0;
        }
        if (i == n)
        {
            num++;
            i = 0;
        }
        if (j == n)
        {
            num++;
            j = 0;
        }
    }
    fclose(f);
    return num;
}


int DeleteX(double *a, int n, double x)//9
{
    int i;
    int k = 0;
    for (i = 0 ; i < n ; i++)
    {
        if (a[i] < x)
        {
            k++;
        }
        else
        {
            a[i - k] = a[i];
        }
    }
    return n - k;
}


int DeleteBFromAMove(double *a, double *b, int n, int m)//10
{
    int i;
    int j;
    int k = 0;
    int flag = 0;
    double eps = 1e-7;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            if (fabs(a[i] - b[j]) < eps)
            {
                k++;
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            a[i - k] = a[i];
        }
        flag = 0;
    }

    return n - k;
}
