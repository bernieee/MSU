#include "io_hw20.h"
#include "solve_hw20.h"


int main (int argc, char *argv[])
{
    int ans;
    int ret;
    double t;
    char *fname = 0;
    list *head;

    if (argc != 2)
    {
        printf("Usage %s [file]\n", argv[0]);
        return -1;
    }

    fname = argv[1];
    ret = read_list(fname, &head);

    if (ret != SUCCESS)
    {
        switch(ret)
        {
            case OPEN_ERROR:
                printf("Can not open file!\n");
                break;
            case MEMORY_ERROR:
                printf("Can not allocate memory!\n");
                break;
            case READ_ERROR:
                printf("Can not read an element!\n");
                break;
            default:
                printf("Unknown error!\n");

        }
        return -2;
    }

    print_list(head);

    t = clock();
    ans = maxlen_between_const_seqence(head);
    t = clock() - t;

    printf("Answer = %d\n", ans);
    printf("Elapsed = %.2f\n", t / CLOCKS_PER_SEC);

    delete_list(head);
    return 0;
}
