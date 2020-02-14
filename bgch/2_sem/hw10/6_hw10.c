#include <stdio.h>
#include <time.h>
#include "hw10.h"


int main(int argc, char **argv) 
{
    char *a;
    char *b;
    char *s;
    int result;
    clock_t time;

    if (argc != 4)
    {
        printf("You have only <%d> args instead of <4>\n", argc);
        return -1;
    }

    a = argv[1];      // filename1 to read
    b = argv[2];      // filename2 to write down
    s = argv[3];

    time = clock();
    result = Func6(a, b, s);
    time = clock() - time;
    printf("%d\n", result);
    printf("Time = %lf\n", (double)time / CLOCKS_PER_SEC);

    return 0;
}
