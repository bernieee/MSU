#include "student.h"

class list2_node: public student
{
    private:
        list2_node *next = nullptr;
        list2_node *prev = nullptr;

    public:
        list2_node *getNext() const
        {
            return next;
        }

        list2_node *getPrev() const
        {
            return prev;
        }

        void setNext(list2_node *new_next)
        {
            next = new_next;
        }

        void setPrev(list2_node *new_prev)
        {
            prev = new_prev;
        }

        list2_node() = default;

        list2_node(const char *new_name, int new_val): student(new_name, new_val)
        {
            next = nullptr;
            prev = nullptr;
        }

        list2_node(const list2_node &x): student((const student &) x)
        {
            next = x.next;
            prev = x.prev;
        }

        list2_node(list2_node &&x): student((student &&) x)
        {
            next = x.next;
            x.next = nullptr;

            prev = x.prev;
            x.prev = nullptr;
        }

        ~list2_node()
        {
            next = nullptr;
            prev = nullptr;
        }

        list2_node &operator=(const list2_node &x)
        {
            *(student *)(this) = (const student &) x;
            next = nullptr;
            prev = nullptr;

            return *this;
        }

        list2_node &operator=(list2_node &&x)
        {
            *(student *)(this) = (student &&) x;

            next = x.next;
            x.next = nullptr;

            prev = x.prev;
            x.prev = nullptr;

            return *this;
        }

        friend class list2;
};
