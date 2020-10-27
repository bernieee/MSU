#include "student.h"


int readFile(const char *fname, int size, student *obj)
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

        ret = obj[i].readFileStudent(f);

        if (ret < 0)
        {
            fclose(f);
            return student::READ_ERROR;
        }
    }

    fclose(f);
    return student::SUCCESS;
}


int student::readFileStudent(FILE *f)
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

    if (init(new_name, new_val) != student::SUCCESS)
    {
        return student::MEMORY_ERROR;
    }

    return student::SUCCESS;
}


int readFormula(int formula, int size, student *obj)
{
    int ret;

    for (int i = 0; i < size; i++)
    {
        ret = obj[i].readFormulaStudent(formula, size, i);

        if (ret < 0)
        {
            printf("%d\n", ret);
            return student::READ_ERROR;
        }
    }

    return student::SUCCESS;
}


int student::readFormulaStudent(int formula, int size, int i)
{
    int new_val;

    new_val = 0;

    if (formula == 1)
    {
        new_val = i;
    }

    if (formula == 2)
    {
        new_val = size - i;
    }

    if (formula == 3)
    {
        new_val = i / 2;
    }

    if (formula == 4)
    {
        new_val = size - i / 2;
    }

    if (init("Student", new_val) != student::SUCCESS)
    {
        return student::MEMORY_ERROR;
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

    if (x.name == nullptr)
    {
        return -1;
    }

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

    if (x.name == nullptr)
    {
        return 1;
    }

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
