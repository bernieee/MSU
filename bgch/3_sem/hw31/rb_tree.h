#include "rb_tree_node.h"
#include <time.h>


template <class T>
class rb_tree
{
    private:
        rb_tree_node<T> *root = nullptr;

    public:
        rb_tree() = default;


        ~rb_tree()
        {
            del(root);
        }


        void del(rb_tree_node<T> *p)
        {
            if (!p)
            {
                return;
            }

            if (p->left)
            {
                del(p->left);
            }

            if (p->right)
            {
                del(p->right);
            }

            delete p;
        }


        void addNode(rb_tree_node<T> *x, rb_tree_node<T> *&p)
        {
            if (!p)
            {
                x->color = rb_tree_node<T>::black;
                p = x;

                balance(p);
                return;
            }

            if ((*x < *p) == 1)
            {
                if (p->left)
                {
                    addNode(x, p->left);
                    balance(p);
                }
                else
                {
                    x->color = rb_tree_node<T>::red;
                    p->left = x;
                }
            }
            else
            {
                if (p->right)
                {
                    addNode(x, p->right);
                    balance(p);
                }
                else
                {
                    x->color = rb_tree_node<T>::red;
                    p->right = x;
                }
            }
        }


        void rotateRight(rb_tree_node<T> *&p)
        {
            rb_tree_node<T> *child = p->right;
            rb_tree_node<T> *grandchild = child->left;

            child->left = p;
            p->right = grandchild;

            p = child;
        }


        void rotateLeft(rb_tree_node<T> *&p)
        {
            rb_tree_node<T> *child = p->left;
            rb_tree_node<T> *grandchild = child->right;

            child->right = p;
            p->left = grandchild;

            p = child;
        }


        void balance(rb_tree_node<T> *&p)
        {
            if (p->color == rb_tree_node<T>::red)
            {
                return;
            }

            rb_tree_node<T> *left;
            rb_tree_node<T> *right;

            if (p->left && p->left->color == rb_tree_node<T>::red)
            {
                if (p->right && p->right->color == rb_tree_node<T>::red) // red uncle
                {
                    left = p->left->left;
                    right = p->left->right;

                    // pull down rb_tree_node<T>::black
                    if ((right && right->color == rb_tree_node<T>::red) || (left && left->color == rb_tree_node<T>::red))
                    {
                        p->color = rb_tree_node<T>::red;
                        p->left->color = rb_tree_node<T>::black;

                        if (p->right && p->right->color == rb_tree_node<T>::red)
                        {
                            p->right->color = rb_tree_node<T>::black;
                        }

                        return;
                    }
                }
                else
                {
                    right = p->left->right;

                    if (right && right->color == rb_tree_node<T>::red) // rotate right subtree
                    {
                        rotateRight(p->left);
                    }

                    left = p->left->left;

                    if (left && left->color == rb_tree_node<T>::red) // pull down rb_tree_node<T>::black
                    {
                        p->color = rb_tree_node<T>::red;
                        p->left->color = rb_tree_node<T>::black;

                        if (p->right && p->right->color == rb_tree_node<T>::red)
                        {
                            p->right->color = rb_tree_node<T>::black;
                            return;
                        }

                        rotateLeft(p);
                        return;
                    }
                }
            }


            if (p->right && p->right->color == rb_tree_node<T>::red)
            {
                if (p->left && p->left->color == rb_tree_node<T>::red) // red uncle
                {
                    left = p->right->left;
                    right = p->right->right;

                    // pull down rb_tree_node<T>::black
                    if ((left && left->color == rb_tree_node<T>::red) || (right && right->color == rb_tree_node<T>::red))
                    {
                        p->color = rb_tree_node<T>::red;
                        p->right->color = rb_tree_node<T>::black;

                        if (p->left && p->left->color == rb_tree_node<T>::red)
                        {
                            p->left->color = rb_tree_node<T>::black;
                        }

                        return;
                    }
                }
                else
                {
                    left = p->right->left;

                    if (left && left->color == rb_tree_node<T>::red) // rotate left subtree
                    {
                        rotateLeft(p->right);
                    }

                    right = p->right->right;

                    if (right && right->color == rb_tree_node<T>::red) // pull down rb_tree_node<T>::black
                    {
                        p->color = rb_tree_node<T>::red;
                        p->right->color = rb_tree_node<T>::black;

                        if (p->left && p->left->color == rb_tree_node<T>::red)
                        {
                            p->left->color = rb_tree_node<T>::black;
                            return;
                        }

                        rotateRight(p);
                        return;
                    }
                }
            }
        }


        int read(const char *fname)
        {
            FILE *f;
            int res;
            rb_tree_node<T> x;

            if (!(f = fopen(fname, "r")))
            {
                return student::OPEN_ERROR;
            }

            while ((res = x.read(f)) == student::SUCCESS)
            {
                rb_tree_node<T> *curr = new rb_tree_node<T>((rb_tree_node<T> &&) x);

                if (!curr)
                {
                    fclose(f);
                    return student::MEMORY_ERROR;
                }
                else
                {
                    addNode(curr, root);
                    root->color = rb_tree_node<T>::black;
                }
            }

            if (!feof(f))
            {
                fclose(f);
                return student::READ_ERROR;
            }

            fclose(f);
            return student::SUCCESS;
        }


        void printNode(int r, int level, rb_tree_node<T> *p)
        {
            int spaces;

            spaces = level * 2;

            if (r < level)
            {
                return;
            }

            p->print(spaces);

            for (int i = 0; i < spaces; i++)
            {
                printf(" ");
            }
            printf("(%d)\n", p->color);

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
            {
                return;
            }

            printNode(r, 0, root);
        }


        int numOfElementsInSubtreesWithNotMoreThanKNodesRoot(int k)
        {
            int num;
            num = 0;

            numOfElementsInSubtreesWithNotMoreThanKNodes(root, &num, k);
            return num;
        }


        int numOfElementsInSubtreesWithNotMoreThanKNodes(rb_tree_node<T> *p, int *num, int k) // task1
        {
            int left_tree;
            int right_tree;
            int sum_tree;

            if (!p)
            {
                return 0;
            }

            left_tree = numOfElementsInSubtreesWithNotMoreThanKNodes(p->left, num, k);
            right_tree = numOfElementsInSubtreesWithNotMoreThanKNodes(p->right, num, k);

            sum_tree = left_tree + right_tree + 1;

            if (sum_tree <= k)
            {
                *num += sum_tree;
            }

            return sum_tree;
        }


        int numOfElementsInSubtreesWithNotMoreThanKLevelsRoot(int k)
        {
            int num;
            int levels;
            num = 0;
            levels = 0;

            numOfElementsInSubtreesWithNotMoreThanKLevels(root, &num, &levels, k);
            return num;
        }


        int numOfElementsInSubtreesWithNotMoreThanKLevels(rb_tree_node<T> *p, int *num, int *levels, int k) // task2
        {
            int left_tree;
            int left_levels = 0;
            int right_tree;
            int right_levels = 0;
            int sum_tree;

            if (!p)
            {
                return 0;
            }

            left_tree = numOfElementsInSubtreesWithNotMoreThanKLevels(p->left, num, &left_levels, k);
            right_tree = numOfElementsInSubtreesWithNotMoreThanKLevels(p->right, num, &right_levels, k);

            if (left_levels > *levels)
            {
                *levels = left_levels;
            }

            if (right_levels > *levels)
            {
                *levels = right_levels;
            }

            sum_tree = left_tree + right_tree + 1;

            if (*levels + 1 <= k)
            {
                *num += sum_tree;
            }

            (*levels) += 1;

            return sum_tree;
        }



        int numOfElementsInSubtreesWithNotMoreThanKNodesOnAnyLevelRoot(int k)
        {
            return numOfElementsInSubtreesWithNotMoreThanKNodesOnAnyLevel(root, k);
        }


        int maxNumOfNodesOnLevel(rb_tree_node<T> *p, int k)
        {
            int max;
            int res;
            int i;

            max = 0;
            i = 0;
            res = -1;

            while (res != 0)
            {
                res = numOfElementsOnKLevel(p, 0, i);

                if (res > k)
                {
                    return res;
                }

                if (res > max)
                {
                    max = res;
                }

                i++;
            }

            return max;
        }


        int numOfElementsInSubtrees(rb_tree_node<T> *p, int *num)
        {
            int left_tree;
            int right_tree;
            int sum_tree;

            if (!p)
            {
                return 0;
            }

            left_tree = numOfElementsInSubtrees(p->left, num);
            right_tree = numOfElementsInSubtrees(p->right, num);

            sum_tree = left_tree + right_tree + 1;

            (*num) += sum_tree;

            return sum_tree;
        }


        int numOfElementsInSubtreesWithNotMoreThanKNodesOnAnyLevel(rb_tree_node<T> *p, int k) // task3
        {
            int max;
            int left_tree;
            int right_tree;

            if (!p)
            {
                return 0;
            }

            max = maxNumOfNodesOnLevel(p, k);

            if (max <= k)
            {
                int num = 0;
                numOfElementsInSubtrees(p, &num);

                return num;
            }

            left_tree = numOfElementsInSubtreesWithNotMoreThanKNodesOnAnyLevel(p->left, k);
            right_tree = numOfElementsInSubtreesWithNotMoreThanKNodesOnAnyLevel(p->right, k);

            return left_tree + right_tree;
        }


        int numOfElementsOnKLevelRoot(int k)
        {
            return numOfElementsOnKLevel(root, 0, k);
        }


        int numOfElementsOnKLevel(rb_tree_node<T> *p, int level, int k) // task4
        {
            int left_tree;
            int right_tree;

            if (!p)
            {
                return 0;
            }

            if (level == k)
            {
                return 1;
            }

            left_tree = numOfElementsOnKLevel(p->left, level + 1, k);
            right_tree = numOfElementsOnKLevel(p->right, level + 1, k);

            return left_tree + right_tree;
        }


        int numOfElementsInKBranchesRoot(int k)
        {
            int num;

            num = 0;

            numOfElementsInKBranches(root, &num, 0, k);

            return num;
        }


        void numOfElementsInKBranches(rb_tree_node<T> *p, int *num, int len, int k) // task5
        {
            if (!p)
            {
                return;
            }

            numOfElementsInKBranches(p->left, num, len + 1, k);
            numOfElementsInKBranches(p->right, num, len + 1, k);

            if (!(p->left) && !(p->right) && (len + 1) == k)
            {
                (*num) += len + 1;
                return;
            }
        }
};
