#include "hw11.h"
#include <stdio.h>
#include <string.h>


static int S(char *buf, char *s)
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


static int Remove(char *s, char *res, char x)//'.', '?', '+', '*' --> '!'
{
    int i;
    int j;
    i = 0;
    j = 0;
    while (s[i] != '\0')
    {
        if (s[i] == x)
        {
            if (s[i] != '.')
            {
                while ((s[i] == x) && (s[i + 1] == x))
                    i++;
            }
            res[j] = '!';
        }
        else if ((s[i] == '\\') && (s[i + 1] == '\\'))
        {
            i++;
            res[j] = s[i];
        }
        else if ((s[i] == '\\') && (s[i + 1] == x))
        {
            i++;
            res[j] = s[i];
        }
        else
            res[j] = s[i];
        i++;
        j++;
    }
    res[j] = s[i];
    printf("%s\n", res);
    return SUCCESS;
}


static int Str2words(char *s, char words[LEN][LEN], char *buft)//3
{
    int n;
    int i;
    int j;
    int flag;
    int len1;
    int len2;
    char buf[LEN];
    n = 0;
    i = 0;
    j = 0;
    flag = 0;
    len1 = 0;
    len2 = 0;
    while (s[i] != '\0')//put words in array
    {
        if ((buft[(int)s[i]] == 1) && (flag == 1))
        {
            words[j][0] = ' ';
            memcpy(words[j] + 1, buf + len2, len1);
            words[j][len1 + 1] = ' ';
            words[j][len1 + 2] = '\0';
            len2 += len1 + 1;
            len1 = 0;
            flag = 0;
            j++;
        }
        else
        {
            buf[i] = s[i];
            len1++;
            flag = 1;
        }
        i++;
    }
    words[j][0] = ' ';
    memcpy(words[j] + 1, buf + len2, len1);
    words[j][len1 + 1] = ' ';
    words[j][len1 + 2] = '\0';
    j++;

    //for (i = 0; i < j; i++)
    //    printf("%s\n", words[i]);
    return j;
}


static int Replace(char *buf, char *res, char *buft, int f)//1, 2, 3:f == 1 if buf, f == 0 if s
{
    int i;
    int j;
    int lens;
    int flag;
    lens = strlen(buf);
    i = 0;
    j = 0;
    flag = 0;;
    if (f == 1)
    {
        res[0] = ' ';
        j++;
    }
    if ((buf[0] == '\\') && (buf[1] == '<'))
    {
        res[0] = ' ';
        j++;
    }
    else if ((buf[lens - 1] == '>') && (buf[lens - 2] == '\\'))
    {
        flag = 1;
    }

    while (buf[i] != '\0')
    {
        if ((buf[i] == '\\') && (buf[i + 1] == '<'))
        {
            i += 2;
            if (buf[i] != '\0')
            {
                res[j] = buf[i];
                i++;
                j++;
            }
        }
        else if ((buf[i] == '\\') && (buf[i + 1] == '>'))
        {
            i += 2;
            if (buf[i] != '\0')
            {
                res[j] = buf[i];
                i++;
                j++;
            }
        }
        else if (buft[(int)buf[i]] == 1)
        {
            res[j] = ' ';
            i++;
            j++;
        }
        else
        {
            res[j] = buf[i];
            i++;
            j++;
        }
    }
    if (f == 1)
    {
        res[j] = ' ';
        j++;
    }
    if (flag == 1)
    {
        res[j] = ' ';
        j++;
    }
    res[j] = buf[i];
    return SUCCESS;
}


static int Find1(FILE *b, char *buf, char *s, char *buft)//1
{
    char string1[LEN];
    char string2[LEN];
    char *res;

    Replace(buf, string1, buft, 1);
    Replace(s, string2, buft, 0);
    res = strstr(string1, string2);
    if (res != NULL)
    {
        fprintf(b, "%s\n", buf);
        //printf("%s\n", string2);
        return 1;
    }
    else
        return 0;
}


static int Find2(FILE *b, char *buf, char *s, char *buft)//2
{
    char string1[LEN];
    char string2[LEN];
    char *res;

    Replace(buf, string1, buft, 1);
    Replace(s, string2, buft, 0);
    res = strstr (string1, string2);
    if (res != NULL)
    {
        fprintf(b, "%s\n", buf);
        //printf("%s\n", string2);
        return 1;
    }
    else
        return 0;
}


static int Find3(FILE *b, char *buf, char words[LEN][LEN], int num, char *buft)//3
{
    char string1[strlen(buf)];
    char *res;
    int i;

    Replace(buf, string1, buft, 1);
    for (i = 0; i < num; i++)
    {
        res = strstr(string1, words[i]);
        if (res != NULL)
        {
            fprintf(b, "%s\n", buf);
            //printf("%s\n", words[i]);
            return 1;
        }
    }
    if (res != NULL)
    {
        fprintf(b, "%s\n", buf);
        //printf("%s\n", words[i]);
        return 1;
    }
    else
        return 0;
}


static int Points(FILE *b, char *buf, char *s)//4
{
    int i;
    i = 0;
    while ((buf[i] != '\0') && (s[i] != '\0'))
    {
        if ((buf[i] != s[i]) && (s[i] != '!'))
            return 0;
        i++;
    }
    fprintf(b, "%s\n", buf);
    return 1;
}


static int Questions(FILE *b, char *buf, char *s)//5
{
    int i;
    int j;
    i = 0;
    j = 0;
    while ((buf[i] != '\0') && (s[j] != '\0'))
    {
        if ((buf[i] != s[j]) && (s[j] == '!'))
            j++;
        else if ((buf[i] != s[j]) && (s[j + 1] != '!'))
            return 0;
        else if ((buf[i] != s[j]) && (s[j + 1] == '!'))
            j++;
        else
        {
            i++;
            j++;
        }
    }
    if ((s[j] == '\0') && (buf[i] != '\0'))
        return 0;
    while (s[j] != '\0')
    {
        if ((s[j] != '!') && (s[j + 1] != '!'))
            return 0;
        j += 2;
    }
    fprintf(b, "%s\n", buf);
    return 1;
}

//seven oneeee one eleven

//seven one*eeee one eleven


static int Plus(FILE *b, char *buf, char *s)//6
{
    int i;
    int j;
    int num;
    char x;
    i = 0;
    j = 0;
    num = 0;
    while ((buf[i] != '\0') && (s[j] != '\0'))
    {
        if ((buf[i] != s[j]) && (s[j] == '!'))
            j++;
        else if (buf[i] != s[j])
            return 0;
        else if ((buf[i] == s[j]) && (s[j + 1] == '!'))
        {
            x = s[j];
            while (buf[i] == x)
            {
                i++;
                num++;
            }
            j += 2;

            while (s[j] == x)
            {
                if (s[j + 1] == '!')
                    j++;
                j++;
                num--;
            }
            if (num <= 0)
                return 0;
            num = 0;
        }
        else
        {
            i++;
            j++;
        }
    }
    fprintf(b, "%s\n", buf);
    return 1;
}


static int Stars(FILE *b, char *buf, char *s)//7
{
    int i;
    int j;
    int num;
    char x;
    i = 0;
    j = 0;
    num = 0;
    while ((buf[i] != '\0') && (s[j] != '\0'))
    {
        if ((buf[i] != s[j]) && (s[j] == '!'))
            j++;
        else if ((buf[i] != s[j]) && (s[j + 1] != '!'))
            return 0;
        else if ((buf[i] != s[j]) && (s[j + 1] == '!'))
            j++;
        else if ((buf[i] == s[j]) && (s[j + 1] == '!'))
        {
            x = s[j];
            while (buf[i] == x)
            {
                i++;
                num++;
            }
            j += 2;

            while (s[j] == x)
            {
                if (s[j + 1] == '!')
                    j += 2;
                else
                {
                    j++;
                    num--;
                }
            }
            if (num < 0)
                return 0;
            num = 0;
        }
        else
        {
            i++;
            j++;
        }
    }
    fprintf(b, "%s\n", buf);
    return 1;
}


static int Range(FILE *b, char *buf, char *s)//8
{
    int i;
    int j;
    int k;
    int n;
    int m;
    int len;
    char x;
    i = 0;
    j = 0;
    k = 0;
    len = 0;
//memcpy(words[j] + 1, buf + len2, len1);

    while ((buf[i] != '\0') && (s[j] != '\0'))
    {
        if ((buf[i] != s[j]) && (s[j] == '!'))
        {
            j++;
            n = (int)s[j];
            j += 2;
            m = (int)s[j];
            j += 2;
            printf("%d %d\n", m, n);
            if (((int)buf[i] >= n) && ((int)buf[i] <=m))
            {
                i++;
            }
            else
                return 0;
        }//asd[12-55]fdfds[34-56]gfd
        else if (buf[i] != s[j])
            return 0;
        else
        {
            i++;
            j++;
        }
    }
    printf("%s\n", buf);
    return 1;
}


//s is in string from a
//'\<string'  --  in the beginning of word; first coming in word
int Func1(const char *fname1, const char *fname2, char *s, char *t)//1
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
        if (Find1(b, buf, s, buft) == 1)
            ans++;
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


//s is in sting from a
//'string/>'  --  in the end of word; last coming in word
int Func2(const char *fname1, const char *fname2, char *s, char *t)//2
{
    FILE *a;
    FILE *b;
    char buf[LEN];
    char buft[STR];
    int ans = 0;
    int i = 0;
    if (!(a = fopen(fname1, "r")))
        return ERROR_OPEN;
    if (!(b = fopen(fname2, "w")))
        return ERROR_OPEN;

    S(buft, t);
    while (fgets(buf, LEN, a))
    {
        buf[strlen(buf) - 1] = '\0';
        if (Find2(b, buf, s, buft) == 1)
            ans++;
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


//string from a and s have common word
int Func3(const char *fname1, const char *fname2, char *s, char *t)//3
{
    FILE *a;
    FILE *b;
    char buf[LEN];
    char buft[STR];
    char words[LEN][LEN];

    int ans = 0;
    int num;

    if (!(a = fopen(fname1, "r")))
        return ERROR_OPEN;
    if (!(b = fopen(fname2, "w")))
        return ERROR_OPEN;

    S(buft, t);
    num = Str2words(s, words, buft);

    while (fgets(buf, LEN, a))
    {
        buf[strlen(buf) - 1] = '\0';
        if (Find3(b, buf, words, num, buft) == 1)
            ans++;
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


//string from a is equal to s
//'.' in s is any symbol in string from a;
//'\.' & '\\' are '/' & '\' in s
int Func4(const char *fname1, const char *fname2, char *s)//4
{
    FILE *a;
    FILE *b;
    char buf[LEN];
    char str[LEN];
    int ans = 0;
    if (!(a = fopen(fname1, "r")))
        return ERROR_OPEN;
    if (!(b = fopen(fname2, "w")))
        return ERROR_OPEN;

    Remove(s, str, '.');
    while (fgets(buf, LEN, a))
    {
        buf[strlen(buf) - 1] = '\0';
        if (Points(b, buf, str) == 1)
            ans++;
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


int Func5(const char *fname1, const char *fname2, char *s)//5
{
    FILE *a;
    FILE *b;
    char buf[LEN];
    char str[LEN];
    int ans = 0;
    if (!(a = fopen(fname1, "r")))
        return ERROR_OPEN;
    if (!(b = fopen(fname2, "w")))
        return ERROR_OPEN;

    Remove(s, str, '?');
    while (fgets(buf, LEN, a))
    {
        buf[strlen(buf) - 1] = '\0';
        if (Questions(b, buf, str) == 1)
            ans++;
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


int Func6(const char *fname1, const char *fname2, char *s)//6
{
    FILE *a;
    FILE *b;
    char buf[LEN];
    char str[LEN];
    int ans = 0;
    if (!(a = fopen(fname1, "r")))
        return ERROR_OPEN;
    if (!(b = fopen(fname2, "w")))
        return ERROR_OPEN;

    Remove(s, str, '+');
    while (fgets(buf, LEN, a))
    {
        buf[strlen(buf) - 1] = '\0';
        if (Plus(b, buf, str) == 1)
            ans++;
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


int Func7(const char *fname1, const char *fname2, char *s)//7
{
    FILE *a;
    FILE *b;
    char buf[LEN];
    char str[LEN];
    int ans = 0;
    if (!(a = fopen(fname1, "r")))
        return ERROR_OPEN;
    if (!(b = fopen(fname2, "w")))
        return ERROR_OPEN;

    Remove(s, str, '*');
    while (fgets(buf, LEN, a))
    {
        buf[strlen(buf) - 1] = '\0';
        if (Stars(b, buf, str) == 1)
            ans++;
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


int Func8(const char *fname1, const char *fname2, char *s)//8
{
    FILE *a;
    FILE *b;
    char buf[LEN];
    char str[LEN];
    int ans = 0;
    if (!(a = fopen(fname1, "r")))
        return ERROR_OPEN;
    if (!(b = fopen(fname2, "w")))
        return ERROR_OPEN;

    Remove(s, str, '[');
    Remove(str, str, ']');
    while (fgets(buf, LEN, a))
    {
        buf[strlen(buf) - 1] = '\0';
        if (Range(b, buf, str) == 1)
            ans++;
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


/*
seven eleven oneone
 nine tttttwo
ten twenty

 nine t*wo
 nine s*tttttwo
*/
