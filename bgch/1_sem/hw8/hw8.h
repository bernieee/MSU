#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N (1 << 28)


int aA(char c);
int strlen_(const char *string);//1
char *strcpy_(char *string1, const char* string2);//2
char *strcat_(char *string1, const char* string2);//3
int  strcmp_(const char *string1, const char* string2);//4
int  strcasecmp_(const char *string1, const char* string2);//5
char *strchr_(const char *string, int ch);//6
char *strrchr_(const char *string, int ch);//7
long unsigned int strcspn_(const char *string1, const char *string2);//8
long unsigned int strspn_(const char *string1, const char *string2);//8
char *strstr_(const char *string1, const char *string2);//10
//char * (*p)(const char *, int);
char *test_strch_(const char *string1, int string2, char * (*p)(const char *, int));
char *test_strrch_(const char *string1, int string2, char * (*p)(const char *, int));
char *test_strstr_(const char *string1, const char *string2, char * (*p)(const char *, const char *));
long unsigned int test_strcspn_(const char *string1, const char *string2, long unsigned int (*p)(const char *, const char *));
