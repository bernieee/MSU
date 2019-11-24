 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (int argc, char *argv[]);
void init_array (double *array, int n);
void printf_array (double *array, int n);
int read_array (const char *name, double *array, int n);
void QuickSort(double *array,int n);
int PoiskMestaX (double *array, int n,double x);

void QuickSort(double *array,int n)

{
    int k;
   double  x = array [(int)n/2];
    k=PoiskMestaX (array,n,x);
    if (n <=1)
       {
        return;
       }
     while (n>1)
     {
          x = array [(int)n/2];
          k=PoiskMestaX (array,n,x);
          if (k==0)
         {
             x=array[0];
             array[0]=array[(int)n/2];
             array[(int)n/2]=x;
             k=1;
         }
         if (k < n - k)
         {
             QuickSort (array,k);
             array = array + k;
             n = n - k;
         }
         else
         {
             QuickSort (array+k,n-k);
             n=k;

         }
     }
}

  int PoiskMestaX (double *array, int n, double x)

  {
      int i ,j;  double A; 
    
     j= n - 1; i=0;
    
while(i <= j) 
{ 
   while((i < n) && (array[i] < x)) 
{ 
       i++; 
} 
   while((j >= 0) && (array[j] >=x)) 
{ 
        j--; 
} 
    if(i < j) 
{ 
A = array[i]; 
array[i] = array[j]; 
array[j] = A; 
i++; 
j--; 
} 
} 
return i; 
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

  int main (int argc, char* argv[])
  { double *array;double t;
    int n;
    char *name = 0;int res;
    if (!(((argc==2)||(argc==3))&&(sscanf(argv[1],"%d",&n)==1)))
    {
        printf ("Usage %s\n",argv[0]); return 2;
    }
    if (n<1) {printf ("Incorrect size\n"); return 3;}
    array = (double*)malloc(n*sizeof(double)) ;
    if (!array)
    {printf ("Not enough memory!\n");return 2;}
    if (argc==3)
        {
            name = argv [2];
        }
    if (name)
    {
        res=read_array (name,array, n);
          if (res<0)
        {
          switch(res)
             { case -1 :
                 printf ("Cannot open file %s\n",name);
                break;
               case -2 :
                printf ("Cannot read file %s\n",name);
                break;
               default :
                printf ("Unknown error \n");
                break;
             }
        free(array); return 1;
        }
     }
     else
           {
            init_array (array,n);
            }
     printf_array (array,n);
     t=clock();
     QuickSort(array,n);
     t=(clock()-t)/(CLOCKS_PER_SEC);
     printf ("\n");
     printf_array (array,n);
     printf ("\n");
     printf ("Elapsed %.2f\n",t);
     free(array);
     return 0;
    }