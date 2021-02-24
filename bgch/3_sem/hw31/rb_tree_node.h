#include "student.h"
#include <math.h>

template <class T> class rb_tree;
template <class T>
class rb_tree_node: public T
{
    enum colors
    {
        invalid,
        red,
        black,
    };

    private:
        rb_tree_node *left = nullptr;
        rb_tree_node *right = nullptr;
        colors color = black;

    public:
        rb_tree_node() = default;

        rb_tree_node(const rb_tree_node &x): T((const T &)x)
        {
            left = nullptr;
            right = nullptr;
            color = invalid;
        }


        rb_tree_node(rb_tree_node &&x): T((T &&)x)
        {
            left = x.left;
            right = x.right;
            color = x.color;

            x.left = nullptr;
            x.right = nullptr;
            x.color = invalid;
        }


        rb_tree_node &operator=(const rb_tree_node &x)
        {
            *(T *)(this) = (const T &) x;

            left = nullptr;
            right = nullptr;
            color = invalid;

            return *this;
        }


        rb_tree_node &operator=(rb_tree_node &&x)
        {
            *(T *)(this) = (T &&) x;

            left = x.left;
            right = x.right;
            color = x.color;

            x.left = nullptr;
            x.right = nullptr;
            x.color = invalid;

            return *this;
        }

        friend class rb_tree<T>;
};
