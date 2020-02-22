#include "hw8.h"


int main(int argc, char* argv[])
{
    int len;

    if (argc != 2)
    {
        printf("Usage %s file\n", argv[0]);
        return 1;
    }

    len = strlen_(argv[1]);
    printf("Length = %d\n", len);
    return 0;
}
