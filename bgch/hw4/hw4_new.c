#include<stdio.h>
#include<math.h>

int StandartDeviation(const char *fname, double *d);//1 13
int SequenceWhat(const char *fname);//2 47
int ElemIsXFirst(const char *fname, double x);//3 129
int ElemIsXLast(const char *fname, double x);//4 165
int MaxElem(const char *fname, double *x);//5 201
int MaxNum(const char *fname, double *x);//6 251
int FirstLastMax(const char *fname, double *x, int *i, int *j);//7 302
int FirstLastElemIsX(const char *fname, double x, int *i, int *j);//8 360

int StandartDeviation(const char *fname, double *d)//1
{
    FILE *f;
    int n = 0;
    double x;
    double sum_q = 0;
    double sum = 0;

    f = fopen(fname, "r");
    if (f == NULL)
    {
       // fclose(f);
        return -1;
    }

    while (fscanf(f, "%lf", &x) == 1)
    {
        n++;
        sum_q += (x * x);
        sum += x;
    }
    if (n != 0)
    {
         *d = (sum_q - sum * sum / n) / n;
    }

    if (feof(f) == 0)
    {
        fclose(f);
        return -2;
    }
    fclose(f);
    return n;
}


int SequenceWhat(const char *fname)//2
{
    FILE *f;
    double d = 0;
    double q =0;
    int arif = 0;
    int geom = 0;
    int len = 0;
    double x0;
    double x1;
    double x2;
    double eps = 1e-7;


    f = fopen(fname, "r");
    if (f == NULL)
    {
        //fclose(f);
        return -1;
    }

    if (fscanf(f, "%lf", &x0) == 1)
    {
        len++;
    }
    else
    {
        fclose(f);
        return 4;
    }

    if (fscanf(f, "%lf", &x1) == 1)
    {
        len++;
    }
    else
    {
        fclose(f);
        return 4;
    }

    d = x1 - x0;
    if ((x0 < eps) && (x0 > -eps))
    {
        q = x1 / x0;
    }
    else
    {
        fclose(f);
        return 0;
    }

    if ((q < eps) && (q > -eps))
    {
        fclose(f);
        return 0;
    }
    if ((d < eps) && (d > -eps))
    {
        fclose(f);
        return 0;
    }

    while (fscanf(f,"%lf",&x2)==1)
    {
        if (fabs(x1) < eps)
        {
            fclose(f);
            return 0;
        }
        else if (fabs(x2 - x1 - d) < eps)
        {
            arif = 1;
        }
        else if (fabs(x2 / x1 - q) < eps)
        {
            geom = 1;
        }
        x0 = x1;
        x1 = x2;
        len++;
    }

    if (feof(f) == 0)
    {
        fclose(f);
        return -2;
    }

    fclose(f);

    if ((arif > 0) && (geom > 0))
        return 0;
    else if (arif > 0)
        return 1;
    else if (geom > 0)
        return 2;
    else
        return 3;
}


int ElemIsXFirst(const char *fname, double x)//3
{
    FILE *f;
    double eps = 1e-7;
    int n = 0;
    double x0;

    f = fopen(fname, "r");
    if (f == NULL)
    {
        //fclose(f);
        return -1;
    }

    while (fscanf(f, "%lf", &x0) == 1)
    {
        n++;
        if (fabs(x - x0) < eps)
        {
            fclose(f);
            return n;
        }
    }

    if (feof(f) == 0)
    {
        fclose(f);
        return -2;
    }

    fclose(f);

    return 0;
}


int ElemIsXLast(const char *fname, double x)//4
{
    FILE *f;
    double eps = 1e-7;
    int n = 0;
    int num = 0;
    double x0;

    f = fopen(fname, "r");
    if (f == NULL)
    {
        //fclose(f);
        return -1;
    }

    while (fscanf(f, "%lf", &x0) == 1)
    {
        n++;
        if (fabs(x - x0) < eps)
        {
            num = n;
        }
    }

    if (feof(f) == 0)
    {
        fclose(f);
        return -2;
    }

    fclose(f);

    return num;
}


int MaxElem(const char *fname, double *x)//5
{
    FILE *f;
    int n = 0;
    int num = 0;
    double x0;
    double max;

    f = fopen(fname, "r");
    if (f == NULL)
    {
        //fclose(f);
        return -1;
    }

    if (fscanf(f, "%lf", &max) == 1)
    {
        n++;
        num = n;
    }
    else
    {
        fclose(f);
        return -3;
    }

    while (fscanf(f, "%lf", &x0) == 1)
    {
        n++;
        if (x0 > max)
        {
            max = x0;
            num = n;
        }
    }

    if (feof(f) == 0)
    {
        fclose(f);
        return -2;
    }

    fclose(f);

    *x = max;
    return num;
}


int MaxNum(const char *fname, double *x)//6
{
    FILE *f;
    int num = 0;
    double x0;
    double max;

    f = fopen(fname, "r");
    if (f == NULL)
        return -1;

    if (fscanf(f, "%lf", &max) == 1)
    {
        num++;
    }
    else
    {
        fclose(f);
        return -3;
    }

    while (fscanf(f, "%lf", &x0) == 1)
    {
        if (x0 > max)
        {
            max = x0;
            num = 1;
        }
        else if (x0 < max)
        {
            continue;
        }
        else
        {
            num++;
        }
    }

    if (feof(f) == 0)
    {
        fclose(f);
        return -2;
    }

    fclose(f);

    *x = max;
    return num;
}


int FirstLastMax(const char *fname, double *x, int *i, int *j)//7
{
    FILE *f;
    int n = 0;
    int first;
    int last;
    double x0;
    double max;

    f = fopen(fname, "r");
    if (f == NULL)
        return -1;

    if (fscanf(f, "%lf", &max) == 1)
    {
        n++;
        first = n;
        last = n;
    }
    else
    {
        fclose(f);
        return -3;
    }

    while (fscanf(f, "%lf", &x0) == 1)
    {
        n++;
        if (x0 > max)
        {
            max = x0;
            first = n;
        }
        else if (x0 < max)
        {
            continue;
        }
        else
        {
            last = n;
        }
    }

    if (feof(f) == 0)
    {
        fclose(f);
        return -2;
    }

    fclose(f);

    *i = first;
    *j = last;
    *x = max;
    return 0;
}


int FirstLastElemIsX(const char *fname, double x, int *i, int *j)//8
{
    FILE *f;
    double eps = 1e-7;
    int n = 0;
    int first = 0;
    int last = 0;
    double x0;

    f = fopen(fname, "r");
    if (f == NULL)
        return -1;

    while (fscanf(f, "%lf", &x0) == 1)
    {
        n++;
        if (fabs(x - x0) < eps)
        {
             if (first == 0)
             {
                 first = n;
             }
             last = n;
        }
    }

    if (feof(f) == 0)
    {
        fclose(f);
        return -2;
    }

    fclose(f);

    if (first != 0)
    {
        *i = first;
        *j = last;
        return 1;
    }
    else
    {
        return 0;
    }
}


int main(int argc, char *argv[])
{
    int ans1;
    int ans2;
    int ans3;
    int ans4;
    int ans5;
    int ans6;
    int ans7;
    int ans8;

    double x3;
    double x4;
    double x5;
    double x6;
    double x7;
    double x8;
    double d;
    int i1;
    int i2;
    int j1;
    int j2;

    const char *fname1 = "1.txt";
    const char *fname2 = "2.txt";
    const char *fname3 = "3.txt";
    const char *fname4 = "4.txt";
    const char *fname5 = "5.txt";
    const char *fname6 = "6.txt";
    const char *fname7 = "7.txt";
    const char *fname8 = "8.txt";

    if (argc != 2)
    {
        printf("Usage %s file\n", argv[0]);
        return 1;
    }
    fname2 = argv[1];

    printf("INPUT:\n");
    scanf("%lf%lf%lf", &x3, &x4, &x8);

    ans1 = StandartDeviation(fname1, &d);//1
    ans2 = SequenceWhat(fname2);//2
    ans3 = ElemIsXFirst(fname3, x3);//3
    ans4 = ElemIsXLast(fname4, x4);//4
    ans5 = MaxElem(fname5, &x5);//5
    ans6 = MaxNum(fname6, &x6);//6
    ans7 = FirstLastMax(fname7, &x7, &i1, &j1);//7
    ans8 = FirstLastElemIsX(fname8, x8, &i2, &j2);//8

    if (ans1 == -1)
        printf("CAN'T OPEN FILE\n");
    else if (ans1 == -2)
        printf("CAN'T READ AN ELEMENT\n");
    else
    {
        printf("NUMBER OF ELEMENTS: %d\n", ans1);
        if (ans1 != 0) printf("STANDART DEVIATION IS: %lf\n", d);
    }


    if (ans2 == -1)
        printf("CAN'T OPEN FILE\n");
    else if (ans2 == -2)
        printf("CAN'T READ AN ELEMENT\n");
    else if (ans2 == 4)
        printf("NOT ENOUGH INFORMATION\n");
    else if (ans2 == 1)
        printf("ARIF\n");
    else if (ans2 == 2)
        printf("GEOM\n");
    else if (ans2 == 3)
        printf("CONST\n");
    else
        printf("NAN\n");


    if (ans3 == -1)
        printf("CAN'T OPEN FILE\n");
    else if (ans3 == -2)
        printf("CAN'T READ AN ELEMENT\n");
    else if (ans3 == 0)
        printf("NO SUCH ELEMENT\n");
    else
        printf("NUMBER OF ELEMENTS IS: %d\n", ans3);


    if (ans4 == -1)
        printf("CAN'T OPEN FILE\n");
    else if (ans4 == -2)
        printf("CAN'T READ AN ELEMENT\n");
    else if (ans4 == 0)
        printf("NO SUCH ELEMENT\n");
    else
        printf("NUMBER OF ELEMENTS IS: %d\n", ans4);


    if (ans5 == -1)
        printf("CAN'T OPEN FILE\n");
    else if (ans5 == -2)
        printf("CAN'T READ AN ELEMENT\n");
    else if (ans5 == -3)
        printf("NO ELEMENTS\n");
    else
    {
        printf("NUMBER OF MAX ELEMENT IS: %d\n", ans5);
        printf("MAX ELEMENT IS: %lf\n", x5);
    }


    if (ans6 == -1)
        printf("CAN'T OPEN FILE\n");
    else if (ans6 == -2)
        printf("CAN'T READ AN ELEMENT\n");
    else if (ans6 == -3)
        printf("NO ELEMENTS\n");
    else
    {
        printf("NUMBER OF MAX ELEMENTS IS: %d\n", ans6);
        printf("MAX ELEMENT IS: %lf\n", x6);
    }


    if (ans7 == -1)
        printf("CAN'T OPEN FILE\n");
    else if (ans7 == -2)
        printf("CAN'T READ AN ELEMENT\n");
    else if (ans7 == -3)
        printf("NO ELEMENTS\n");
    else
    {
        printf("FIRST NUMBER OF MAX ELEMENTS IS: %d\n", i1);
        printf("LAST NUMBER OF MAX ELEMENTS IS: %d\n", j1);
        printf("MAX ELEMENT IS: %lf\n", x7);
    }


    if (ans8 == -1)
        printf("CAN'T OPEN FILE\n");
    else if (ans8 == -2)
        printf("CAN'T READ AN ELEMENT\n");
    else if (ans8 == 0)
        printf("NO ELEMENTS\n");
    else
    {
        printf("FIRST NUMBER OF ELEMENT IS: %d\n", i2);
        printf("LAST NUMBER OF ELEMENT IS: %d\n", j2);
        //printf("MAX ELEMENT IS: %lf\n", x);
    }

    return 0;
}
