#ifndef record_H
#define record_H
#include <memory>
#include <stdio.h>
# include <string.h>
#include "condition.h"

enum class read_status
{
    success = 0,
    eof = -1,
    format = -2,
    memory = -3,
    read = -4,
};


class record
{
    private:
        std::unique_ptr<char []> name = nullptr;
        int phone = 0;
        int group = 0;
    public:
        record () = default;
        ~record () = default;

        char *get_name() const
        {
            return name.get();
        }
        int get_phone() const
        {
            return phone;
        }
        int get_group() const
        {
            return group;
        }

        int init (const char *n, int p, int g);
        // Allow as return value for functions

        record (record &&x) = default; // move constructor
        record& operator= (record&& x) = default; // Assignement move operator

        // Prohoibit pass by value
        // (it is default when move constructor is declared)
        record (const record &x) = delete;
        // Prohoibit assignement operator
        // (it is default when move constructor is declared)
        record& operator= (const record&) = delete;

        // Check condition ’x’ for field ’name’ for ’this’ and ’y’
        bool compare_name (condition x, record& y) const;

        // Check condition ’x’ for field ’phone’ for ’this’ and ’y’
        bool compare_phone (condition x, record& y) const;

        // Check condition ’x’ for field ’group’ for ’this’ and ’y’
        bool compare_group (condition x, record&  y) const;

        void print (FILE * fp = stdout);
        read_status read (FILE *fp = stdin);
};

# endif
