#include <stdio.h>
#include <time.h>
#include "hw11.h"


int main(int argc, char **argv)
{
    char *a;
    char *b;
    char *s;
    char *t;
    int result;
    clock_t time;

    if (argc != 5)
    {
        printf("You have only <%d> args instead of <5>\n", argc);
        return -1;
    }

    a = argv[1];      // filename1 to read
    b = argv[2];      // filename2 to write down
    s = argv[3];
    t = argv[4];

    time = clock();
    result = Func3(a, b, s, t);
    time = clock() - time;
    printf("%d\n", result);
    printf("Time = %lf\n", (double)time / CLOCKS_PER_SEC);

    return 0;
}
