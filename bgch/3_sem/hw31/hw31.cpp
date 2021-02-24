#include "rb_tree.h"


int main(int argc, char *argv[])
{
    char *fname = 0;
    int res;
    int r;
    int k;
    int ans1;
    int ans2;
    int ans3;
    int ans4;
    int ans5;
    time_t time;

    if (argc != 4 || atoi(argv[1]) < 0 || atoi(argv[2]) < 1)
    {
        printf("Usage %s r k [file]\n", argv[0]);
        return -1;
    }

    r = atoi(argv[1]);
    k = atoi(argv[2]);
    fname = argv[3];


// student
    rb_tree<student> *root = new rb_tree<student>();

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

    root->print(r);
    printf("\n");

    time = clock();
    ans1 = root->numOfElementsInSubtreesWithNotMoreThanKNodesRoot(k);
    time = clock() - time;

    printf("%s : Task = %d Result = %d Elapsed = %.2f\n\n", argv[0], 1, ans1, (double)time / CLOCKS_PER_SEC);

    time = clock();
    ans2 = root->numOfElementsInSubtreesWithNotMoreThanKLevelsRoot(k);
    time = clock() - time;

    printf("%s : Task = %d Result = %d Elapsed = %.2f\n\n", argv[0], 2, ans2, (double)time / CLOCKS_PER_SEC);

    time = clock();
    ans3 = root->numOfElementsInSubtreesWithNotMoreThanKNodesOnAnyLevelRoot(k);
    time = clock() - time;

    printf("%s : Task = %d Result = %d Elapsed = %.2f\n\n", argv[0], 3, ans3, (double)time / CLOCKS_PER_SEC);

    time = clock();
    ans4 = root->numOfElementsOnKLevelRoot(k);
    time = clock() - time;

    printf("%s : Task = %d Result = %d Elapsed = %.2f\n\n", argv[0], 4, ans4, (double)time / CLOCKS_PER_SEC);

    time = clock();
    ans5 = root->numOfElementsInKBranchesRoot(k);
    time = clock() - time;

    printf("%s : Task = %d Result = %d Elapsed = %.2f\n\n", argv[0], 5, ans5, (double)time / CLOCKS_PER_SEC);

    delete root;

    return 0;
}
