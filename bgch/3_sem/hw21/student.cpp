#include"student.h"

//student(const char *name=nullptr, int val=0); // constuctor
//student(const student &x); // copy-constructor
//student(student &&x); // move-constructor
//~student(); // destructor


int readStudent(const char *fname, int size, student *obj)
{
    FILE *f;

    if (!(f = fopen(fname, "r")))
    {
        return OPEN_ERROR;
    }

    for (int i = 0; i < size; i++)
    {
        obj[i].read(f);
    }

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


student::student(const char *new_name, int new_val)
{
    if (new_name != nullptr)
    {
        val = new_val;
        name = new char[strlen(new_name) + 1];

        strcpy(name, new_name);
    }
}


student::student(const student &x)
{
    val = x.val;
    name = new char[strlen(x.name) + 1];

    strcpy(name, x.name);
}


student::student(student &&x)
{
    val = x.val;
    name = new char[strlen(x.name) + 1];

    strcpy(name, x.name);
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
        name = new char[strlen(x.name) + 1];

        strcpy(name, x.name);
        val = x.val;
    }

    return *this;
}


