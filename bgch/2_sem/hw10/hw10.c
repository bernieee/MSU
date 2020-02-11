#include "hw10.h"

//prints string from a, if string != s, else prints r
int Func1(const char *fname1, const char *fname2, const char *s, const char *r)//1
{
    FILE *a;
    FILE *b;
    char buf[LEN];
    //char buft[STR];
    int ans = 0;
    if (!(a = fopen(fname1, "r")))
        return ERROR_OPEN;
    if (!(b = fopen(fname2, "w")))
        return ERROR_OPEN;

    //S(bufs, s);
    while (fgets(buf, LEN, a))
    {
        if (Cmp(buf, s, 0) == 1) // 1 is YES, 0 is NO
        {
            fprintf(b, "%s\n", r);
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

static int Cmp(char *buf, const char *s, char *buft)
{
    int i = 0;
    int j = 0;
    while (buf[i] != '\0')
    {
        if (buf[i] == s[j])
        {
            i++;
            j++;
        }
        else
        {
            //if (Skip(buf[i], t) == 1)
            if (buft == 0)
                break;
            else if (buft[(int)buf[i]] == 1)//если это пробелный символ
                i++;
            else
                break;
        }
    }
    if (buf[i] - s[i] == 0)
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
    //char bufs[STR];
    int ans = 0;
    if (!(a = fopen(fname1, "r")))
        return ERROR_OPEN;
    if (!(b = fopen(fname2, "w")))
        return ERROR_OPEN;

    T(buft, t);
    //S(bufs, s);
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
    for (int i = 0; i < 256; i++)
    {
        buft[i] = 0;
    }
    i = 0;
    while (t[i] != "\0")
    {
        buft[(int)t[i]] = 1;
    }
    return 0;
}


/*static int S(char *bufs, const char *s)
{
    int i = 0;
    while (s[i] != '\0')
    {
        bufs[(int)s[i]] = 1;
    }
    return 0;
}*/


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
    //char bufs[STR];
    int ans = 0;
    if (!(a = fopen(fname1, "r")))
        return ERROR_OPEN;
    if (!(b = fopen(fname2, "w")))
        return ERROR_OPEN;

    T(buft, t);
    //S(bufs, s);
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

