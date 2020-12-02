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

        ~b_tree_node()
        {
            //delete [] values;
            //delete [] children;
            //delete [] values;
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

            //printf("left = %d  right = %d\n", left, right);


            while (right - left > 0)
            {
                int mid = left + (right - left) / 2;
                int res = (values[mid] < x);

                //printf("left = %d  right = %d  mid = %d\n", left, right, mid);

                if (res == 1)
                {
                    left = mid + 1;
                }
                else if (res == -1)
                {
                    //right = mid - 1;
                    right = mid;
                }
                else
                {
                    return mid;
                }
            }

            //printf("left = %d  right = %d\n", left, right);

            return left;
        }


        friend class b_tree<T>;
};
