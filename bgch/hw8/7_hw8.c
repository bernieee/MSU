#include "hw8.h"
#define LEN 1234


int main(int argc, char* argv[])
{
    const char *ans;

    if (argc != 3)
    {
        printf("Usage %s file\n", argv[0]);
        return 1;
    }

    ans = strrchr_(argv[1], (int)argv[2][0]);
    if (ans == 0)
        printf("No elements\n");
    else
    {
        printf("Place = %s\n", ans);
    }
    return 0;
}
