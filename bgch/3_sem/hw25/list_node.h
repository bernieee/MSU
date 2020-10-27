#include "student.h"

class list_node: public student
{
    private:
        list_node *next = nullptr;

    public:
        list_node *getNext() const
        {
            return next;
        }

        void setNext(list_node *new_next)
        {
            next = new_next;
        }

        list_node() = default;

        list_node(const char *new_name, int new_val): student(new_name, new_val)
        {
            next = nullptr;
        }

        list_node(const list_node &x): student(x)
        {
            next = x.next;
        }

        list_node(list_node &&x): student(x)
        {
            next = x.next;
            x.next = nullptr;
        }

        ~list_node()
        {
            next = nullptr;
        }

        list_node &operator=(const list_node &x)
        {
            *(student *)(this) = x;
            next = nullptr;

            return *this;
        }

        list_node &operator=(list_node &&x)
        {
            *(student *)(this) = x;

            next = x.next;
            x.next = nullptr;

            return *this;
        }

        friend class list;
};
