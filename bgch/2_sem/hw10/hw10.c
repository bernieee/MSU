#include "hw10.h"
#include<stdio.h>
#include<string.h>


static int Change1(FILE *b, char *buf, const char *s, const char *r)
{
    char * res;
    int lens;
    int flag;
    int i;
    lens = strlen(s);
    i = 0;
    flag = 0;

    while (buf[i] != '\0')
    {
        res = strstr((buf + i), s);
        if (res != NULL)
        {
            flag = 1;
            while ((buf + i) != res)
            {
                fprintf(b, "%c", buf[i]);
                i++;
            }
            fprintf(b, "%s", r);
            i += lens;
        }
        else
        {
            fprintf(b, "%s", buf + i);
            break;
        }
    }
    fprintf(b, "\n");
    if (flag == 1)
        return 1;
    else
        return 0;
}


static int Cmp(char *buf, const char *s, char *buft)
{
    int i = 0;
    int j = 0;
    if (strcmp(buf, s) == 0)
        return 1;
    printf("%d\n", strcmp(buf, s));
    while ((buf[i] != '\0') && (s[j] != '\0'))
    {
        if (buf[i] == s[j])
        {
            i++;
            j++;
        }
        else
        {
            if (buft[(int)buf[i]] == 1)//если это пробелный символ
                i++;
            else if (buft[(int)s[j]] == 1)//если это пробелный символ
                j++;
            else
                return 0;
        }
    }
    return 1;
}


static int S(char *buf, const char *s)
{
    int i;
    for (i = 0; i < 256; i++)
    {
        buf[i] = 0;
    }
    i = 0;
    while (s[i] != '\0')
    {
        buf[(int)s[i]] = 1;
        i++;
    }
    return 0;
}


static int CmpBin(char *buf, char *bufs, char *buft)
{
    for (int i = 0; buf[i]; i++)
    {
        if ((bufs[(int)buf[i]] == 0) && (buft[(int)buf[i]] == 0))
            return 0;
    }
    return 1;
}


static int Strstr(char *buf, const char *s, char *buft)
{
    int i;
    int j;
    int tmp;
    i = 0;
    while (buf[i] != '\0')
    {
        j = 0;
        if (buf[i] == s[j])
        {
            tmp = i;
            while (buf[tmp] != '\0')
            {
                if (buf[tmp] == s[j])
                {
                    tmp++;
                    j++;
                }
                else
                {
                    if (buft[(int)buf[tmp]] == 1)//если это пробелный символ
                        tmp++;
                    else if (buft[(int)s[j]] == 1)//если это пробелный символ
                        j++;
                    else
                        break;
                }
            }
        }
        if (s[j] == '\0')
            break;
        else
            i++;
    }
    if (buf[i] == '\0')
        return 0;
    else
        return 1;
}


static int Change5(FILE *b, char *buf, const char *s, int flag)
{
   if (flag == 1)//beginning is '^'
   {
       if (strstr(buf, s + 1) == buf)
       {
           fprintf(b, "%s", buf);
           return 1;
       }
   }
   else
   {
       if (strstr(buf, s))
       {
           fprintf(b, "%s", buf);
           return 1;
       }
    }
    return 0;
}


static int StrS1(char *s)
{
    int flag1 = 0;
    int j = 0;
    int i = 0;
    int flag2 = 0;
    if (s[0] == '^')//^
        flag1 = 1;
    while (s[j] != '\0')
    {
        s[i] = s[j];//rewrite s
        if (s[i] == '\\')
        {
            if (s[j + 1] == '\\')
            {
                if (flag2 == 0)
                {
                    flag2 = 1;
                    j++;
                }
                else
                {
                    i++;
                    j++;
                }
            }
            else if (s[j + 1] == '^')
            {
                j++;
                if (flag2 == 1)
                {
                    flag2 = 0;
                    i++;
                }
            }
            //j++;
            //i++;
            flag2 = 0;
        }
        else
        {
            j++;
            i++;
            flag2 = 0;
        }
    }
    s[i] = '\0';
    printf("%s\n", s);
    return flag1;
}


static int StrS2(char *s, int lens)
{
    int flag1 = 0;
    int j = 0;
    int i = 0;
    int flag2 = 0;
    if (s[lens - 1] == '&')
    {
        flag1 = 1;
        s[lens - 1]='\0';
    }
    while (s[j] != '\0')
    {
        s[i] = s[j];
        if (s[i] == '\\')
        {
            if (s[j + 1] == '\\')
            {
                if (flag2 == 0)
                {
                    flag2 = 1;
                    j++;
                }
                else
                {
                    flag2 = 0;
                    i++;
                    j++;
                }
            }
            if (s[j + 1] == '&')
            {
                j++;
                if (flag2 == 1)
                {
                    flag2 = 0;
                    i++;
                }
            }
            j++;
            i++;
            flag2 = 0;
        }
        else
        {
            j++;
            i++;
            flag2 = 0;
        }
    }
    s[i] = '\0';
    return flag1;
}


static int Change6(FILE *b, char *buf, const char *s, int lens, int flag)
{
    int lenbuf = strlen (buf);
    if (flag == 1)
    {
        if (strstr(buf + lenbuf - lens, s))
        {
            fprintf(b, "%s", buf);
            return 1;
        }
    }
    else
    {
        if (strstr(buf, s))
        {
            fprintf(b, "%s", buf);
            return 1;
        }
    }
    return 0;
}


static int Change7(FILE *b, char *buf, const char *s, const char *l, const char *r)
{
    char * res;
    int lens;
    int flag;
    int i;
    lens = strlen(s);
    i = 0;
    flag = 0;

    while (buf[i] != '\0')
    {
        res = strstr((buf + i), s);
        if (res != NULL)
        {
            flag = 1;
            while ((buf + i) != res)
            {
                fprintf(b, "%c", buf[i]);
                i++;
            }
            fprintf(b, "%s", l);
            fprintf(b, "%s", s);
            fprintf(b, "%s", r);
            i += lens;
        }
        else
        {
            fprintf(b, "%s", buf + i);
            break;
        }
    }
    fprintf(b, "\n");
    if (flag == 1)
        return 1;
    else
        return 0;
}


static int Change8(FILE *b, char *buf, const char *bufs, const char *bufr)
{
    int res;
    int i;
    i = 0;
    res = 0;

    for (i = 0; buf[i]; i++)
    {
        if (bufs[(int)buf[i]] == 1)
        {
            //if (bufr[(int)buf[i]] != 0)
            buf[i] = (char)bufr[(int)buf[i]];
            res++;
        }

    }
    fprintf(b, "%s\n", buf);
    return res;
}


static int SR(char *bufs, char *bufr, const char *s, const char *r)
{
    int i;
    //int lens;
    int lenr;
    //lens = strlen(s);
    lenr = strlen(r);
    for (i = 0; i < 256; i++)
    {
        bufs[i] = 0;
        bufr[i] = 0;
    }
    i = 0;
    while (s[i] != '\0')
    {
        bufs[(int)s[i]] = 1;
        if (i < lenr)
            bufr[(int)s[i]] = (int)r[i];
        i++;
    }
    return 0;
}


//prints string from a, if string != s, else prints r
int Func1(const char *fname1, const char *fname2, const char *s, const char *r)//1
{
    FILE *a;
    FILE *b;
    char buf[LEN];
    int ans = 0;
    if (!(a = fopen(fname1, "r")))
        return ERROR_OPEN;
    if (!(b = fopen(fname2, "w")))
        return ERROR_OPEN;

    while (fgets(buf, LEN, a))
    {
        buf[strlen(buf) - 1] = '\0';
        if (Change1(b, buf, s, r) == 1) // 1 is YES, 0 is NO
        {
            ans++;
        }
    }
    if (!feof(a))
    {
        fclose(a);
        fclose(b);
        return ERROR_READ;
    }
    fclose(a);
    fclose(b);
    return ans;
}


//skips all symbols from t and prints string from a, if string != s
int Func2(const char *fname1, const char *fname2, const char *s, const char *t)//2
{
    FILE *a;
    FILE *b;
    char buf[LEN];
    char buft[STR];
    int ans = 0;
    if (!(a = fopen(fname1, "r")))
        return ERROR_OPEN;
    if (!(b = fopen(fname2, "w")))
        return ERROR_OPEN;

    S(buft, t);
    while (fgets(buf, LEN, a))
    {
        buf[strlen(buf) - 1] = '\0';
        if (Cmp(buf, s, buft) == 0)
        {
            fprintf(b, "%s\n", buf);
            ans++;
        }
    }
    if (!feof(a))
    {
        fclose(a);
        fclose(b);
        return ERROR_READ;
    }
    fclose(a);
    fclose(b);
    return ans;
}


int Func3(const char *fname1, const char *fname2, const char *s, const char *t)//3
{
    FILE *a;
    FILE *b;
    char buf[LEN];
    char buft[STR];
    char bufs[STR];
    int ans = 0;
    if (!(a = fopen(fname1, "r")))
        return ERROR_OPEN;
    if (!(b = fopen(fname2, "w")))
        return ERROR_OPEN;

    S(buft, t);
    S(bufs, s);
    while (fgets(buf, LEN, a))
    {
        buf[strlen(buf) - 1] = '\0';
        if (CmpBin(buf, bufs, buft) == 1)
        {
            fprintf(b, "%s\n", buf);
            //printf("+\n");
            ans++;
        }
    }
    if (!feof(a))
    {
        fclose(a);
        fclose(b);
        return ERROR_READ;
    }
    fclose(a);
    fclose(b);
    return ans;
}


int Func4(const char *fname1, const char *fname2, const char *s, const char *t)//4
{
    FILE *a;
    FILE *b;
    char buf[LEN];
    char buft[STR];
    int ans = 0;
    if (!(a = fopen(fname1, "r")))
        return ERROR_OPEN;
    if (!(b = fopen(fname2, "w")))
        return ERROR_OPEN;

    S(buft, t);
    while (fgets(buf, LEN, a))
    {
        buf[strlen(buf) - 1] = '\0';
        if (Strstr(buf, s, buft) == 1)//s подстрока buf
        {
            fprintf(b, "%s\n", buf);
            ans++;
        }
    }
    if (!feof(a))
    {
        fclose(a);
        fclose(b);
        return ERROR_READ;
    }
    fclose(a);
    fclose(b);
    return ans;
}


int Func5(const char *fname1, const char *fname2, const char *s)//5
{
    FILE *a;
    FILE *b;
    char buf[LEN];
    int ans = 0;
    int flag = 0;
    if (!(a = fopen(fname1, "r")))
        return ERROR_OPEN;
    if (!(b = fopen(fname2, "w")))
        return ERROR_OPEN;

    flag = StrS1((char *)s);
    while (fgets(buf, LEN, a))
    {
        buf[strlen(buf) - 1] = '\0';
        if (Change5(b, buf, s, flag) == 1)
        {
            ans++;
        }
    }
    if (!feof(a))
    {
        fclose(a);
        fclose(b);
        return ERROR_READ;
    }
    fclose(a);
    fclose(b);
    return ans;
}


int Func6(const char *fname1, const char *fname2, const char *s)//6
{
    FILE *a;
    FILE *b;
    char buf[LEN];
    int ans = 0;
    int flag = 0;
    int lens = 0;
    if (!(a = fopen(fname1, "r")))
        return ERROR_OPEN;
    if (!(b = fopen(fname2, "w")))
        return ERROR_OPEN;

    lens = strlen(s);
    StrS2((char *)s, lens);
    while (fgets(buf, LEN, a))
    {
        buf[strlen(buf) - 1] = '\0';
        if (Change6(b, buf, s, lens, flag) == 1)
        {
            fprintf(b, "%s\n", buf);
            ans++;
        }
    }
    if (!feof(a))
    {
        fclose(a);
        fclose(b);
        return ERROR_READ;
    }
    fclose(a);
    fclose(b);
    return ans;
}



int Func7(const char *fname1, const char *fname2, const char *s, const char *l, const char *r)//7
{
    FILE *a;
    FILE *b;
    char buf[LEN];
    int ans = 0;
    if (!(a = fopen(fname1, "r")))
        return ERROR_OPEN;
    if (!(b = fopen(fname2, "w")))
        return ERROR_OPEN;

    while (fgets(buf, LEN, a))
    {
        buf[strlen(buf) - 1] = '\0';
        if (Change7(b, buf, s, l, r) == 1)//s подстрока buf
        {
            ans++;
        }
    }
    if (!feof(a))
    {
        fclose(a);
        fclose(b);
        return ERROR_READ;
    }
    fclose(a);
    fclose(b);
    return ans;
}


int Func8(const char *fname1, const char *fname2, const char *s, const char *r)//8
{
    FILE *a;
    FILE *b;
    char buf[LEN];
    char bufs[STR];
    char bufr[STR];
    int ans = 0;
    if (!(a = fopen(fname1, "r")))
        return ERROR_OPEN;
    if (!(b = fopen(fname2, "w")))
        return ERROR_OPEN;

    SR(bufs, bufr, s, r);
    while (fgets(buf, LEN, a))
    {
        buf[strlen(buf) - 1] = '\0';
        ans += Change8(b, buf, bufs, bufr);
    }
    if (!feof(a))
    {
        fclose(a);
        fclose(b);
        return ERROR_READ;
    }
    fclose(a);
    fclose(b);
    return ans;
}
