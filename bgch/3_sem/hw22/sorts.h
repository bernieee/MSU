#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <typeinfo>
#include <iostream>
#include "student.h"


void printObjects(student *obj, int n);

int binSearch(student *obj, student &x, int n);//1
int merge(student *obj_a, student *obj_b, student *obj_c, int n, int m);//2
int findX(student *obj, student &x, int n);//3
void bubbleSort(student *obj, int n);//4
void minSort(student *obj, int n);//5
void insertSort1(student *obj, int n);//6 increase
void insertSort2(student *obj, int n);//6 decrease
void binSort(student *obj, int n);//7
void mergeSort(student *obj_a, student *obj_b, int n);//8
int min(int a, int b);//8
void mergeS(student *obj_a, student *obj_b, int left, int mid, int right);//8
void quickSort(student *obj, int n);//9
void heapSort(student *obj, int n);//10
