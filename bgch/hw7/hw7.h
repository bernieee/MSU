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
