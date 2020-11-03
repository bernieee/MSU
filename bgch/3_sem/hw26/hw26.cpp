#include "tree.h"


int main(int argc, char *argv[])
{
    char *fname = 0;
    int max_print;
    int res;
    int ans1;
    int ans2;
    int ans4;
    int ans5;
    time_t time;
    tree root;

    if (argc != 3 || atoi(argv[1]) <= 0)
    {
        printf("Usage %s max_print [file]\n", argv[0]);
        return -1;
    }

    max_print = atoi(argv[1]);
    fname = argv[2];

    res = root.read(fname);

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

        return -1;
    }

    root.print(max_print);
    printf("\n");

    time = clock();
    ans1 = root.numOfLeavesRoot();
    time = clock() - time;

    printf("Task = %d Result = %d Elapsed = %.2f\n\n", 1, ans1, (double)time / CLOCKS_PER_SEC);

    time = clock();
    ans2 = root.maxLenOfBranchRoot();
    time = clock() - time;

    printf("Task = %d Result = %d Elapsed = %.2f\n\n", 2, ans2, (double)time / CLOCKS_PER_SEC);

    time = clock();
    ans4 = root.maxDifferenceBetwenDepthsRoot();
    time = clock() - time;

    printf("Task = %d Result = %d Elapsed = %.2f\n\n", 4, ans4, (double)time / CLOCKS_PER_SEC);

    time = clock();
    ans5 = root.numOfElementsWithOnlyChildRoot();
    time = clock() - time;

    printf("Task = %d Result = %d Elapsed = %.2f\n\n", 5, ans5, (double)time / CLOCKS_PER_SEC);



    return 0;
}
