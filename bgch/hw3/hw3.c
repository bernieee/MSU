#include <stdio.h>

int elem_num (const char *fname);//1
int max_num (const char *fname);//2
int more_than_previous_num (const char *fname);//3
int local_max_num (const char *fname);//4
int sequence_what(const char *fname);//5
int is_fib (const char *fname);//6
int is_fib_reverse (const char *fname);//7
int a_b (const char *fnamea, const char *fnameb);//8


int elem_num (const char *fname)//1
{
    FILE *f;
    double x0;
    double x;
    int ans = 0;
    
    f = fopen(fname, "r");
    if (f == NULL) 
        return -1;
    
    if (fscanf(f, "%lf", &x0) == 1)
        ans++;
    
    while (fscanf(f, "%lf", &x) == 1)
    {
        if (x > x0) 
            ans++;
        x0 = x;
    }
    
    if (feof(f) == 0) 
        return -2;
    
    fclose(f);
    
    return ans;
}


int max_num (const char *fname)//2
{
    FILE *f;
    double x;
    double max = 0;
    int ans = 0;
    
    f = fopen(fname, "r");
    if (f == NULL) 
        return -1;
    
    if (fscanf(f, "%lf", &x) == 1)
    {
        max = x;
        ans++;
    }
    
    while (fscanf(f, "%lf", &x) == 1)
    {
        if (x > max) 
        {
            max = x;
            ans = 1;
        }
        else if (x < max)
            continue;
        else
            ans++;
    }
    
    if (feof(f) == 0) 
        return -2;
    
    fclose(f);
    
    return ans;
}


int more_than_previous_num (const char *fname)//3
{
    FILE *f;
    double x0;
    double x;
    int ans = 0;
    
    f = fopen(fname, "r");
    if (f == NULL) 
        return -1;
    
    if (fscanf(f, "%lf", &x0) == 1)
       // ans++;
    
    while (fscanf(f, "%lf", &x) == 1)
    {
        if (x > x0) 
            ans++;
        x0 = x;
    }
    
    if (feof(f) == 0) 
        return -2;
    
    fclose(f);
    
    return ans;
}


int local_max_num (const char *fname)//4
{
    FILE *f;
    double x0;
    double x1;
    double x2;
    //double max = 0;
    int ans = 0;
    
    f = fopen(fname, "r");
    if (f == NULL) 
        return -1;
    
    if (fscanf(f, "%lf%lf", &x0, &x1) == 1)
    {
        if (x0 > x1)
            ans++;
    }
    
    while (fscanf(f, "%lf", &x2) == 1)
    {
        if ((x1 > x0) && (x1 > x2))
        {
            ans++;
        }
        x0 = x1;
        x1 = x2;
    }
    
    if (x1 > x0)
    {
        ans++;
    }
    
    if (feof(f) == 0) 
        return -2;
    
    fclose(f);
    
    return ans;
}


int sequence_what(const char *fname)//5
{
    FILE *f;
	int up = 0;
    int down = 0;
    int no = 0;
    int len = 0;
    double x0;
    double x;
    
    f = fopen(fname, "r");
    if (f == NULL) 
        return -1;
    
    if (fscanf(f, "%lf", &x0) == 1)
    {
        len++;
    }
    
	while(fscanf(f,"%lf",&x)==1)
	{
	    if (x > x0) 
        {
            up++;
            x0 = x;
        }
		else if (x < x0) 
        {
            down++;
            x0 = x; 
        }
		else 
        {
            no++;
            x0 = x;
        }
        len++;
	}
    
     if (feof(f) == 0) 
        return -2;
    
    fclose(f);
    
	if ((up > 0) && (down > 0))
        return 0;
    else if (len == 1)
        return 4;
    else if (up > 0)
        return 1;
    else if (down > 0)
        return 2;
    else //if (no > 0)
        return 3;
}
    

int is_fib (const char *fname)//6
{
    FILE *f;
    int x0;
    int x1;
    int x2;
    
    f = fopen(fname, "r");
    if (f == NULL) 
        return -1;
    
    if (fscanf(f, "%d%d", &x0, &x1) == 2)
    
    while (fscanf(f, "%d", &x2) == 1)
    {
        if (x2 != x0 + x1)
            return 0;
        x0 = x1;
        x1 = x2;
    }
    
    if (feof(f) == 0) 
        return -2;
    
    fclose(f);
    
    return 1;
}


int is_fib_reverse (const char *fname)//7
{
    FILE *f;
    int x0;
    int x1;
    int x2;
    
    f = fopen(fname, "r");
    if (f == NULL) 
        return -1;
    
    if (fscanf(f, "%d%d", &x0, &x1) == 2)
    
    while (fscanf(f, "%d", &x2) == 1)
    {
        if (x2 != x0 - x1)
            return 0;
        x0 = x1;
        x1 = x2;
    }
    
    if (feof(f) == 0) 
        return -2;
    
    fclose(f);
    
    return 1;
}
    

int a_b (const char *fnamea, const char *fnameb)//8
{
    FILE *fa;
    FILE *fb;
    double b;
    double a1;
    double a2;
    double a3;
    //int ans = 0;
    
    fa = fopen(fnamea, "r");
    if (fa == NULL) 
        return -1;
    
   fb = fopen(fnameb, "r");
    if (fb == NULL) 
        return -1;
    
    if (fscanf(fb, "%lf", &b) == 1)
    if (fscanf(fa, "%lf%lf", &a1, &a2) == 2)
    
    while ((fscanf(fb, "%lf", &b) == 1) && (fscanf(fa, "%lf", &a3) == 1))
    {
        //printf("%lf\n%lf\n%lf\n%lf\n", b, a1, a2, a3);
            if (b != (a1 + a3) / 2)
            {
                return 0;
            }
            a1 = a2;
            a2 = a3;
        
    }
    if ((feof(fa) == 0) || (feof(fa) == 0))
        return -2;
    
    fclose(f);
    
    return 1;
}


int main(void)
{
    const char *fname1 = "1.txt";
    const char *fname2 = "2.txt";
    const char *fname3 = "3.txt";
    const char *fname4 = "4.txt";
    const char *fname5 = "5.txt";
    const char *fname6 = "6.txt";
    const char *fname7 = "7.txt";
    const char *fnamea8 = "8a.txt";
    const char *fnameb8 = "8b.txt";
    
    int ans1 = elem_num (fname1);//1
    int ans2 = max_num (fname2);//2
    int ans3 = more_than_previous_num (fname3);//3
    int ans4 = local_max_num (fname4);//4
    int ans5 = sequence_what(fname5);//5
    int ans6 = is_fib (fname6);//6
    int ans7 = is_fib_reverse (fname7);//7
    int ans8 = a_b (fnamea8, fnameb8);//8
    
    
    if (ans1 == -1)
        printf("CAN'T OPEN FILE\n");
    else if (ans1 == -2)
        printf("CAN'T READ AN ELEMENT\n");
    else
        printf("NUMBER OF DIFFERENT ELEMENTS: %d\n", ans1);
    
    
    if (ans2 == -1)
        printf("CAN'T OPEN FILE\n");
    else if (ans2 == -2)
        printf("CAN'T READ AN ELEMENT\n");
    else
        printf("NUMBER OF MAX ELEMENTS: %d\n", ans2);
    
    
    if (ans3 == -1)
        printf("CAN'T OPEN FILE\n");
    else if (ans3 == -2)
        printf("CAN'T READ AN ELEMENT\n");
    else
        printf("NUMBER OF ELEMENTS THAT MORE THAN PREVIOUS: %d\n", ans3);
    
    
    if (ans4 == -1)
        printf("CAN'T OPEN FILE\n");
    else if (ans4 == -2)
        printf("CAN'T READ AN ELEMENT\n");
    else
        printf("NUMBER OF LOCAL MAX ELEMENTS: %d\n", ans4);
    
    
    if (ans5 == -1)
        printf("CAN'T OPEN FILE\n");
    else if (ans5 == -2)
        printf("CAN'T READ AN ELEMENT\n");
    else if (ans5 == 0)
        printf("SEQUENCE IS NOT MONOTONOUS\n");
    else if (ans5 == 1)
        printf("SEQUENCE GOES UP\n");
    else if (ans5 == 2)
        printf("SEQUENCE GOES DOWN\n");
    else if (ans5 == 3)
        printf("SEQUENCE IS CONST\n");
    else if (ans5 == 4)
        printf("CANT'T PREDICT BEHAVIOUR OF SEQUENCE\n");
    
    
    if (ans6 == -1)
        printf("CAN'T OPEN FILE\n");
    else if (ans6 == -2)
        printf("CAN'T READ AN ELEMENT\n");
    else if (ans6 == 0)
        printf("IT IS NOT THE FIBONACCI SEQUENCE\n");
    else
        printf("IT IS THE FIBONACCI SEQUENCE\n");
    
    
    if (ans7 == -1)
        printf("CAN'T OPEN FILE\n");
    else if (ans7 == -2)
        printf("CAN'T READ AN ELEMENT\n");
    else if (ans7 == 0)
        printf("IT IS NOT THE REVERSED FIBONACCI SEQUENCE\n");
    else
        printf("IT IS THE REVERSED FIBONACCI SEQUENCE\n");
    
    
    if (ans8 == -1)
        printf("CAN'T OPEN FILE\n");
    else if (ans8 == -2)
        printf("CAN'T READ AN ELEMENT\n");
    else if (ans8 == 0)
        printf("FALSE\n");
    else
        printf("TRUE\n");
    
    return 0;
}