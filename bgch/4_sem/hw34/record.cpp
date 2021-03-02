# include "record.h"
# define LEN 1234

using namespace std;


int record::init(const char *n, int p, int g)
{
    phone = p;
    group = g;

    if (n)
    {
        name = std::make_unique<char []> (strlen(n) + 1);
        if (!name)
        {
            return -1;
        }
        strcpy(name.get(), n);
    }
    else
    {
        name = nullptr;
    }

    return 0;
}


read_status record::read(FILE *fp)
{
    char buf[LEN];
    name = nullptr;

    if (fscanf (fp, "%s%d%d", buf, &phone, &group) != 3)
    {
        if (feof(fp))
        {
            return read_status::eof;
        }

        return read_status::format;
    }
    if (init (buf, phone, group))
    {
        return read_status::memory;
    }
    return read_status::success;
}


bool record::compare_name(condition x, record& y) const
{
    int cmp = strcmp(name.get(), y.name.get());

    switch (x)
    {
        case condition::none:
            return true;
        case condition::eq:
            return cmp == 0;
        case condition::ne:
            return cmp != 0;
        case condition::lt:
            return cmp < 0;
        case condition::gt:
            return cmp > 0;
        case condition::le:
            return cmp <= 0;
        case condition::ge:
            return cmp >= 0;
        case condition::like:
            return false;
    }
    return false;
}


// Check condition ’x’ for field ’phone’ for ’this’ and ’y’
bool record::compare_phone(condition x, record& y) const
{
    switch (x)
    {
        case condition::none:
            return true;
        case condition::eq:
            return phone == y.phone;
            //return phone == y;
        case condition::ne:
            return phone != y.phone;
            //return phone != y;
        case condition::lt:
            return phone < y.phone;
            //return phone < y;
        case condition::gt:
            return phone > y.phone;
            //return phone > y;
        case condition::le:
            return phone <= y.phone;
            //return phone <= y;
        case condition::ge:
            return phone >= y.phone;
            //return phone >= y;
        case condition::like:
            return false;
    }
    return false;
}


bool record::compare_group(condition x, record& y) const
{
    switch (x)
    {
        case condition::none:
            return true;
        case condition::eq:
            return group == y.group;
            //return group == y;
        case condition::ne:
            return group != y.group;
            //return group != y;
        case condition::lt:
            return group < y.group;
            //return group < y;
        case condition::gt:
            return group > y.group;
            //return group > y;
        case condition::le:
            return group <= y.group;
            //return group <= y;
        case condition::ge:
            return group >= y.group;
            //return group >= y;
        case condition::like:
            return false;
    }
    return false;
}
