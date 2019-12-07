#include "hw8.h"


//int test_str_(const char *string1, const char *string2, int (*p)(const char *, const char *));
//int (*p)(const char *, const char *);

char *test_strch_(const char *string1, int string2, char * (*p)(const char *, int))
{
    int i;
    char *res = 0;
    for (i = 0; i < N; i++)
    {
        res = (*p)(string1, string2);
    }
    return res;
}


char *test_strrch_(const char *string1, int string2, char * (*p)(const char *, int))
{
    int i;
    char *res = 0;
    for (i = 0; i < N; i++)
    {
        res = (*p)(string1, string2);
    }
    return res;
}
