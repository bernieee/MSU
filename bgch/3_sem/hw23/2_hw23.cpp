#include "solve_hw23.h"


int main(int argc, char *argv[])
{
    char *fname = 0;
    int max_print;
    int size;
    int ans;
    time_t time;
    list *head;

    if (argc != 3 || atoi(argv[1]) <= 0)
    {
        printf("Usage %s max_print [file]\n", argv[0]);
        return -1;
    }

    max_print = atoi(argv[1]);
    fname = argv[2];

    size = readList(fname, &head);

    if (size < 0)
    {
        switch(size)
        {
            case student::OPEN_ERROR:
                printf("Can not open file!\n");
                break;
            case student::MEMORY_ERROR:
                printf("Can not allocate memory!\n");
                break;
            case student::READ_ERROR:
                printf("Can not read an element!\n");
                break;
            default:
                printf("Unknown error!\n");

        }
        return -1;
    }

    if (max_print > size)
    {
        max_print = size;
    }

    printList(head, max_print);

    time = clock();
    ans = numOfElemsGreaterThanPrevious(head);
    time = clock() - time;

    printf("Answer = %d\n", ans);

    printf("Time = %lf\n", (double)time / CLOCKS_PER_SEC);

    delList(head);
    return 0;
}
