#include "student.h"
#include "sorts.h"

int main(int argc, char *argv[])
{
    char *fname = 0;
    int size;
    int ret;
    int max_print;
    time_t time;
    student *obj_a;
    student *obj_b;

    if ((argc != 3) || ((atoi(argv[2])) <= 0))
    {
        printf("Usage %s [file] size\n", argv[0]);
        return -1;
    }

    size = atoi(argv[2]);
    fname = argv[1];

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

    ret = readStudent(fname, size, obj_a);

    if (ret != student::SUCCESS)
    {
        switch(ret)
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
        delete [] obj_a;
        delete [] obj_b;
        return -1;
    }

    max_print = size;

    if (size > 10)
    {
        max_print = 10;
    }

    printObjects(obj_a, max_print);

    time = clock();
    mergeSort(obj_a, obj_b, size, siftUp);
    time = clock() - time;

    printObjects(obj_a, max_print);

    printf("Time = %lf\n", (double)time / CLOCKS_PER_SEC);

    delete [] obj_a;
    delete [] obj_b;
    return 0;
}
