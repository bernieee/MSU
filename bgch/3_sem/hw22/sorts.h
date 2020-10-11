#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "student.h"

int siftUp(student x, student y);
int siftDown(student x, student y);

void printObjects(student *obj, int n);

int binSearch(student *obj, student x, int n, int (*Sift) (student x, student y));//1
int merge(student *obj_a, student *obj_b, student *obj_c, int n, int m);//2
int findX(student *obj, student x, int n, int (*Sift) (student x, student y));//3
void bubbleSort(student *obj, int n, int (*Sift) (student x, student y));//4
void minSort(student *obj, int n, int (*Sift) (student x, student y));//5
void insertSort(student *obj, int n, int (*Sift) (student x, student y));//6
void binSort(student *obj, int n, int (*Sift) (student x, student y));//7
void mergeSort(student *obj_a, student *obj_b, int n, int (*Sift) (student x, student y));//8
int min(int a, int b);//8
void mergeS(student *obj_a, student *obj_b, int left, int mid, int right, int (*Sift) (student x, student y));//8
void quickSort(student *obj, int n, int (*Sift) (student x, student y));//9
void heapSort(student *obj, int n, int (*Sift) (student x, student y));//10
