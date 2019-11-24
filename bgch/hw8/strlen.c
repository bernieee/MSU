#include<stdio.h>
#include<stdlib.h>


int my_strlen(char *a);
char * my_strdup(char *a);
int my_strcmp(char *a, char *b);
int my_strchr(char *a, char b);
int my_strstr(char *a, char *b);


int main()
{
	//char s[]="abrakadabra";
	//char p[]="rakadabr";
	scanf("%s", s);
	scanf("%s", p);
	printf("%d",my_strstr(s,p));
	return 0;
}

int my_strlen(char *a)
{
	int len=0;
	while (a[len]!='\0') len++;
	return len;
}

char * my_strdup(char *a)
{
	char *b;
	int i;
	int n=my_strlen(a);
	b=malloc((n+1)*sizeof(char));
	for(i=0;i<n;i++) b[i]=a[i];
	return b;
}
int my_strcmp(char *a, char *b)
{
	int i=0;
	while((a[i]!='\0')&&(a[i]==b[i])) i++;
	return a[i]-b[i];
}
int my_strchr(char *a, char b)
{
	int i;
	int n=my_strlen(a);
	while(a[i]!='\0')
	{
		if(a[i]==b) break;
	}
	return i;
}
int my_strstr(char *a, char *b)
{
	int i=0,j,tmp;
	while(a[i]!='\0')
	{
		if(a[i]==b[0])
		{
			tmp=i;
			j=0;
			while((a[tmp]!='\0')&&(b[j]!='\0')&&(a[tmp]==b[j])) j++;
		}
		if (b[j]=='\0') break;
		else i++;
	}
	return i;
}
