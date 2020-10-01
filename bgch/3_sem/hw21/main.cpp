#include"student.h"

int main(int argc, char *argv[])
{
    char *fname = 0;
    int size;
    int ret;
    int max_print;
    student *obj;

    if ((argc != 3) || ((atoi(argv[1])) <= 0))
    {
        printf("Usage %s size [file]\n", argv[0]);
        return -1;
    }

    size = atoi(argv[1]);
    fname = argv[2];

    if (!(obj = new student[size]))
    {
        printf("Can not read an element!\n");
        return -1;
    }

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

    if (size > 10)
    {
        max_print = 10;
    }

    for (int i = 0; i < max_print; i++)
    {
        obj[i].print();
    }

    delete [] obj;
    return 0;
}
