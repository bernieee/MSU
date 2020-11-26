#include "student.h"

class tree_node: public student
{
    private:
        tree_node *down = nullptr;
        tree_node *level = nullptr;

    public:
        tree_node() = default;
        ~tree_node()
        {
            down = nullptr;
            level = nullptr;
        }

        tree_node *getDown() const
        {
            return down;
        }

        tree_node *getLevel() const
        {
            return level;
        }

        tree_node(const char *new_name, int new_val): student(new_name, new_val)
        {
            down = nullptr;
            level = nullptr;
        }

        tree_node(const tree_node &x): student(x)
        {
            down = x.down;
            level = x.level;
        }

        tree_node(tree_node &&x): student(x)
        {
            down = x.down;
            x.down = nullptr;

            level = x.level;
            x.level = nullptr;
        }

        tree_node &operator=(const tree_node &x)
        {
            //*(student *)(this) = (const student &) x;
            *(student *)(this) = x;
            down = nullptr;
            level = nullptr;

            return *this;
        }

        tree_node &operator=(tree_node &&x)
        {
            //*(student *)(this) = (student &&) x;
            *(student *)(this) = x;

            down = x.down;
            x.down = nullptr;

            level = x.level;
            x.level = nullptr;

            return *this;
        }

        friend class tree;
};
