#include "hw8.h"
#define LEN 1234


int main(int argc, char* argv[])
{
   //int ch;
    char *ans;
    time_t time;

    if (argc != 3)
    {
        printf("Usage %s file\n", argv[0]);
        return 1;
    }

    time = clock();
    ans = test_strstr_(argv[1], argv[2], &strstr_);
    time = clock() - time;
    if (ans == 0)
        printf("No elements\n");
    else
    {
        printf("Place = %s\n", ans);
    }
    printf("Time = %lf\n", (double)time / CLOCKS_PER_SEC);

    time = clock();
    ans = test_strstr_(argv[1], argv[2], &strstr);
    time = clock() - time;
    if (ans == 0)
        printf("Std No elements\n");
    else
    {
        printf("Std Place = %s\n", ans);
    }
    printf("Std Time = %lf\n", (double)time / CLOCKS_PER_SEC);


    return 0;
}
