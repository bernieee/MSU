#include "sorts.h"
#include "student.h"


void printObjects(student *obj, int n)
{
    for (int i = 0; i < n; i++)
    {
        obj[i].print();
    }

    printf("\n");
}


int binSearch(student *obj, student &x, int n)//1
{
    int left;
    int right;
    int mid;

    left = 0;
    right = n;

    while (left < right)
    {
        mid = (left + right) / 2;

        if (obj[mid] < x)
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


int findX(student *obj, student &x, int n)//3
{
    int i;
    int j;

    i = 0;
    j = n - 1;

    while (i < j)
    {
        while ((i < n) && (obj[i] < x))
        {
            i++;
        }

        while ((j > 0) && ((obj[j] < x) != 1))
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


void bubbleSort(student *obj, int n)//4
{
    int flag;

    for (int i = 0; i <= n; i++)
    {
        flag = 0;

        for (int j = 0; j < n - i - 1; j++)
        {
            if (obj[j] > obj[j + 1])
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


void minSort(student *obj, int n)//5
{
    int min;

    for (int i = 0; i < n; i++)
    {
        min = i;

        for (int j = i + 1; j < n; j++)
        {
            if (obj[j] < obj[min])
            {
                min = j;
            }
        }

        obj[i].swap(obj[min]);
    }
}



void insertSort1(student *obj, int n)//6 increase
{
    int j;
    student tmp_obj;

    for (int i = 1; i < n; i++)
    {
        tmp_obj.swap(obj[i]);

        for (j = i - 1; j >= 0; j--)
        {
            if (tmp_obj > obj[j])
                break;

            obj[j + 1].swap(obj[j]);
        }

        obj[j + 1].swap(tmp_obj);
    }
}


void insertSort2(student *obj, int n)//6 decrease
{
    int j;
    student tmp_obj;

    for (int i = 1; i < n; i++)
    {
        tmp_obj.swap(obj[i]);

        for (j = 0; j < i; j++)
        {
            if (tmp_obj < obj[j])
                break;
        }

        for (int k = i; k > j; k--)
        {
            obj[k].swap(obj[k - 1]);
        }

        obj[j].swap(tmp_obj);
    }
}



void binSort(student *obj, int n)//7
{
    int change;
    student tmp_obj;

    for (int i = 1; i < n; i++)
    {
        if (obj[i] < obj[i - 1])
        {
            change = binSearch(obj, obj[i], i);
            tmp_obj.swap(obj[i]);

            for (int j = i; j > change; j--)//move
            {
                obj[j].swap(obj[j - 1]);
            }

            obj[change].swap(tmp_obj);
        }
    }
}


void mergeSort(student *obj_a, student *obj_b, int n)//8
{
    for (int i = 1; i < n; i *= 2)
    {
        for (int j = 0; j < n - i; j += 2 * i)
        {
            mergeS(obj_a, obj_b, j, j + i, min(j + 2 * i, n));
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


void mergeS(student *obj_a, student *obj_b, int left, int mid, int right)//8
{
    int i = 0;
    int j = 0;

    while ((left + i < mid) && (mid + j < right))
    {
        if (obj_a[left + i] < obj_a[mid + j])
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


void quickSort(student *obj, int n)//9
{
    int i;

    if (n <= 1)
    {
        return;
    }

    while (n > 1)
    {
        i = findX(obj, obj[(n - 1) / 2], n);

        if (i == 0)
        {
            obj[0].swap(obj[(n - 1) / 2]);
            i = 1;
        }

        if (i < n - i)
        {
            quickSort(obj, i);
            obj += i;
            n -= i;
        }

        else
        {
            quickSort(obj + i, n - i);
            n = i;
        }
    }
}


void heapSort(student *obj, int n)//10
{
   int k;
   int j;
   student tmp_obj;

   for (int i = 1; i < n; i++)
   {
       tmp_obj.swap(obj[i]);
       j = i;

       while ((j > 0) && (tmp_obj > obj[(j - 1) / 2]))
       {
           j = (j - 1) / 2;
       }

       k = i;

       while (k > j)
       {
           obj[k].swap(obj[(k - 1) / 2]);
           k = (k - 1) / 2;
       }

       obj[j].swap(tmp_obj);
   }

   for (int i = n - 1; i > 0; i--)
   {
       obj[0].swap(obj[i]);
       j = 0;

       while (j < i)
       {
           k = j;

           if ((2 * k + 1 < i) && (obj[k] < obj[2 * k + 1]))
           {
               j = 2 * k + 1;
           }

           if ((2 * k + 2 < i) && (obj[k] < obj[2 * k + 2]) && (obj[2 * k + 2] > obj[2 * k + 1]))
           {
               j = 2 * k + 2;
           }

           if (j == k)
               break;

           obj[k].swap(obj[j]);
       }
   }
}
