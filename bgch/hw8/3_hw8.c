#include "hw8.h"
#define LEN 1234


int main(int argc, char* argv[])
{
    int len;
    char string[LEN];

    if (argc != 3)
    {
        printf("Usage %s file\n", argv[0]);
        return 1;
    }

    strcpy_(string, argv[1]);
    strcat_(string, argv[2]);
    printf("Stringcat = %s\n", string);
    return 0;
}
