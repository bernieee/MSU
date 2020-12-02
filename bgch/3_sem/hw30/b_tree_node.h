#include "student.h"
#include <math.h>

template <class T> class b_tree;
template <class T>
class b_tree_node: public T
{
    private:
        T *values = nullptr;
        b_tree_node **children = nullptr;
        int size = 0;

    public:
        b_tree_node() = default;

        b_tree_node(const b_tree_node &x): T((const T &)x)
        {
            values = x.values;
            children = x.children;
            size = x.size;
        }


        b_tree_node(b_tree_node &&x): T((T &&)x)
        {
            values = x.values;
            children = x.children;
            size = x.size;

            x.values = nullptr;
            x.children = nullptr;
            x.size = 0;
        }


        b_tree_node &operator=(const b_tree_node &x)
        {
            *(T *)(this) = (const T &) x;

            values = nullptr;
            children = nullptr;
            size = 0;

            return *this;
        }


        b_tree_node &operator=(b_tree_node &&x)
        {
            *(T *)(this) = (T &&) x;

            values = x.values;
            children = x.children;
            size = x.size;

            x.values = nullptr;
            x.children = nullptr;
            x.size = 0;

            return *this;
        }


        int init(int m)
        {
            values = new T[2 * m];
            children = new b_tree_node *[2 * m + 1];

            if (!values)
            {
                return student::MEMORY_ERROR;
            }

            if (!children)
            {
                return student::MEMORY_ERROR;
            }

            for (int i = 0; i < 2 * m + 1; i++)
            {
                children[i] = nullptr;
            }

            return student::SUCCESS;
        }


        int search(const T &x)
        {
            int left = 0;
            int right = size;

            while (right - left > 0)
            {
                int mid = left + (right - left) / 2;
                int res = (values[mid] < x);

                if (res == 1)
                {
                    left = mid + 1;
                }
                else if (res == -1)
                {
                    right = mid;
                }
                else
                {
                    return mid;
                }
            }

            return left;
        }


        friend class b_tree<T>;
};
