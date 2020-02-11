#include<stdio.h>
#include<stdlib.h>

int bin_reverse(int n);//1
int max_num_ones(int n);//2
int max_num_nulls(int n);//3
int max_len_ones(int n);//4
int max_len_nulls(int n);//5
int ones_to_nulls(int n);//6
int nulls_to_ones(int n);//7
int double_k();//8
int sequence_1(int n);//9
int sequence_2(int n);//10
double sum_1(int n);//11
double sum_2(int n);//12
double sum_3(int n);//13
int prime_num(int n);//14

int bin_reverse(int n)//1
{
	int k, out=0;
	while(n!= 0)
	{
		k=n&1;
		out<<=1;
		out+=k;
		printf("%d", k);
		n>>=1;
	}
	printf("\n");
	printf("%d\n", out);
	return out;
}

int max_num_ones(int n)//2
{
	int count=0, max=-100;
	while(n!= 0)
	{
		if((n&1)==1) count++;
		else
		{
			if(count>max) max=count;
			count=0;
		}
		n>>=1;
	}
	if(count>max) max=count;
	printf("%d\n", max);
	return max;
}

int max_num_nulls(int n)//3
{
	int count=0, max=-100;
	while(n!= 0)
	{
		//printf("%d\n", n&1);
		if((n&1)==0) count++;
		else
		{
			if(count>max) max=count;
			count=0;
			//printf("2\n");
		}
		n>>=1;
	}
	if(count>max) max=count;
	printf("%d\n", max);
	return max;
}

/*int max_len_ones(int n)//4
{
	int len=0, max=0, flag=0;
	while(n!=0)
	{
		if((n&1)==1 && flag==0) flag=1;
		else if((n&1)==0 && flag==1) len++;
		else if((n&1)==1 && flag==1)
		{
			if (len>max) max=len;
			len++;
		}
		n>>=1;
	}
	printf("%d\n", max);
	return max;
}*/

int max_len_ones(int n)//4
{
	int len=0, first, flag=0;
	while(n!=0)
	{
		if((n&1)==1 && flag==0) {flag=1; first=len;}
		len++;
		n>>=1;
	}
	printf("%d\n", len-first-1);
	return len-first-1;
}

int max_len_nulls(int n)//5
{
	int len=0, max=0, flag=0;
	while(n!=0)
	{
		if((n&1)==0 && flag==0) flag=1;
		else if((n&1)==1 && flag==1) len++;
		else if((n&1)==0 && flag==1)
		{
			if (len>max) max=len;
			len++;
		}
		n>>=1;
	}
	printf("%d\n", max);
	return max;
}

int ones_to_nulls(int n)//6
{
	int mask=0, count=0, ans=n;
	while(n!=0)
	{
		if((n&7)==7) {mask+=(1<<(count+1));}
		count++;
		n>>=1;
	}
	//printf("%d %d\n", n, mask);
	ans-=mask;
	printf("%d\n", ans);
	return ans;
}

int nulls_to_ones(int n)//7
{
	int mask=0, count=0, ans=n;
	while(n!=0)
	{
		if((n&7)==0) {mask+=(1<<(count+1));}
		count++;
		n>>=1;
	}
	ans+=mask;
	printf("%d\n", ans);
	return ans;
}

int double_k()//8
{
	double n, p;
	int len=0, dec=1;
	int x;
	if(scanf("%lf", &n)!=1)
		printf("ERROR\n");
	x=(int)n;
	p=n;
	if(n<1)
	{
		while((int)p!=1)
		{
			p=p*2.;
			printf("%lf\n", p);
			len++;
		}
		printf("%d\n", -len);
		return -len;
	}
	else
	{
		while(x!=0) 
		{
			x>>=1;
			len++;
		}
		printf("%d\n",len-1);
		return len-1;
	}
}

int sequence_1(int n)//9
{
	int i;
	int x0=1, x1;
	int pow_2=1;
	for(i=0;i<n;i++)
	{
		pow_2*=2;
		x1=x0*3+4*pow_2;
		x0=x1;
	}
	if(n==0) {printf("%d\n", x0); return x0;}
	else {printf("%d\n", x1); return x1;}
}

int sequence_2(int n)//10
{
	int i;
	int x0=2, x1=9, x2;
	int pow_4=1;
	for(i=1;i<n;i++)
	{
		x2=x1*5-x0*6+pow_4;
		pow_4*=4;
		x0=x1;
		x1=x2;
	}
	if(n==0) {printf("%d\n", x0);return x0;}
	else if(n==1) {printf("%d\n", x1);return x1;}
	else {printf("%d\n", x2);return x2;}
}

double sum_1(int n)//11
{
	int i;
	double k=1.;
	double sum=0.;
	for(i=1;i<=n;i++)
	{
		k*=i;
		sum+=(1./k);
	}
	printf("%lf\n", sum);
	return sum;
}

double sum_2(int n)//12
{
	int i;
	double sum=0.;
	for(i=1;i<=n;i++)
	{
		if(i%2==0) sum+=(1./i);
		else sum-=(1./i);
	}
	printf("%lf\n", sum);
	return sum;
}

double sum_3(int n)//13
{
	int i;
	double k=2.;
	//double pow_2=1.;
	double sum=k;
	for(i=2;i<=n;i++)
	{
		//pow_2*=2.;
		k*=2./i;
		sum+=k;
	}
	printf("%.16lf\n", sum);
	return sum;
}

int prime_num(int n)//14
{
	int* prime;
	int j,i,ans=1;
	prime=(int*)malloc(n*sizeof(int));
	if (prime==NULL) 
	{
		printf("ERROR\n");
		return 0;
	}
	for (int i=3; i<n; i++)
		prime[i]=1;
	prime[0]=prime[1]=0;
	for (int i=3; i<n; i++)
		if (prime[i]==1)
			if (i*i<n)
				for (j=i*i;j<n;j+=i)
					prime[j]=0;
	for (int i=3; i<n; i++)
	{
		if((i%2!=0)&&(prime[i]==1)) ans++;
	}
	printf("%d\n", ans);
	return ans;
}


int main(void)
{
	int n;
	printf("INPUT N:\n");
	if(scanf("%d", &n)!=1)
		printf("ERROR\n");
	//bin_reverse(n);
	//max_num_ones(n);
	//max_num_nulls(n);
	//max_len_ones(n);
	//max_len_nulls(n);
	//ones_to_nulls(n);
	//nulls_to_ones(n);
	//double_k();
	//sequence_1(n);
	//sequence_2(n);
	//sum_1(n);
	//sum_2(n);
	sum_3(n);
	//prime_num(n);
	return 0;
}