#include "tree_node.h"
#include <time.h>
#include <math.h>


/*
    del // 44
    addNode // 70
    read // 98
    printNode // 144
    print // 176


    numOfLeavesRoot // 182
    maxLenOfBranchRoot // 216
    maxNumOfElementsOnLevelRoot // 251
    maxDifferenceBetweenNumOfElementsRoot // 347
    numOfElementsWithOnlyChildRoot // 416
*/


template <class T>
class tree
{
    private:
        tree_node<T> *root = nullptr;

    public:
        tree() = default;

        ~tree()
        {
            del(root);
        }


        void del(tree_node<T> *p)
        {
            tree_node<T> *left;
            tree_node<T> *right;

            if (!p)
            {
                return;
            }

            left = p->getLeft();
            right = p->getRight();

            if (left)
            {
                del(left);
            }

            if (right)
            {
                del(right);
            }

            delete p;
        }


        void addNode(tree_node<T> *x, tree_node<T> *p)
        {
            if ((*x < *p) == 1)
            {
                if (p->left == nullptr)
                {
                    p->left = x;
                }
                else
                {
                    addNode(x, p->left);
                }
            }
            else
            {
                if (p->right == nullptr)
                {
                    p->right = x;
                }
                else
                {
                    addNode(x, p->right);
                }
            }
        }


        int read(const char *fname)
        {
            FILE *f;
            int res;
            tree_node<T> tmp;

            root = new tree_node<T>();

            if (!(f = fopen(fname, "r")))
            {
                return student::OPEN_ERROR;
            }

            if (root->read(f) != student::SUCCESS)
            {
                fclose(f);
                return student::READ_ERROR;
            }

            while ((res = tmp.read(f)) == student::SUCCESS)
            {
                tree_node<T> *curr = new tree_node<T>((tree_node<T> &&) tmp);

                if (!curr)
                {
                    fclose(f);
                    return student::MEMORY_ERROR;
                }
                else
                    addNode(curr, root);
            }

            if (!feof(f))
            {
                fclose(f);
                return student::READ_ERROR;
            }

            fclose(f);
            return student::SUCCESS;
        }


        void printNode(int r, int level, tree_node<T> *p)
        {
            int spaces;

            spaces = level * 2;

            if (r < level)
            {
                return;
            }

            p->print(spaces);

            if (p->left)
            {
                printNode(r, level + 1, p->left);
            }

            if (p->right)
            {
                printNode(r, level + 1, p->right);
            }

            return;
        }


        void print(int r)
        {
            if (r == 0)
                return;
            printNode(r, 0, root);
        }


        int numOfLeavesRoot()
        {
            return numOfLeaves(root);
        }


        int numOfLeaves(tree_node<T> *p) // 1
        {
            int left_leaves;
            int right_leaves;
            tree_node<T> *left;
            tree_node<T> *right;

            if (!p)
            {
                return 0;
            }

            left = p->getLeft();
            right = p->getRight();

            if (left == nullptr && right == nullptr)
            {
                return p->getLength();
            }

            left_leaves = numOfLeaves(left);

            right_leaves = numOfLeaves(right);

            return left_leaves + right_leaves;
        }


        int maxLenOfBranchRoot()
        {
            return maxLenOfBranch(root);
        }


        int maxLenOfBranch(tree_node<T> *p) // 2
        {
            int left_tree;
            int right_tree;
            tree_node<T> *left;
            tree_node<T> *right;

            if (!p)
            {
                return 0;
            }

            left = p->getLeft();
            right = p->getRight();

            left_tree = maxLenOfBranch(left);
            right_tree = maxLenOfBranch(right);

            if (left_tree > right_tree)
            {
                return left_tree + p->getLength();
            }
            else
            {
                return right_tree + p->getLength();
            }
        }


        int maxNumOfElementsOnLevelRoot(int depth)
        {
            int *num_on_levels;
            int max_num;
            int num;

            max_num = 0;
            num_on_levels = new int[depth];

            if (!num_on_levels)
            {
                for (int i = 0; i < depth; i++)
                {
                    num = numOfNodesOnLevel(root, i, 0);

                    if (num > max_num)
                    {
                        max_num = num;
                    }
                }

                return max_num;
            }

            for (int i = 0; i < depth; i++)
            {
                num_on_levels[i] = 0;
            }

            maxNumOfElementsOnLevel(root, 0, num_on_levels, &max_num);

            delete [] num_on_levels;

            return max_num;
        }


        void maxNumOfElementsOnLevel(tree_node<T> *p, int level, int *num_on_levels, int *max) // 3
        {
            tree_node<T> *left;
            tree_node<T> *right;

            left = p->getLeft();
            right = p->getRight();

            if (left)
            {
                num_on_levels[level] += p->getLength();

                if (num_on_levels[level] > *max)
                {
                    *max = num_on_levels[level];
                }
                maxNumOfElementsOnLevel(left, level + 1, num_on_levels, max);
            }

            if (right)
            {
                num_on_levels[level] += p->getLength();

                if (num_on_levels[level] > *max)
                {
                    *max = num_on_levels[level];
                }
                maxNumOfElementsOnLevel(right, level + 1, num_on_levels, max);
            }
        }


        int numOfNodesOnLevel(tree_node<T> *p, int level, int i_level) // 3
        {
            tree_node<T> *left;
            tree_node<T> *right;

            int count = 0;

            if (!p)
            {
               return 0;
            }

            left = p->getLeft();
            right = p->getRight();

            if (i_level == level)
            {
               return p->getLength();
            }

            count += numOfNodesOnLevel(left, level, i_level + 1);
            count += numOfNodesOnLevel(right, level, i_level + 1);

            return count;
        }


        int maxDifferenceBetweenNumOfElementsRoot()
        {
            int x;
            x = 0;

            maxDifferenceBetweenNumOfElements(root, &x);

            return x;
        }


        int maxDifferenceBetweenNumOfElements(tree_node<T> *p, int *max) // 4
        {
            int left_tree;
            int right_tree;
            int diff_tree;
            tree_node<T> *left;
            tree_node<T> *right;

            if (!p)
            {
                return 0;
            }

            left = p->getLeft();
            right = p->getRight();

            left_tree = maxDifferenceBetweenNumOfElements(left, max);
            right_tree = maxDifferenceBetweenNumOfElements(right, max);

            diff_tree = abs(left_tree - right_tree);

            if (diff_tree > *max)
            {
                *max = diff_tree;
            }

            return left_tree + right_tree + p->getLength();
        }


        int numOfElementsWithOnlyChildRoot()
        {
            return numOfElementsWithOnlyChild(root);
        }


        int numOfElementsWithOnlyChild(tree_node<T> *p) // 5
        {
            int if_left_child;
            int if_right_child;
            int left_only_child;
            int right_only_child;
            tree_node<T> *left;
            tree_node<T> *right;

            if (!p)
            {
                return 0;
            }

            left = p->getLeft();
            right = p->getRight();

            if_left_child = 0;
            if_right_child = 0;

            if (left && right == nullptr)
            {
                if_left_child += p->getLength();
            }

            if (right && left == nullptr)
            {
                if_right_child += p->getLength();
            }

            left_only_child = numOfElementsWithOnlyChild(left) + if_left_child;
            right_only_child = numOfElementsWithOnlyChild(right) + if_right_child;

            return left_only_child + right_only_child;
        }
};
