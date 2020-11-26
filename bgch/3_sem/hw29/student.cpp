#include "student.h"


int student::read(FILE *f)
{
    char new_name[256];
    int new_val;

    if (!new_name)
    {
        return student::MEMORY_ERROR;
    }

    if (fscanf(f, "%s%d", new_name, &new_val) != 2)
    {
        return student::READ_ERROR;
    }

    remove();

    if (init(new_name, new_val) != student::SUCCESS)
    {
        return student::MEMORY_ERROR;
    }

    return student::SUCCESS;
}


void student::print(int spaces) const
{
    for (int i = 0; i < spaces; i++)
    {
        printf(" ");
    }

    printf("%s %d\n", name, val);
}


int student::init(const char *new_name, int new_val)
{
    val = new_val;

    if (new_name)
    {
        name = new char[strlen(new_name) + 1];

        if (!name)
        {
            return student::MEMORY_ERROR;
        }

        strcpy(name, new_name);
    }
    else
    {
        name = nullptr;
    }

    return student::SUCCESS;
}


void student::remove()
{
    if (name != nullptr)
    {
        delete [] name;
        name = nullptr;
    }
    val = 0;
}


student::student(const char *new_name, int new_val)
{
    init(new_name, new_val);
}


student::~student()
{
    remove();
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
        remove();
        init(x.name, x.val);
    }

    return *this;
}


student &student::operator=(student &&x)
{
    val = x.val;
    name = x.name;

    x.val = 0;
    x.name = nullptr;

    return *this;
}


int student::operator<(const student &x) const
{
    int cmp;

    if (x.name == nullptr)
    {
        return -1;
    }

    cmp = strcmp(name, x.name);

    if (cmp == 0)
    {
        //return val < x.val;
        if (val < x.val)
            return 1;
        else if (val > x.val)
            return -1;
        else
            return 0;
    }
    else
    {
        //return cmp < 0;
        if (cmp < 0)
            return 1;
        else if (cmp > 0)
            return -1;
        else
            return 0;
    }
}


void student::swap(student &x)
{
    char *tmp_name;
    int tmp_val;

    tmp_name = name;
    name = x.name;
    x.name = tmp_name;

    tmp_val = val;
    val = x.val;
    x.val = tmp_val;
}
