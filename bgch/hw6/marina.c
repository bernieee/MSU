#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (const char *name, double*a);
void init_array (double *a, int n);
void printf_array (double *a, int n);
int read_array (const char *name, double *a, int n);
int place (double *a,int n);

int place (double *array,int n)
{   double A;
    int gran, x0, xn, i, j;

    gran=(int)((x0+xn)/2);
    for (i=1;i<n;i++)
       {  
        x0=0;xn=i;
            while (x0<xn)
           { 
                
                gran=(int)((x0+xn)/2);

             if (array[i]>array[gran])
                {
                   x0=gran+1;
                }
             else
                {
                   if (array[i]<array[gran])
                      {
                        xn=gran;
                      }
                      else
                        {
                            x0=gran;
                            break;
                        }

                 }

            }
            A=array[i];
            for (j=i;j>x0;j--)
                 {
                  array[j]=array[j-1];
                 }
             array[x0]=A;
    }

    return 0;

}
int read_array (const char *name, double *array, int n)
{
    FILE *f;int i;double x;
    f=fopen(name,"r");
    if (!f)
    {
        return -1;
    }
    for (i=0;i<n;i++)
    {
        if (fscanf(f,"%lf",&x)==1)
                array[i]=x;
        else {
                fclose(f);return -2;
             }
    }

    fclose(f);
    return 0;
}

void printf_array (double *array,int n)
{
    int i;int k=0;
    for (i=0;i<n;i++)
    {   k++;
        printf ("%lf",array[i]);
        printf ("\n");
        if (k==20)
            break;
    }
}
void init_array (double *array, int n)
{
    int i;int k = n;
    for (i=0;i<n;i++)
    {   k--;
        array[i]=k;
    }
}
 int main (const char *name, double *array)
{ int n;
  scanf ("%d",&n);
  name = "1.txt";
  read_array (name,array,n);
  printf_array (array,n) ;
  place (array,n);
  printf ("\n");
  printf_array (array,n) ;
  return 0;
}