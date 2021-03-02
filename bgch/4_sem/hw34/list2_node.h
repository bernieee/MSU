#ifndef list2_node_H
#define list2_node_H
#include "record.h"

template <class T> class list2;
template <class T>
class list2_node: public T
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

        list2_node() = default;

        list2_node(const list2_node &x): T((const T &)x)
        {
            next = x.next;
            prev = x.prev;
        }

        list2_node(list2_node &&x): T((T &&)x)
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
            *(T *)(this) = (const T &) x;
            next = nullptr;
            prev = nullptr;

            return *this;
        }

        list2_node &operator=(list2_node &&x)
        {
            *(T *)(this) = (T &&) x;

            next = x.next;
            x.next = nullptr;

            prev = x.prev;
            x.prev = nullptr;

            return *this;
        }

        friend class list2<T>;
};

#endif
