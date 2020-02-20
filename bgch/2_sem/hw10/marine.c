 
#include <stdio.h>
#include <string.h>
#include "f.h"
#define LEN 1234

static int test1_f1 (char *buf, const char *s,const char *r,FILE *name,int s_len)
{ int i,j;
 char *t;
 int f = 0;
 int ans = 0;
i = 0;
j = strlen(buf);
while (i < j) 
{
t = strstr(buf + i, s);
if (t != NULL)
{
f = 1;
while (buf + i != t)
{
fprintf(name, "%c", buf[i]);
++i;
}
fprintf(name, "%s", r);
i += s_len;
}
else 
{
fprintf(name, "%s", buf + i);
break;
}

if (f) ans++;
}
return ans;
}

int f1 (char *name1 ,char *name2, const char *s,const char *r, int ss)
{
  FILE *fp;
  FILE *ff;
  int res = 0;
  char buf [LEN];
  if (!(fp = fopen (name1, "r")))
       return ERROR_OPEN;
  if (!(ff = fopen (name2, "w")))
       return ERROR_OPEN;
  while (fgets (buf, LEN, fp))
  {
    if ( test1_f1 (buf,s,r,ff,ss))
    res ++;
    fprintf(ff,"\n");
  }
  if (!feof (fp))
  {
   fclose (fp);fclose (ff);
   return ERROR_READ;
  }
 fclose (fp);fclose (ff);
 return res;
}


static int test2_f2 (char *buf,int *BUF,char *s,FILE *name)
{  int i = 0;
   int flag = 0;
   int j = 0;
   int count = 0;
  for (i=0; buf[i] && (buf[i]!='\n') ; i++)
  { 
    if(BUF[(unsigned char)buf[i]>>5] & 1<<(31-(((unsigned char )buf[i])&31)))
       continue;
    
    if (buf[i]!=s[j])
    { flag=1;break; }

    ++j; 
  }
    if (flag || s[j])
    { count++;fprintf(name,"%s",buf);}
return count;
}




static int test3_f3 (char *buf,int *BUF,FILE *name)
{ 
  int i = 0;
  for (i=0;buf[i];i++)
    {if (buf[i]=='\n')
    {buf[i]='\0'; break;}}
    i=0;
   while(buf[i])
  {
   if(!((BUF[(unsigned char)buf[i]>>5] & 1<<(31-(((unsigned char)buf[i])&31)))))
    {return 0;}
    i++;
   } 
  { fprintf (name,"%s\n",buf);}
  
return 1 ;
}





int f2 (char *name1 ,char *name2,char *s,const char *t)
{
  FILE *fp;
  FILE *ff;
  char buf [LEN];int BUF [8];
  int res = 0;int i = 0; int j =0 ;
  if (!(fp = fopen (name1, "r")))
       return ERROR_OPEN;
  if (!(ff = fopen (name2, "w")))
       return ERROR_OPEN;
  
  
  for(i=0;i<8;i++)
  {BUF[i]=0;}
  
i=0;
  while (t[i])
{
  BUF[(unsigned char)t[i]>>5] |= 1<<(31-(((unsigned char )t[i])&31));
  i++;
}
 i=0;
  
  while (s[i])
{
  if(!(BUF[(unsigned char)s[i]>>5] & 1<<(31-(((unsigned char )s[i])&31))))
  {s[j]=s[i];j++;}
  i++;
} 
 s[j]='\0';
 printf("%s\n",s);
  
  while (fgets (buf, LEN, fp))
  {
    if ( test2_f2 (buf,BUF,s,ff))
    res ++;
  }
  if (!feof (fp))
  {
   fclose (fp);fclose (ff);
   return ERROR_READ;
  }
 fclose (fp);fclose (ff);
 return res;
}

int f3 (char *name1 ,char *name2, char *s,char *t)
 {
  FILE *fp;
  FILE *ff;
  char buf [LEN];int BUF [8];
  int res = 0;int i = 0;
  if (!(fp = fopen (name1, "r")))
       return ERROR_OPEN;
  if (!(ff = fopen (name2, "w")))
       return ERROR_OPEN;
  
for(i=0;i<8;i++)
  {BUF[i]=0;}
  
i=0;
  while (s[i])
{
  BUF[(unsigned char)s[i]>>5] |= 1<<(31-((unsigned char )s[i]&31));
  i++;
}

  i=0;
  while (t[i])
{
  BUF[(unsigned char)t[i]>>5] |= 1<<(31-((unsigned char )t[i]&31));
  i++;
}

  while (fgets (buf, LEN, fp))
  {
    
    if ( test3_f3 (buf,BUF,ff))
    res ++;
  }
  if (!feof (fp))
  {
   fclose (fp);fclose (ff);
   return ERROR_READ;
  }
 fclose (fp);fclose (ff);
 return res;
}




static int test4_f4 (char *buf,int *BUF, const char *s,FILE *name)
{ 
  int i = 0;
   int j = 0;
  for (i=0; buf[i] && (buf[i]!='\n') ; i++)
  { 
    if (!s[j])
    {fprintf (name,"%s",buf);return 1;} 
 
    if(BUF[(unsigned char)buf[i]>>5] & 1<<(31-(((unsigned char )buf[i])&31)))
       continue;
    
    if (buf[i]==s[j])
        j++;
    else  
        j=0;
  } 
    if (!s[j])
    {fprintf (name,"%s",buf);return 1;} 

return 0;
    
}

int f4 (char *name1 ,char *name2,char *s,const char *t)
{
  FILE *fp;
  FILE *ff;
  char buf [LEN];int BUF [8];
  int res = 0;int i = 0; int j = 0;
  if (!(fp = fopen (name1, "r")))
       return ERROR_OPEN;
  if (!(ff = fopen (name2, "w")))
       return ERROR_OPEN;
  
  
  for(i=0;i<8;i++)
  {BUF[i]=0;}
  
i=0;
  while (t[i])
{
  BUF[(unsigned char)t[i]>>5] |= 1<<(31-(((unsigned char )t[i])&31));
  i++;
}
 i=0;
  
  while (s[i])
{
  if(!(BUF[(unsigned char)s[i]>>5] & 1<<(31-(((unsigned char )s[i])&31))))
  {s[j]=s[i];j++;}
  i++;
} 
 s[j]='\0';
 printf("%s\n",s);
  
  while (fgets (buf, LEN, fp))
  {
    if ( test4_f4 (buf,BUF,s,ff))
    res ++;
  }
  if (!feof (fp))
  {
   fclose (fp);fclose (ff);
   return ERROR_READ;
  }
 fclose (fp);fclose (ff);
 return res;
}


static int test_f5 (char *buf, const char *s,FILE *name, int flag)
{  
   if (flag==1)
   { if (strstr(buf,s+1) == buf )
     {fprintf (name,"%s", buf);return 1;} }
   else 
   { if (strstr(buf,s))
    { fprintf (name,"%s", buf);return 1;} }
return 0;
}


static int change_string5 (char *s)
{ int flag1 = 0;int j = 0; int i = 0;int flag;
   if ((s[0])==94) flag1 = 1;
    while (s[j]!='\0')
{     
    s[i]=s[j];
    if (s[i]==92)
{ if (s[j+1]==92)
{if (flag==0)
{flag=1; j++;continue;}
else
{flag=0; i++;j++;continue;} }
if (s[j+1]==94)
{j++;
if (flag==1)
{flag=0;i++;}
continue;}
j++;i++;flag=0;}
else {j++;i++;flag=0;}}s[i]='\0';
return flag1;
}
    
int f5 (char *name1 ,char *name2, char *s)
{
  FILE *fp;
  FILE *ff;
  int res = 0;int flag;
  char buf [LEN];
  if (!(fp = fopen (name1, "r")))
       return ERROR_OPEN;
  if (!(ff = fopen (name2, "w")))
       return ERROR_OPEN;
  flag=change_string5 (s);
  printf ("%s",s);
  while (fgets (buf, LEN, fp))
  { 
    if ( test_f5(buf,s,ff,flag))
    res ++;
    fprintf(ff,"\n\n");
    
  }
  if (!feof (fp))
  {
   fclose (fp);fclose (ff);
   return ERROR_READ;
  }
 fclose (fp);fclose (ff);
  printf("\n\n");
 return res;
}


 
static int change_string6 (char *s,int s_len)
{ int flag1 = 0;int j = 0; int i = 0;int flag;
   if ((s[s_len-1])== 36)
   {flag1 = 1;s[s_len-1]='\0';}
    
    while (s[j]!='\0')
{     
    s[i]=s[j];
    if (s[i]==92)
{ if (s[j+1]==92)
{if (flag==0)
{flag=1; j++;continue;}
else
{flag=0; i++;j++;continue;} }
if (s[j+1]==36)
{j++;
if (flag==1)
{flag=0;i++;}
continue;}
j++;i++;flag=0;}
else {j++;i++;flag=0;}} s[i]='\0';
return flag1;
}


     
static int test_f6 (char *buf, char *s,FILE *name, int flag, int s_len)
{  
   int buf_len = strlen (buf);
   if (flag==1)
   {
     if (strstr(buf+buf_len - s_len,s))
     {fprintf (name,"%s", buf);return 1; }}
   else 
   { if (strstr(buf,s))
     {fprintf (name,"%s", buf);return 1; }}
return 0;
}
      


int f6 (char *name1 ,char *name2, char *s)
{
  FILE *fp;
  FILE *ff;int i = 0;
  int res = 0;int flag;int s_len;
  char buf [LEN];
  if (!(fp = fopen (name1, "r")))
       return ERROR_OPEN;
  if (!(ff = fopen (name2, "w")))
       return ERROR_OPEN;
  s_len = strlen (s);
  flag=change_string6 (s,s_len);
  s_len = strlen (s);
  printf ("%s",s);
  while (fgets (buf, LEN, fp))
  {  
    for (i=0;buf[i];i++)
       {if (buf[i]=='\n')
       { buf[i]='\0';break;}}

    if ( test_f6(buf,s,ff,flag,s_len))
    { res ++;
    fprintf(ff,"\n\n");}
    
  }
  if (!feof (fp))
  {
   fclose (fp);fclose (ff);
   return ERROR_READ;
  }
 fclose (fp);fclose (ff);
  printf("\n\n");
 return res;
}




static int test7_f7 (char *buf, const char *s,const char *l,const char *r,FILE *name, int s_len)
{ 
 int ans = 0, i, j = 0, f = 0;
 char *t = NULL;

    for (i=0;buf[i];i++)
    {if (buf[i]=='\n')
    {buf[i]='\0'; break;}}
i = 0;
j = strlen(buf);
while (i < j) 
{
 t = strstr(buf + i, s);
if (t != NULL) 
{ f = 1;
   while (buf + i != t) 
{
  fprintf(name, "%c", buf[i]);
  ++i;
}
fprintf(name, "%s%s%s",l,s, r);
i += s_len;
}
else 
{
fprintf(name, "%s", buf + i);
break;
}
}
if (f) ++ans;
return ans;
    
}
  
  
  
int f7 (const char *name1 ,const char *name2, const char *s,const char *l,const char *r)
{
  FILE *fp;
  FILE *ff;
  int res = 0;
  int s_len;
  char buf [LEN];
  if (!(fp = fopen (name1, "r")))
       return ERROR_OPEN;
  if (!(ff = fopen (name2, "w")))
       return ERROR_OPEN;
  s_len=strlen(s);
  while (fgets (buf, LEN, fp))
  { 
    if ( test7_f7 (buf,s,l,r,ff,s_len))
    res ++;
    fprintf(ff,"\n");
    
  }
  if (!feof (fp))
  {
   fclose (fp);fclose (ff);
   return ERROR_READ;
  }
 fclose (fp);fclose (ff);
 return res;
}


static int test_f8 (char *buf, int *BUF, const char *s,const char *r,FILE *name, int r_len)

{    int i = 0;
     int count = 0;
     int j = 0; char string[2];string[1]='\0';
     for (i=0; buf[i] && (buf[i]!='\n');i++)
   {
       if (!(BUF[(unsigned char)buf[i]>>5] & 1<<(31-(((unsigned char )buf[i])&31))))
            fprintf (name, "%c",buf[i]);
 
       else 
       {   string[0]=buf[i];
           
           j = strcspn (s,string);

           if (j < r_len)
          {fprintf (name, "%c", r[j]);count++;}
       }
   }
return count;
}


int f8 (char *name1 ,char *name2,char *s,char *r)
{
  FILE *fp;
  FILE *ff;
  char buf [LEN];int BUF [8];
  int res = 0;int i = 0;int r_len = 0;
  if (!(fp = fopen (name1, "r")))
       return ERROR_OPEN;
  if (!(ff = fopen (name2, "w")))
       return ERROR_OPEN;
  
  
  for(i=0;i<8;i++)
  {BUF[i]=0;}
  
i=0;
  while (s[i])
{
  BUF[(unsigned char)s[i]>>5] |= 1<<(31-(((unsigned char )s[i])&31));
  i++;
}

  r_len = strlen(r);
  while (fgets (buf, LEN, fp))
  {
    if ( test_f8 (buf,BUF,s,r,ff,r_len))
    res += test_f8 (buf,BUF,s,r,ff,r_len);
  }
  if (!feof (fp))
  {
   fclose (fp);fclose (ff);
   return ERROR_READ;
  }
 fclose (fp);fclose (ff);
 return res;
}
