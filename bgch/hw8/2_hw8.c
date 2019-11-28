#include "hw8.h"
#define LEN 1234


int main(int argc, char* argv[])
{
    int len;
    char string[LEN];

    if (argc != 2)
    {
        printf("Usage %s file\n", argv[0]);
        return 1;
    }

    strcpy_(string, argv[1]);
    printf("String = %s\n", string);
    return 0;
}
