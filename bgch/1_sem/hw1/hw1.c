#include<stdio.h>
#include<stdlib.h>

int bit(unsigned int x);
int bin_reverse(unsigned int n);//1
int max_num_ones(unsigned int n);//2
int max_num_nulls(unsigned int n);//3
int max_len_ones(unsigned int n);//4
int max_len_nulls(unsigned int n);//5
int ones_to_nulls(unsigned int n);//6
int nulls_to_ones(unsigned int n);//7
int double_k(double n);//8
int sequence_1(int n);//9
int sequence_2(int n);//10
double sum_1(int n);//11
double sum_2(int n);//12
double sum_3(int n);//13
int prime_num(int n);//14

int bit(unsigned int x)
{
    int i, j;
    int len=sizeof(int)*8;
    for(i=len-1;i>=0;i--)
        if(x&(1<<i)) break;
    for(j=i;j>=0;j--)
        printf("%u", (x>>j)&1);
    printf("\n");
    return 0;
}

int bin_reverse(unsigned int n)//1
{
    unsigned int k, out=0;
    while(n!= 0)
    {
        k=n&1;
        out<<=1;
        out+=k;
        n>>=1;
    }
    return out;
}

int max_num_ones(unsigned int n)//2
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
    return max;
}

int max_num_nulls(unsigned int n)//3
{
    int count=0, max=-100;
    while(n!= 0)
    {
        if((n&1)==0) count++;
        else
        {
            if(count>max) max=count;
            count=0;
        }
        n>>=1;
    }
    if(count>max) max=count;
    return max;
}

int max_len_ones(unsigned int n)//4
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
    return max;
}


int max_len_nulls(unsigned int n)//5
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
    return max;
}

int ones_to_nulls(unsigned int n)//6
{
    int mask=0, count=0, ans=n;
    while(n!=0)
    {
        if((n&7)==7) {mask+=(1<<(count+1));}
        count++;
        n>>=1;
    }
    ans-=mask;
    return ans;
}

int nulls_to_ones(unsigned int n)//7
{
    int mask=0, count=0, ans=n;
    while(n!=0)
    {
        if((n&7)==0) {mask+=(1<<(count+1));}
        count++;
        n>>=1;
    }
    ans+=mask;
    return ans;
}

int double_k(double n)//8
{
    double p;
    int len=0;
    int x;
    x=(int)n;
    p=n;
    if(n<1)
    {
        while((int)p!=1)
        {
            p=p*2.;
            len++;
        }
        return -len;
    }
    else
    {
        while(x!=0)
        {
            x>>=1;
            len++;
        }
        return len-1;
    }
}

int sequence_1(int n)//9
{
    int i;
    int x0=1, x1;
    int pow_2=1;
    if(n<0)
    {
        printf("ERROR\n");
        return -1;
    }
    for(i=0;i<n;i++)
    {
        pow_2*=2;
        x1=x0*3+4*pow_2;
        x0=x1;
    }
    if(n==0) {return x0;}
    else {return x1;}
}

int sequence_2(int n)//10
{
    int i;
    int x0=2, x1=9, x2;
    int pow_4=1;
    if(n<0)
    {
        printf("ERROR\n");
        return -1;
    }
    for(i=1;i<n;i++)
    {
        x2=x1*5-x0*6+pow_4;
        pow_4*=4;
        x0=x1;
        x1=x2;
    }
    if(n==0) {return x0;}
    else if(n==1) {return x1;}
    else {return x2;}
}

double sum_1(int n)//11
{
    int i;
    double k=1.;
    double sum=0.;
    for(i=1;i<=n;i++)
    {
        k/=i;
        sum+=k;
    }
    return sum;
}

double sum_2(int n)//12
{
    int i;
    double sum=0.;
    if(n<1)
    {
        printf("ERROR\n");
        return -1;
    }
    for(i=1;i<=n;i++)
    {
        if(i%2==0) sum+=(1./i);
        else sum-=(1./i);
    }
    return sum;
}

double sum_3(int n)//13
{
    int i;
    double k=2.;
    double sum=k;
    if(n<1)
    {
        printf("ERROR\n");
        return -1;
    }
    for(i=2;i<=n;i++)
    {
        k*=2./i;
        sum+=k;
    }
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
    for (i=3; i<n; i++)
        prime[i]=1;
    prime[0]=prime[1]=0;
    for (i=3; i<n; i++)
        if (prime[i]==1)
            if (i*i<n)
                for (j=i*i;j<n;j+=i)
                    prime[j]=0;
    for (i=3; i<n; i++)
    {
        if((i%2!=0)&&(prime[i]==1)) ans++;
    }
    return ans;
}


int main(void)
{
    int n;

    printf("INPUT N:\n");

    if(scanf("%d", &n)!=1)
        printf("ERROR\n");

    printf("%u = ",n);
    bit(n);

    //1
    printf("1) OUTPUT: %u = ", bin_reverse(n));
    bit(bin_reverse(n));

    //2
    printf("2) OUTPUT: %d\n", max_num_ones(n));

    //3
    printf("3) OUTPUT: %d\n", max_num_nulls(n));

    //4
    printf("4) OUTPUT: %d\n", max_len_ones(n));

    //5
    printf("5) OUTPUT: %d\n", max_len_nulls(n));

    //6
    printf("6) OUTPUT: %d = ", ones_to_nulls(n));
    bit(ones_to_nulls(n));

    //7
    printf("7) OUTPUT: %d = ", nulls_to_ones(n));
    bit(nulls_to_ones(n));

    //9
    printf("9) OUTPUT: %d\n", sequence_1(n));

    //10
    printf("10) OUTPUT: %d\n", sequence_2(n));

    //11
    printf("11) OUTPUT: %.6lf\n", sum_1(n));

    //12
    printf("12) OUTPUT: %.16lf\n", sum_2(n));

    //13
    printf("13) OUTPUT: %.16lf\n", sum_3(n));

    //14
    printf("14) OUTPUT: %d\n", prime_num(n));

    //8
    /*double n;
    printf("INPUT N:\n");
    if(scanf("%lf", &n)!=1)
        printf("ERROR\n");
    printf("8) OUTPUT: %d\n", double_k(n));*/

    return 0;
}
