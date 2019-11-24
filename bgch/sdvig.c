#include<stdio.h>
#include<stdlib.h>


int change(int *a, int n, int k, int i, int m);
int gcd(int m,int n);

int main()
{
	int k,n,i,m,funk;
	int *a;
	scanf("%d",&n);
	scanf("%d",&k);
	a=malloc(n*sizeof(int));
	for(i=0;i<n;i++) {scanf("%d",&a[i]);}
	k=k%n;
	funk=gcd(n,k);
	if (funk==1) change(a,n,k,0,n);
	else
	{
		m=n/funk;
		i=0;
		while(i<funk) 
		{
			change(a,n,k,i,m);
			i++;
		}	
	}
	for(i=0;i<n;i++) printf("%d ",a[i]);
	printf("\n");
	free(a);
	return 0;
}
int change(int *a, int n, int k, int i, int m)
{
	int rem,x,j;
	rem=a[i];
	for(j=0;j<m;j++) {i=(i+k)%n; x=a[i]; a[i]=rem; rem=x;}
	return 0;
}
int gcd(int m,int n)
{
	while (m>0)
	{
		n%=m;
		n+=m;
		m=n-m;
		n-=m;
	}
	return n;
}