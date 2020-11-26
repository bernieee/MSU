#include "list2_node.h"

class list2
{
    private:
        list2_node *head = nullptr;
        static int m;
        static int r;

    public:
        list2() = default;
        ~list2()
        {
            del();
        }

        static void setM(int m)
        {
            list2::m = m;
        }

        static void setR(int r)
        {
            list2::r = r;
        }

        int getLength() const;
        int read(FILE *f);
        void print(int spaces);
        void del();
        int operator<(const list2 &x);
};

