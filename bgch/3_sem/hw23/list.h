#include "student.h"

class list: public student
{
    private:
        list *next = nullptr;

    public:
        list *getNext() const
        {
            return next;
        }

        void setNext(list *new_next)
        {
            next = new_next;
        }

        list() = default;

        list(const char *new_name, int new_val): student(new_name, new_val)
        {
            next = nullptr;
        }

        list(const list &x): student(x)
        {
            next = x.next;//?
            //next = nullptr;
        }

        list(list &&x): student(x)
        {
            next = x.next;
            x.next = nullptr;
        }

        ~list()
        {
            next = nullptr;
        }

        list &operator=(const list &x)
        {
            *(student *)(this) = x;
            next = nullptr;

            return *this;
        }

        list &operator=(list &&x)
        {
            *(student *)(this) = x;
            next = x.next;
            x.next = nullptr;

            return *this;
        }
        //int operator>(const list &x) const;
        //int operator<(const list &x) const;
};


int readList(const char *fname, list **head);
void delList(list *head);
void printList(list *head, int max_print);
