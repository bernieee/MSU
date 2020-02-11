#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


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
int MergeS(double *a, double *b, int l, int m, int r);//8
void QuickSort(double *a, int n);//9
int HeapSort(double *a, int n);//10
