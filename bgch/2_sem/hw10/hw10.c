#include "hw10.h"

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

    lens = strlen(s);
    lenr = strlen(r);
    while (fgets(buf, LEN, a))
    {
        if (Change(b, buf, s, r) == 1) // 1 is YES, 0 is NO
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
            else
                return 0;
        }
    }
    if (buf[i] - s[j] == 0)
        return 1;
    else
        return 0;
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

    T(buft, t);
    while (fgets(buf, LEN, a))
    {
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


static int T(char *buft, const char *t)
{
    int i;
    for (i = 0; i < 256; i++)
    {
        buft[i] = 0;
    }
    i = 0;
    while (t[i] != '\0')
    {
        buft[(int)t[i]] = 1;
        i++;
    }
    return 0;
}


static int S(char *bufs, const char *s)
{
    int i;
    for (i = 0; i < 256; i++)
    {
        bufs[i] = 0;
    }
    i = 0;
    while (s[i] != '\0')
    {
        buft[(int)s[i]] = 1;
        i++;
    }
    return 0;
}


/*static int Skip(char x, const char *t)
{
    int ans = 0;
    int i = 0;
    while (t[i] != '\0')
    {
        if (t[i] == x)
        {
            ans = 1;
            break;
        }
    }
    return ans;
}*/


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

    T(buft, t);
    S(bufs, s);
    while (fgets(buf, LEN, a))
    {
        if (CmpBin(buf, bufs, buft) == 1)
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


static int CmpBin(char *buf, char *bufs, char *buft)
{
    for (int i = 0; buf[i]; i++)
    {
        if ((bufs[(int)buf[i]] == 0) && (buft[(int)buf[i]] == 0))
            return 0;
    }
    return 1;
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

    T(buft, t);
    while (fgets(buf, LEN, a))
    {
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
    if (flag == 1)
        return 1;
    else
        return 0;
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
        if (Change8(b, buf, s, r) == 1)
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


static int Change8(FILE *b, char *buf, const char *s, const char *r)
{
    char * res;
    int lens;
    int flag;
    int i;
    lens = strlen(s);
    lens = strlen(s);
    i = 0;
    flag = 0;

    while (buf[i] != '\0')
    {
         for (int i = 0; buf[i]; i++)
         {
            if ((bufs[(int)buf[i]] == 0) && (buft[(int)buf[i]] == 0))
                return 1;
            flag = 1;
            while ((buf + i) != res)
            {
                fprintf(b, "%c", buf[i]);
                i++;
            }
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
    if (flag == 1)
        return 1;
    else
        return 0;
}


static int SR(char *bufs, char *bufr, const char *s, const char *r)
{
    int i;
    int lens;
    int lenr;
    lens = strlen(s);
    lenr = strlen(r);
    for (i = 0; i < 256; i++)
    {
        bufs[i] = 0;
        bufr[i] = 0;
    }
    i = 0;
    while (s[i] != '\0')
    {
        buft[(int)s[i]] = 1;
        i++;
    }
    return 0;
}

