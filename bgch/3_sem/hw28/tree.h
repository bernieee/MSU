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

        int numOfElementsInNodesWithKChildsRoot(int k);
        void numOfElementsInNodesWithKChilds(tree_node *p, int num_on_level, int *num, int k); // 1
        int numOfElementsInSubtreesWithNotMoreThanKNodesRoot(int k);
        int numOfElementsInSubtreesWithNotMoreThanKNodes(tree_node *p, int *num, int k); // 2
        int numOfElementsInSubtreesWithNotMoreThanKLevelsRoot(int k);
        int numOfElementsInSubtreesWithNotMoreThanKLevels(tree_node *p, int *num, int *levels, int k); // 3
        int numOfElementsInSubtreesWithNotMoreThanKElementsOnAnyLevelRoot(int k);
        int maxNumOfElementsOnAnyLevel(tree_node *p);
        int numOfElementsInSubtreesWithNotMoreThanKElementsOnAnyLevel(tree_node *p, int *num, int k); // 4
        int numOfElementsOnKLevelRoot(int k);
        void numOfElementsOnKLevel(tree_node *p, int *num, int i_level, int k); // 5
        int numOfElementsOnKLevelInt(tree_node *p, int i_level, int k);


};
