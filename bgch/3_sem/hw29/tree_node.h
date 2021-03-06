#include "list2.h"

template <class T> class tree;
template <class T>
class tree_node: public T
{
    private:
        tree_node *left = nullptr;
        tree_node *right = nullptr;

    public:
        tree_node() = default;
        ~tree_node()
        {
            left = nullptr;
            right = nullptr;
        }

        tree_node *getLeft() const
        {
            return left;
        }

        tree_node *getRight() const
        {
            return right;
        }

        tree_node(const tree_node &x): T((const T &)x)
        {
            left = x.left;
            right = x.right;
        }

        tree_node(tree_node &&x): T((T &&)x)
        {
            left = x.left;
            x.left = nullptr;

            right = x.right;
            x.right = nullptr;
        }

        tree_node &operator=(const tree_node &x)
        {
            *(T *)(this) = (const T &) x;

            left = nullptr;
            right = nullptr;

            return *this;
        }

        tree_node &operator=(tree_node &&x)
        {
            *(T *)(this) = (T &&) x;

            left = x.left;
            x.left = nullptr;

            right = x.right;
            x.right = nullptr;

            return *this;
        }

        friend class tree<T>;
};
