#include "hw8.h"
#include <string.h>
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
    ans = strspn_(argv[1], argv[2]);
    time = clock() - time;
    printf("Place = %d\n", ans);
    printf("Time = %lf\n", (double)time / CLOCKS_PER_SEC);
    return 0;
}
