#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int InitArray(const char *fname, double *array, int n);
int PrintArray(double *array, int n);
int PrintMistakes(int n);
int GCD(int m, int n);
int Move(double *array, int n, int k, int j, int steps);
int Symetry(double *array, int n);//1
int Reverse(double *array, int n);//2
int SumArray(double *array, int n);//3
int DeleteBFromA(double *a, double *b, int n, int m);//4
int Merge(double *a, double *b, double *c, int n, int m);//5
int Cycle(double *array, int n, int k);//6, 7
int SequenceIn(const char *fname, double *a, int n);//8
int DeleteX(double *a, int n, double x);//9
int DeleteBFromAMove(double *a, double *b, int n, int m);//10
