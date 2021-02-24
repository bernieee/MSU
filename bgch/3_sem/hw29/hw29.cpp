#include "tree.h"

int list2::m = 0;
int list2::r = 0;

int main(int argc, char *argv[])
{
    char *fname = 0;
    int res;
    int r;
    int m;
    int ans1;
    int ans2;
    int ans3;
    int ans4;
    int ans5;
    time_t time;

    if (argc != 4 || atoi(argv[1]) < 0 || atoi(argv[3]) < 0)
    {
        printf("Usage %s max_print [file] m\n", argv[0]);
        return -1;
    }

    r = atoi(argv[1]);
    fname = argv[2];
    m = atoi(argv[3]);

    list2::setR(r);
    list2::setM(m);


// student
    tree<student> *root1 = new tree<student>;

    res = root1->read(fname);

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

    root1->print(r);
    printf("\n");

    time = clock();
    ans1 = root1->numOfLeavesRoot();
    time = clock() - time;

    printf("%s : Task = %d Result = %d Elapsed = %.2f\n\n", argv[0], 1, ans1, (double)time / CLOCKS_PER_SEC);

    time = clock();
    ans2 = root1->maxLenOfBranchRoot();
    time = clock() - time;

    printf("%s : Task = %d Result = %d Elapsed = %.2f\n\n", argv[0], 2, ans2, (double)time / CLOCKS_PER_SEC);

    time = clock();
    ans3 = root1->maxNumOfElementsOnLevelRoot(ans2);
    time = clock() - time;

    printf("%s : Task = %d Result = %d Elapsed = %.2f\n\n", argv[0], 3, ans3, (double)time / CLOCKS_PER_SEC);

    time = clock();
    ans4 = root1->maxDifferenceBetweenNumOfElementsRoot();
    time = clock() - time;

    printf("%s : Task = %d Result = %d Elapsed = %.2f\n\n", argv[0], 4, ans4, (double)time / CLOCKS_PER_SEC);

    time = clock();
    ans5 = root1->numOfElementsWithOnlyChildRoot();
    time = clock() - time;

    printf("%s : Task = %d Result = %d Elapsed = %.2f\n\n", argv[0], 5, ans5, (double)time / CLOCKS_PER_SEC);

    delete root1;


// list2
    tree<list2> *root2 = new tree<list2>;

    res = root2->read(fname);

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

    root2->print(r);
    printf("\n");

    time = clock();
    ans1 = root2->numOfLeavesRoot();
    time = clock() - time;

    printf("%s : Task = %d Result = %d Elapsed = %.2f\n\n", argv[0], 1, ans1, (double)time / CLOCKS_PER_SEC);

    time = clock();
    ans2 = root2->maxLenOfBranchRoot();
    time = clock() - time;

    printf("%s : Task = %d Result = %d Elapsed = %.2f\n\n", argv[0], 2, ans2, (double)time / CLOCKS_PER_SEC);

    time = clock();
    ans3 = root2->maxNumOfElementsOnLevelRoot(ans2);
    time = clock() - time;

    printf("%s : Task = %d Result = %d Elapsed = %.2f\n\n", argv[0], 3, ans3, (double)time / CLOCKS_PER_SEC);

    time = clock();
    ans4 = root2->maxDifferenceBetweenNumOfElementsRoot();
    time = clock() - time;

    printf("%s : Task = %d Result = %d Elapsed = %.2f\n\n", argv[0], 4, ans4, (double)time / CLOCKS_PER_SEC);

    time = clock();
    ans5 = root2->numOfElementsWithOnlyChildRoot();
    time = clock() - time;

    printf("%s : Task = %d Result = %d Elapsed = %.2f\n\n", argv[0], 5, ans5, (double)time / CLOCKS_PER_SEC);

    delete root2;

    return 0;
}
