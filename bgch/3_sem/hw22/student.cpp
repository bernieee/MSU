#include "student.h"


int readStudent(const char *fname, int size, student *obj)
{
    FILE *f;
    int ret;

    if (!(f = fopen(fname, "r")))
    {
        return student::OPEN_ERROR;
    }

    for (int i = 0; i < size; i++)
    {
        if (feof(f))
        {
            fclose(f);
            return student::READ_ERROR;
        }
        ret = obj[i].read(f);
        if (ret < 0)
        {
            fclose(f);
            return student::READ_ERROR;
        }
    }

    fclose(f);
    return student::SUCCESS;
}


int student::read(FILE *f)
{
    name = new char[256];

    if (!name)
    {
        return student::MEMORY_ERROR;
    }

    if (!fscanf(f, "%s%d", name, &val))
    {
        return student::READ_ERROR;
    }

    return student::SUCCESS;
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
        if (name != nullptr)
        {
            delete [] name;
            name = nullptr;
        }
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
    cmp = strcmp(name, x.name);

    if (cmp == 0)
    {
        return val < x.val;
    }
    else
    {
        return cmp < 0;
    }
}


int student::operator>(const student &x) const
{
    int cmp;
    cmp = strcmp(name, x.name);

    if (cmp == 0)
    {
        return val > x.val;
    }
    else
    {
        return cmp > 0;
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
