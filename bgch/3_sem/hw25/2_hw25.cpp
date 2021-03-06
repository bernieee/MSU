#include "list.h"


int main(int argc, char *argv[])
{
    char *fname = 0;
    int max_print;
    int res;
    int len;
    time_t time;
    list *head;

    if (argc != 3 || atoi(argv[1]) <= 0)
    {
        printf("Usage %s max_print [file]\n", argv[0]);
        return -1;
    }

    max_print = atoi(argv[1]);
    fname = argv[2];

    head = new list();

    res = head->read(fname);

    if (res < 0)
    {
        switch(res)
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

        delete head;
        return -1;
    }

    len = head->getLength();

    if (max_print > len)
    {
        max_print = len;
    }

    head->print(max_print);

    time = clock();
    head->minSort();
    time = clock() - time;

    head->print(max_print);
    len = head->getLessThanPrevious();

    printf("Number of elements less than previous = %d\n\n", len);

    printf("Time = %lf\n", (double)time / CLOCKS_PER_SEC);

    head->del();
    delete head;

    return 0;
}
