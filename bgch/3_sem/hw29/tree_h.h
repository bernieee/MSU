#include "tree_node.h"
#include <time.h>
#include <math.h>

template <class T>
class tree
{
    private:
        tree_node<T> *root = nullptr;
        void addNode(tree_node<T> *x, tree_node<T> *root=nullptr);

    public:
        tree() = default;
        ~tree();

        void del(tree_node<T> *p);
        int read(const char *fname);
        void printNode(int r, int level, tree_node<T> *p);
        void print(int r);

        int numOfLeavesRoot();
        int numOfLeaves(tree_node<T> *p); // 1
        int maxLenOfBranchRoot();
        int maxLenOfBranch(tree_node<T> *p); // 2
        int maxNumOfElementsOnLevelRoot(int depth);
        void maxNumOfElementsOnLevel(tree_node<T> *p, int level, int *num_on_level, int *max); // 3
        int numOfNodesOnLevel(tree_node<T> *p, int level, int i_level); // 3
        int maxDifferenceBetwenDepthsRoot();
        int maxDifferenceBetwenDepths(tree_node<T> *p, int *depth); // 4
        int numOfElementsWithOnlyChildRoot();
        int numOfElementsWithOnlyChild(tree_node<T> *p); // 5

};
