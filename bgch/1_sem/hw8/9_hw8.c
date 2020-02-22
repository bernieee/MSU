#include "hw8.h"
#include <string.h>
#define LEN 1234


int main(int argc, char* argv[])
{
   //int ch;
    int ans;
    time_t time;

    if (argc != 3)
    {
        printf("Usage %s file\n", argv[0]);
        return 1;
    }

    time = clock();
    ans = test_strcspn_(argv[1], argv[2], &strspn_);
    time = clock() - time;
    if (ans == 0)
        printf("No elements\n");
    else
    {
        printf("Place = %d\n", ans);
    }
    printf("Time = %lf\n", (double)time / CLOCKS_PER_SEC);

    time = clock();
    ans = test_strcspn_(argv[1], argv[2], &strspn);
    time = clock() - time;
    if (ans == 0)
        printf("Std No elements\n");
    else
    {
        printf("Std Place = %d\n", ans);
    }
    printf("Std Time = %lf\n", (double)time / CLOCKS_PER_SEC);


    return 0;
}
