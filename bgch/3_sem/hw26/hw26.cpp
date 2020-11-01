#include "tree.h"


int main(int argc, char *argv[])
{
    char *fname = 0;
    int max_print;
    int res;
    int ans1;
    time_t time;
    tree *root;

    if (argc != 3 || atoi(argv[1]) <= 0)
    {
        printf("Usage %s max_print [file]\n", argv[0]);
        return -1;
    }

    max_print = atoi(argv[1]);
    fname = argv[2];

    root = new tree();

    res = root->read(fname);

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

        delete root;
        return -1;
    }

//    printf("root = %d\n", root->getVal());

    root->print(max_print);

    time = clock();
    ans1 = root->numOfLeafsRoot();
    time = clock() - time;

    printf("Task = %d Result = %d Elapsed = %.2f\n", 1, ans1, (double)time / CLOCKS_PER_SEC);

    //root->del();
    delete root;

    return 0;
}
