#include"student.h"


int readStudent(const char *fname, int size, student *obj)
{
    FILE *f;
    int ret;

    if (!(f = fopen(fname, "r")))
    {
        return OPEN_ERROR;
    }

    for (int i = 0; i < size; i++)
    {
        if (feof(f))
        {
            fclose(f);
            return READ_ERROR;
        }
        ret = obj[i].read(f);
        if (ret < 0)
        {
            fclose(f);
            return READ_ERROR;
        }
    }

    fclose(f);
    return SUCCESS;
}


int student::read(FILE *f)
{
    name = new char[256];

    if (!name)
    {
        return MEMORY_ERROR;
    }

    if (!fscanf(f, "%s%d", name, &val))
    {
        return READ_ERROR;
    }

    return SUCCESS;
}


void student::print() const
{
    printf("%s %d\n", name, val);
}


int student::init(const char *new_name, int new_val)
{
    val = new_val;

    if (new_name != nullptr)
    {
        name = new char[strlen(new_name) + 1];

        if (!name)
        {
            return MEMORY_ERROR;
        }

        strcpy(name, new_name);
    }
    else
    {
        name = nullptr;
    }

    return SUCCESS;
}


student::student(const char *new_name, int new_val)
{
    init(new_name, new_val);
}


student::~student()
{
    if (name != nullptr)
    {
        delete [] name;
        name = nullptr;
    }
    val = 0;
}


student::student(const student &x) // copy-constructor
{
    init(x.name, x.val);
}


student::student(student &&x) // move-constructor
{
    val = x.val;
    name = x.name;

    x.val = 0;
    x.name = nullptr;
}


student &student::operator=(const student &x)
{
    if (this != &x)
    {
        delete [] name;
        name = new char[strlen(x.name) + 1];

        strcpy(name, x.name);
        val = x.val;
    }

    return *this;
}


student &student::operator=(student &&x)
{
    if (this != &x)
    {
        delete [] name;
        name = x.name;
        val = x.val;

        x.name = nullptr;
    }

    return *this;
}
