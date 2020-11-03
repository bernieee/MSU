#include "student.h"
#include "tree_node.h"
#include <time.h>
#include <math.h>

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

        int numOfLeavesRoot();
        int numOfLeaves(tree_node *p); // 1
        int maxLenOfBranchRoot();
        int maxLenOfBranch(tree_node *p); // 2
        int maxNumOfElementsOnLevelRoot();
        int maxNumOfElementsOnLevel(tree_node *p); // 3
        int numOfElementsWithOnlyChildRoot();
        int maxDifferenceBetwenDepthsRoot();
        void maxDifferenceBetwenDepths(tree_node *p, int *max_depth); // 4
        int numOfElementsWithOnlyChild(tree_node *p); // 5
};
