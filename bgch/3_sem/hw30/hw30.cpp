#include "b_tree.h"


int main(int argc, char *argv[])
{
    char *fname = 0;
    int res;
    int r;
    int k;
    int m;
    int ans1;
    int ans2;
    int ans3;
    int ans4;
    int ans5;
    int ans6;
    time_t time;

    if (argc != 5 || atoi(argv[1]) < 1 || atoi(argv[2]) < 0 || atoi(argv[3]) < 1)
    {
        printf("Usage %s m r k [file]\n", argv[0]);
        return -1;
    }

    m = atoi(argv[1]);
    r = atoi(argv[2]);
    k = atoi(argv[3]);
    fname = argv[4];


// student
    b_tree<student> *root = new b_tree<student>();
    root->init(m);

    /*if (root->init(m) != student::SUCCESS)
    {
        printf("Can not allocate memory!!!\n");

        delete root;
        return -1;
    }*/


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
    ans1 = root->numOfElementsWithKChildsRoot(k);
    time = clock() - time;

    printf("%s : Task = %d Result = %d Elapsed = %.2f\n\n", argv[0], 1, ans1, (double)time / CLOCKS_PER_SEC);

    time = clock();
    ans2 = root->numOfSubtreesWithNotMoreThanKNodesRoot(k);
    time = clock() - time;

    printf("%s : Task = %d Result = %d Elapsed = %.2f\n\n", argv[0], 2, ans2, (double)time / CLOCKS_PER_SEC);

    time = clock();
    ans3 = root->numOfSubtreesWithNotMoreThanKLevelsRoot(k);
    time = clock() - time;

    printf("%s : Task = %d Result = %d Elapsed = %.2f\n\n", argv[0], 3, ans3, (double)time / CLOCKS_PER_SEC);

    time = clock();
    ans4 = root->numOfSubtreesWithNotMoreThanKNodesOnAnyLevelRoot(k);
    time = clock() - time;

    printf("%s : Task = %d Result = %d Elapsed = %.2f\n\n", argv[0], 4, ans4, (double)time / CLOCKS_PER_SEC);

    time = clock();
    ans5 = root->numOfElementsOnKLevelRoot(k);
    time = clock() - time;

    printf("%s : Task = %d Result = %d Elapsed = %.2f\n\n", argv[0], 5, ans5, (double)time / CLOCKS_PER_SEC);

    time = clock();
    ans6 = root->numOfElementsInKBranchesRoot(k);
    time = clock() - time;

    printf("%s : Task = %d Result = %d Elapsed = %.2f\n\n", argv[0], 6, ans6, (double)time / CLOCKS_PER_SEC);


    delete root;

    return 0;
}
