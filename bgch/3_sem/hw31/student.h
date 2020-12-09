#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include <new>

#ifndef STUDENT_H
#define STUDENT_H



class student
{
    private:
        char *name = nullptr;
        int val = 0;
        int init(const char *new_name, int new_val);

    public:
        enum ERRORS
        {
            SUCCESS = 0,
            OPEN_ERROR = -1,
            READ_ERROR = -2,
            MEMORY_ERROR = -3

        };
        int getVal() const
        {
            return val;
        }

        const char *getName() const
        {
            return name;
        }

        student() = default;
        student(const char *new_name, int new_val);
        student(const student &x);
        student(student &&x);
        ~student();
        student &operator=(const student &x);
        student &operator=(student &&x);
        int operator<(const student &x) const;
        void swap(student &x);
        int read(FILE *f);
        void print(int spaces) const;
        void remove();
};


#endif
