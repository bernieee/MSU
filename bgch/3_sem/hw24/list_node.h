#include "student.h"

class list_node: public student
{
    private:
        list_node *next = nullptr;
        list_node *prev = nullptr;

    public:
        list_node *getNext() const
        {
            return next;
        }

        list_node *getPrev() const
        {
            return prev;
        }

        void setNext(list_node *new_next)
        {
            next = new_next;
        }

        void setPrev(list_node *new_prev)
        {
            prev = new_prev;
        }

        list_node() = default;

        list_node(const char *new_name, int new_val): student(new_name, new_val)
        {
            next = nullptr;
            prev = nullptr;
        }

        list_node(const list_node &x): student(x)
        {
            next = x.next;
            prev = x.prev;
        }

        list_node(list_node &&x): student(x)
        {
            next = x.next;
            x.next = nullptr;

            prev = x.prev;
            x.prev = nullptr;
        }

        ~list_node()
        {
            next = nullptr;
            prev = nullptr;
        }

        list_node &operator=(const list_node &x)
        {
            *(student *)(this) = x;
            next = nullptr;
            prev = nullptr;

            return *this;
        }

        list_node &operator=(list_node &&x)
        {
            *(student *)(this) = x;

            next = x.next;
            x.next = nullptr;

            prev = x.prev;
            x.prev = nullptr;

            return *this;
        }

        friend class list;
};
