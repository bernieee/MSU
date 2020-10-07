#include "student.h"
#include "sorts.h"

int main(int argc, char *argv[])
{
    char *fname1 = 0;
    char *fname2 = 0;
    int ans;
    int size1;
    int size2;
    int ret;
    int max_print;
    int formula1;
    int formula2;
    time_t time;
    student *obj_a;
    student *obj_b;

    if (((argc != 6) && (argc != 8)) || (atoi(argv[1]) <= 0) || (atoi(argv[2]) <= 0) || (atoi(argv[3]) < 0)
        || (atoi(argv[3]) > 4) || (argc == 6 && atoi(argv[4]) <= 0) || (argc == 8 && atoi(argv[5] <= 0))
        || (argc == 6 && atoi(argv[5]) <= 0) || (argc == 8 && atoi(argv[6] <= 0)))
    {
        printf("Usage %s max_print size1 formula1 [file1] size2 formula2 [file2]\n", argv[0]);
        return -1;
    }

    if (argc == 6)
    {
        size2 = atoi(argv[4]);
        formula2 = atoi(argv[5]);
    }


    if (argc == 8)
    {
        size2 = atoi(argv[5]);
        formula2 = atoi(argv[6]);
        fname1 = argv[4];
        fname2 = argv[7];
    }

    max_print = atoi(argv[1]);
    size1 = atoi(argv[2]);
    formula1 = atoi(argv[3]);

    student x(new_name, new_val);

    if (max_print > size)
    {
        max_print = size;
    }

    if (!(obj_a = new student[size]))
    {
        printf("Can not read an element!\n");
        return -1;
    }

    if (!(obj_b = new student[size]))
    {
        printf("Can not read an element!\n");
        delete [] obj_a;
        return -1;
    }


    if (formula1 == 0)
    {
        ret1 = readFile(fname1, size1, obj_a);
    }
    else
    {
        ret1 = readFormula(formula1, size1, obj_a);
    }

    if (formula2 == 0)
    {
        ret2 = readFile(fname2, size2, obj_b);
    }
    else
    {
        ret2 = readFormula(formula2, size2, obj_b);
    }


    if (ret1 != student::SUCCESS || ret2 != student::SUCCESS)
    {
        switch(ret1)
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
        delete [] obj;
        return -1;
    }

    printObjects(obj, max_print);

    time = clock();
    ans = binSearch(obj, x, size, siftUp);
    time = clock() - time;

    printf("Answer = %d\n", ans);

    printf("Time = %lf\n", (double)time / CLOCKS_PER_SEC);

    delete [] obj;
    return 0;
}
