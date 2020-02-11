#include "hw8.h"
#define LEN 1234
//#define N 1<<28


int main(int argc, char* argv[])
{
    //int len;
    char string[LEN];
    time_t time;

    if (argc != 2)
    {
        printf("Usage %s file\n", argv[0]);
        return 1;
    }

    time = clock();
    test_str_(string, argv[1], &strcpy_);
    time = clock() - time;

    printf("String = %s\n", string);
    printf("Time = %lf\n", (double)time / CLOCKS_PER_SEC);


    time = clock();
    test_strcpy_(string, argv[1], &strcpy);
    time = clock() - time;

    printf("Std String = %s\n", string);
    printf("Std Time = %lf\n", (double)time / CLOCKS_PER_SEC);

    return 0;
}
