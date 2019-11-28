#include "hw8.h"
#define LEN 1234


int main(int argc, char* argv[])
{
    int ans;

    if (argc != 3)
    {
        printf("Usage %s file\n", argv[0]);
        return 1;
    }

    printf("%s\n", argv[1]);
    printf("%s\n", argv[2]);
    ans = strsnp_(argv[1], argv[2]);
    printf("Place = %d\n", ans);
    return 0;
}
