#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#define LEN 1234


int SiftUp(char *x, char *y);
int SiftDown(char *x, char *y);
int InitArray(const char *fname, char **array, int n);
int PrintArray(char **array, int n);
int PrintMistakes(int n);
int BinSearch(char **a, int n, char *x, int (*Sift) (char *x, char *y));//1
int Merge(char **a, char **b, char **c, int n, int m);//2
int FindX(char **a, int n, char *x, int (*Sift) (char *x, char *y));//3
int BubbleSort(char **a, int n, int (*Sift) (char *x, char *y));//4
int MinSort(char **a, int n, int (*Sift) (char *x, char *y));//5
int InsertSort(char **a, int n, int (*Sift) (char *x, char *y));//6
int BinSort(char **a, int n, int (*Sift) (char *x, char *y));//7
int MergeSort(char **a, char **b, int n, int (*Sift) (char *x, char *y));//8
int Min(int a, int b);//8
int MergeS(char **a, char **b, int l, int m, int r, int (*Sift) (char *x, char *y));//8
void QuickSort(char **a, int n, int (*Sift) (char *x, char *y));//9
int HeapSort(char **a, int n, int (*Sift) (char *x, char *y));//10
