#include "student.h"
#include "tree_node.h"
#include <time.h>

class tree
{
    private:
        tree_node *root = nullptr;
        void addNode(tree_node *x, tree_node *root=nullptr);

    public:
        tree() = default;
        ~tree();

        void del(tree_node *p);
        int read(const char *fname);
        void printNode(int max_print, int level, tree_node *p);
        void print(int max_print);

        int numOfLeafsRoot();
        int numOfLeafs(tree_node *p);
};
