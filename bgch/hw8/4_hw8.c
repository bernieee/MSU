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

    ans = strcmp_(argv[1], argv[2]);

    if (ans < 0)
        printf("string1 < string2\n");
    else if (ans == 0)
        printf("string1 == string2\n");
    else
        printf("string1 > string2\n");
    return 0;
}
