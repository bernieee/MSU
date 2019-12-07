#include "hw8.h"
#define LEN 1234


int main(int argc, char* argv[])
{
    int ans;
    time_t time;

    if (argc != 3)
    {
        printf("Usage %s file\n", argv[0]);
        return 1;
    }

    time = clock();
    ans = test_str_(argv[1], argv[2], &strcmp_);
    time = clock() - time;

    if (ans < 0)
        printf("string1 < string2\n");
    else if (ans == 0)
        printf("string1 == string2\n");
    else
        printf("string1 > string2\n");
    printf("Time = %lf\n", (double)time / CLOCKS_PER_SEC);


    time = clock();
    ans = test_str_(argv[1], argv[2], &strcmp);
    time = clock() - time;

    if (ans < 0)
        printf("string1 < string2\n");
    else if (ans == 0)
        printf("string1 == string2\n");
    else
        printf("string1 > string2\n");
    printf("Std Time = %lf\n", (double)time / CLOCKS_PER_SEC);


    return 0;
}
