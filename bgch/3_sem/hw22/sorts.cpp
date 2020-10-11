#include "sorts.h"
#include "student.h"


int siftUp(student x, student y)
{
    if (x > y)
        return 1;
    else if (x < y)
        return -1;
    else
        return 0;
}


int siftDown(student x, student y)
{
    if (x < y)
        return 1;
    else if (x > y)
        return -1;
    else
        return 0;
}


void printObjects(student *obj, int n)
{
    for (int i = 0; i < n; i++)
    {
        obj[i].print();
    }

    printf("\n");
}


int binSearch(student *obj, student x, int n, int (*Sift) (student x, student y))//1
{
    int left;
    int right;
    int mid;

    left = 0;
    right = n;

    while (left < right)
    {
        mid = (left + right) / 2;

        if ((*Sift)(obj[mid], x) < 0)
        {
            left = mid + 1;
        }
        else
        {
            right = mid;
        }
    }
    return left;
}


int merge(student *obj_a, student *obj_b, student *obj_c, int n, int m)//2
{
    int i;
    int j;
    int k;

    i = j = k = 0;

    while ((i < n) && (j < m))
    {
        if (obj_a[i] < obj_b[j])
        {
            obj_c[k].swap(obj_a[i]);
            i++;
        }
        else
        {
            obj_c[k].swap(obj_b[j]);
            j++;
        }
        k++;
    }

    while (j < m)
    {
        obj_c[k].swap(obj_b[j]);
        j++;
        k++;
    }

    while (i < n)
    {
        obj_c[k].swap(obj_a[i]);
        i++;
        k++;
    }

    return n + m;
}


int findX(student *obj, student x, int n, int (*Sift) (student x, student y))//3
{
    int i;
    int j;

    i = 0;
    j = n - 1;

    while (i < j)
    {
        while ((i < n) && ((*Sift)(obj[i], x) < 0))
        {
            i++;
        }

        while ((j > 0) && ((*Sift)(obj[j], x) >= 0))
        {
            j--;
        }

        if (i < j)
        {
            obj[i].swap(obj[j]);
            i++;
            j--;
        }
        else
        {
            return i;
        }
    }

    return n;
}


void bubbleSort(student *obj, int n, int (*Sift) (student x, student y))//4
{
    int flag;

    for (int i = 0; i <= n; i++)
    {
        flag = 0;

        for (int j = 0; j < n - i - 1; j++)
        {
            if ((*Sift)(obj[j], obj[j + 1]) > 0)
            {
                obj[j].swap(obj[j + 1]);
                flag = 1;
            }
        }

        if (flag == 0)
        {
            return;
        }
    }
}


void minSort(student *obj, int n, int (*Sift) (student x, student y))//5
{
    int min;

    for (int i = 0; i < n; i++)
    {
        min = i;

        for (int j = i + 1; j < n; j++)
        {
            if ((*Sift)(obj[j], obj[min]) < 0)
            {
                min = j;
            }
        }

        obj[i].swap(obj[min]);
    }
}



void insertSort(student *obj, int n, int (*Sift) (student x, student y))//6
{
    int j;
    student tmp_obj;

    for (int i = 1; i < n; i++)
    {
        tmp_obj = obj[i];

        for (j = 0; j < i; j++)
        {
            if ((*Sift)(tmp_obj, obj[j]) < 0)
                break;
        }

        for (int k = i; k > j; k--)
        {
            obj[k] = obj[k - 1];
        }

        obj[j] = tmp_obj;
    }
}


void binSort(student *obj, int n, int (*Sift) (student x, student y))//7
{
    int change;
    student tmp_obj;

    for (int i = 1; i < n; i++)
    {
        if ((*Sift)(obj[i], obj[i - 1]) < 0)
        {
            change = binSearch(obj, obj[i], i, Sift);
            tmp_obj = obj[i];

            for (int j = i; j > change; j--)//move
            {
                obj[j] = obj[j - 1];
            }

            obj[change] = tmp_obj;
        }
    }
}


void mergeSort(student *obj_a, student *obj_b, int n, int (*Sift) (student x, student y))//8
{
    for (int i = 1; i < n; i *= 2)
    {
        for (int j = 0; j < n - i; j += 2 * i)
        {
            mergeS(obj_a, obj_b, j, j + i, min(j + 2 * i, n), Sift);
        }
    }
}


int min(int a, int b)//8
{
    if (a < b)
        return a;
    else
        return b;
}


void mergeS(student *obj_a, student *obj_b, int left, int mid, int right, int (*Sift) (student x, student y))//8
{
    int i = 0;
    int j = 0;

    while ((left + i < mid) && (mid + j < right))
    {
        if ((*Sift)(obj_a[left + i], obj_a[mid + j]) < 0)
        {
            obj_b[i + j].swap(obj_a[left + i]);
            i++;
        }
        else
        {
            obj_b[i + j].swap(obj_a[mid + j]);
            j++;
        }
    }

    while (left + i < mid)
    {
        obj_b[i + j].swap(obj_a[left + i]);
        i++;
    }

    while (mid + j < right)
    {
        obj_b[i + j].swap(obj_a[mid + j]);
        j++;
    }

    for (int c = 0; c < i + j; c++)
    {
        obj_a[left + c].swap(obj_b[c]);
    }
}


void quickSort(student *obj, int n, int (*Sift) (student x, student y))//9
{
    int i;
    student x;

    if (n <= 1)
    {
        return;
    }

    while (n > 1)
    {
        x = obj[(n - 1) / 2];
        i = findX(obj, x, n, Sift);

        if (i == 0)
        {
            obj[0].swap(obj[(n - 1) / 2]);
            i = 1;
        }

        if (i < n - i)
        {
            quickSort(obj, i, Sift);
            obj += i;
            n -= i;
        }

        else
        {
            quickSort(obj + i, n - i, Sift);
            n = i;
        }
    }
}



void heapSort(student *obj, int n, int (*Sift) (student x, student y))//10
{
   int k;
   int j;
   student tmp_obj;

   for (int i = 1; i < n; i++)
   {
       tmp_obj = obj[i];
       j = i;

       while ((j > 0) && (Sift(tmp_obj, obj[(j - 1) / 2]) > 0))
       {
           j = (j - 1) / 2;
       }

       k = i;

       while (k > j)
       {
           obj[k] = obj[(k - 1) / 2];
           k = (k - 1) / 2;
       }

       obj[j] = tmp_obj;
   }

   for (int i = n - 1; i > 0; i--)
   {
       obj[0].swap(obj[i]);
       j = 0;

       while (j < i)
       {
           k = j;

           if ((2 * k + 1 < i) && (Sift(obj[k], obj[2 * k + 1]) < 0))
           {
               j = 2 * k + 1;
           }

           if ((2 * k + 2 < i) && (Sift(obj[k], obj[2 * k + 2]) < 0) && (Sift(obj[2 * k + 2], obj[2 * k + 1]) > 0))
           {
               j = 2 * k + 2;
           }

           if (j == k)
               break;

           obj[k].swap(obj[j]);
       }
   }
}
