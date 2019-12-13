#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "hw8.h"


int strlen_(const char *string)//1
{
    int len = 0;
    while (string[len] != '\0')
        len++;
    return len;
}


char *strcpy_(char *string1, const char *string2)//2
{
    int len = 0;
    //while (*(string1++) = *(string2++))
    while (string2[len] != '\0')
    {
        string1[len] = string2[len];
        len++;
    }
    string1[len] = '\0';
    return string1;
}


char *strcat_(char *string1, const char *string2)//3
{
    int len1;
    int len2;
    len1 = strlen_(string1);
    len2 = 0;
    while (string2[len2] != '\0')
    {
        string1[len1] = string2[len2];
        len1++;
        len2++;
    }
    string1[len1] = '\0';
    return string1;
}


int strcmp_(const char *string1, const char *string2)//4
{
    int i = 0;
    while ((string1[i] != '\0') && (string1[i] == string2[i]))
        i++;
    return string1[i] - string2[i];
}


int aA(char c)
{
    if ((int)c < 97)
        return (int)c + 32;
    return (int)c;
}


int strcasecmp_(const char *string1, const char *string2)//5
{
    int i = 0;
    while ((string1[i] != '\0') && (aA(string1[i]) == aA(string2[i])))
        i++;
    return string1[i] - string2[i];
}


char *strchr_(const char *string, int ch)//6
{
    while((*string) != '\0')
    {
        if ((int)(*string) == ch)
            break;
        string++;
    }
    return (char *)string;
}


char *strrchr_(const char *string, int ch)//7
{
    int i;
    int len;
    len = strlen_(string);
    for (i = len - 1; i >= 0; i--)
    {
        if((int)string[i] == ch)
            break;
    }
    if (i == 0)
        return 0;
    return (char *)(string + i);
}


int strcsnp_(const char *string1, const char *string2)//8
{
    int i;
    int j;
    i = 0;
    while (string1[i] != '\0')
    {
        j = 0;
        while (string2[j] != '\0')
        {
            if (string2[j] == string1[i])
                return i;
            j++;
        }
        i++;
    }
    return i;
}


int strsnp_(const char *string1, const char *string2)//9
{
    int i;
    int j;
    int k;
    i = 0;
    while (string1[i] != '\0')
    {
        j = 0;
        k = 0;
        while (string2[j] != '\0')
        {
            if (string2[j] != string1[i])
                k++;
            j++;
        }
        if (k == j)
            return i;
        i++;
    }
    return i;
}


const char *strstr_(const char *string1, const char *string2)//10
{
    int i;
    int j;
    int tmp;
    i = 0;
    while (string1[i] != '\0')
    {
        j = 0;
        if (string1[i] == string2[j])
        {
            tmp = i;
            while ((string1[tmp] != '\0') && (string1[tmp] == string2[j]))
            {
                tmp++;
                j++;
            }
        }
        if (string2[j] == '\0')
            break;
        else
            i++;
    }
    if (string1[i] == '\0')
        return 0;
    return (string1 + i);
}
