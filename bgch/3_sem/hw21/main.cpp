#include"student.h"

using namespace std;

int main(int argc, char *argv[])
{
    char *fname = 0;
    int size;
    int ret;
    int max_print;
    student *obj;

    if (argc != 3)
    {
        printf("Usage %s size [file]\n", argv[0]);
        return -1;
    }

    size = atoi(argv[1]);
    fname = argv[2];


    obj = new student[size];

    /*try
    {
        obj = new student[size];
    }
    catch (std::bad_alloc e)
    {
        printf("Can not allocate memory!\n");
        return -1;
    }*/

    ret = readStudent(fname, size, obj);

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
        delete [] obj;
        return -1;
    }

    max_print = size;

    if (size > 20)
    {
        max_print = 20;
    }

    for (int i = 0; i < max_print; i++)
    {
        obj[i].print();
    }

    delete [] obj;
    return 0;
}
