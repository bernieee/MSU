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

        int numOfNodes(tree_node *p);
        int maxLenOfBranchRoot();
        int maxLenOfBranch(tree_node *p);
        int maxNumOfElementsOnLevelRoot(tree_node *p, int *num_on_levels, int depth);
        void maxNumOfElementsOnLevel(tree_node *p, int level, int *num_on_levels, int *max);

        int numOfSubtreesWithNotMoreThanKNodesRoot(int k);
        int numOfSubtreesWithNotMoreThanKNodes(tree_node *p, int *num, int k); // 1
        int numOfElementsInSubtreesWithNotMoreThanKNodesRoot(int k);
        int numOfElementsInSubtreesWithNotMoreThanKNodes(tree_node *p, int *num, int k); // 2
        int numOfSubtreesWithNotMoreThanKLevelsRoot(int k);
        int numOfSubtreesWithNotMoreThanKLevels(tree_node *p, int *num, int k); // 3
        int numOfSubtreesWithNotMoreThanKElementsOnAnyLevelRoot(int depth, int k);
        int numOfSubtreesWithNotMoreThanKElementsOnAnyLevel(tree_node *p, int *num_on_levels, int depth, int max_num, int k); // 4
        int numOfNodesOnKLevelRoot(int k);
        int numOfNodesOnKLevel(tree_node *p, int level, int i_level); // 5


};
