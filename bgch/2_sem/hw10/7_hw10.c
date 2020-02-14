#include <stdio.h>
#include <time.h>
#include "hw10.h"


int main(int argc, char **argv) 
{
    char *a;
    char *b;
    char *s;
    char *l;
    char *r;
    int result;
    clock_t time;

    if (argc != 6)
    {
        printf("You have only <%d> args instead of <6>\n", argc);
        return -1;
    }

    a = argv[1];      // filename1 to read
    b = argv[2];      // filename2 to write down
    s = argv[3];
    l = argv[4];
    r = argv[5];
    
    time = clock();
    result = Func7(a, b, s, l, r);
    time = clock() - time;
    printf("%d\n", result);
    printf("Time = %lf\n", (double)time / CLOCKS_PER_SEC);

    return 0;
}
