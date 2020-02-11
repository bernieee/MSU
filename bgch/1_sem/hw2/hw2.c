#include <stdio.h>
#include <stdlib.h>

int is_prime(int n);
double precision(void);	//1
double func2(double x);	//2
void minimax(double x, double y, double z, double *a, double *b); //3
int sum_fib(int n);		//5	
double sum_1(int n, double x);	//6
double sum_2(int n, double x); 	//7
int prime_sum(int n); 	//8


double precision(void)
{
	double eps = 1;
	while (1 + eps != 1)
	{
		eps /= 2;
	}
	return eps;
}


double func2(double x)//2
{
	if (x < 1) 
	{
		return ((1 - x) - 2) / (3 - x);
	}
	else if ((x >= 1) && (x < 3))
	{
		return ((x - 1) - 2) / (3 - x);
	}
	else
	{
		return ((x - 1) - 2) / (x - 3);
	}
}


void minimax(double x, double y, double z, double *a, double *b)//3
{
	if ((x > y) && (y > z))
	{
		*a = x;
		*b = z;
	}
	if ((x > y) && (y < z))
	{
		*a = x;
		*b = y;
	}
	if ((x > y) && (x < z))
	{
		*a = z;
		*b = y;
	}
	if ((x < y) && (y < z))
	{
		*a = z;
		*b = x;
	}
	if ((x < y) && (x > z))
	{
		*a = y;
		*b = z;
	}
	if ((x < z) && (y > z))
	{
		*a = y;
		*b = x;
	}
}


int sum_fib(int n)//5
{
	int f0 = 1;
	int f1 = 1;
	int fn;
	int sum = 2;

	int i;
	for (i = 2; i < n; i++)
	{
		fn = f0 + f1;
		sum += fn;
		f0 = f1;
		f1 = fn;
	}
	return sum;
}


double sum_1(int n, double x)//6
{
	int i;
	double k = 1;
	double sum = 0;
	for (i = 1; i <= n; i++)
	{	
		k *= x / i;
		sum += k;
	}
	return sum;
}


double sum_2(int n, double x)//7
{
	int i;
	double sum = 0;
    if (n < 1)
    {
        printf("ERROR\n");
        return -1;
    }
	for(i = 1; i <= n; i++)
	{
		if (i % 2 == 0)
		{
			sum += x / i;
			//printf();
		} else 
		{
			sum -= x / i;
		}
	}
	return sum;
}


int is_prime(int n)
{
	int i;
	if (n == 1)
		return 0;
	for (i = 2; i * i <= n; i++)
	{
		if (n % i == 0) 
			return 0;
	}
	return 1;
}



int prime_sum(int n)//8
{
	int i = 2;
	int count = 0;
	int ans = 0;
	while (count < n)
	{
		if (is_prime(i)) 
		{
			count++;
			ans += i;
		}
		i++;
	}
	return ans;
}


int main(void) 
{
	double a;
	double b;
	double x;
	double y;
	double z;
	int n;
	
	//printf("1) OUTPUT: %.17lf\n", precision());
	/* //2
	if (scanf("%lf", &x) != 1)
		printf("ERROR\n");
	printf("2) OUTPUT: %lf\n", func2(x));
	*/
	
	/* //3
	if (scanf("%lf%lf%lf", &x, &y, &z) != 3)
	{
		printf("ERROR\n");
	}
	minimax(x, y, z, &a, &b);
	printf("3) OUTPUT: a = %lf\n b = %lf\n", a, b);
	*/
	
	/* //5 
	if (scanf("%d", &n) != 1)
		printf("ERROR\n");
	printf("5) OUTPUT: sum = %d\n", sum_fib(n));
	
	
	//6
	if (scanf("%d %lf", &n, &x) != 2)
		printf("ERROR\n");
	printf("6) OUTPUT: %.16lf\n", sum_1(n, x));
	
	//7
	printf("7) OUTPUT: %.16lf\n", sum_2(n, x));
	*/
	
	//8
	if (scanf("%d", &n) != 1)
		printf("ERROR\n");
	printf("8) OUTPUT: %d\n", prime_sum(n));
	return 0;
}