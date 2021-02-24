#include "b_tree_node.h"
#include <time.h>


template <class T>
class b_tree
{
    private:
        int m;
        b_tree_node<T> *root = nullptr;

    public:
        b_tree() = default;


        ~b_tree()
        {
            del(root);
        }


        void init(int new_m)
        {
            m = new_m;
        }


        void del(b_tree_node<T> *p)
        {
            if (!p)
            {
                return;
            }


            for (int i = 0; i <= p->size; i++)
            {
                del(p->children[i]);
            }

            delete [] p->values;
            delete [] p->children;
            delete p;
            p = nullptr;
        }


        int addNode(T &x, b_tree_node<T> *&first, b_tree_node<T> *&second, T &y)
        {
            int index;
            b_tree_node<T> *p;

            index = first->search(x);

            p = first->children[index];

            if (p)
            {
                if (addNode(x, p, second, y) == 1)
                {
                    return 1;
                }
            }
            else
            {
                second = nullptr;
                y = (T &&) x;
            }

            if (first->size < 2 * m)
            {
                insertNode(y, index, first->size - 1, first, second);

                return 1;
            }
            else
            {
                p = new b_tree_node<T>();

                if (p->init(m) != student::SUCCESS)
                {
                    delete p;
                    return -3;
                }


                if (index > m)
                {
                    index -= (m + 1);

                    for (int i = 0; i < m - 1; i++) // m -- middle
                    {
                        if (first != root)
                            first->size -= 1;

                        p->size += 1;
                        p->values[i] = (T &&) first->values[i + m + 1];
                        p->children[i] = first->children[i + m + 1];
                    }

                    if (first != root)
                        first->size -= 1;

                    p->children[m - 1] = first->children[2 * m];

                    insertNode(y, index, p->size - 1, p, second);

                    y = (T &&) first->values[m];
                    second = p;

                    return -1;
                }
                else if (index < m)
                {
                    for (int i = 0; i < m; i++) // m -- middle
                    {
                        if (first != root)
                            first->size -= 1;

                        p->size += 1;
                        p->values[i] = (T &&) first->values[i + m];
                        p->children[i] = first->children[i + m];
                    }

                    if (first != root)
                        first->size -= 1;


                    p->children[m] = first->children[2 * m];

                    T rem = (T &&) first->values[m - 1];
                    int size;

                    if (first == root)
                    {
                        size = first->size - m - 2;
                    }
                    else
                    {
                        size = first->size - 1;
                    }

                    insertNode(y, index, size, first, second);

                    y = (T &&) rem;
                    second = p;

                    return -2;
                }
                else
                {
                    for (int i = 0; i < m; i++) // m -- middle
                    {
                        if (first != root)
                            first->size -= 1;

                        p->size += 1;
                        p->values[i] = (T &&) first->values[i + m];
                        p->children[i] = first->children[i + m];
                    }

                    p->children[m] = first->children[2 * m];
                    p->children[0] = second;

                    second = p;

                    return -1;
                }
            }
        }


        void insertNode(T &x, int index, int size, b_tree_node<T> *&first, b_tree_node<T> *&second)
        {
            for (int i = size; i >= index; i--)
            {
                first->values[i + 1] = (T &&) first->values[i];
                first->children[i + 2] = first->children[i + 1];
            }

            first->values[index] = (T &&) x;
            first->children[index + 1] = second;
            first->size += 1;
        }


        b_tree_node<T> *add(T &x)
        {
            int res;

            if (!root)
            {
                root = new b_tree_node<T>();
                root->init(m);
                //TODO
                root->values[0] = (T &&) x;
                root->size = 1;

                return root;
            }

            T y;
            b_tree_node<T> *first = root;
            b_tree_node<T> *second;

            if ((res = addNode(x, first, second, y)) == 1)
            {
                return first;
            }


            if (root->size < 2 * m)
            {
                int index = root->search(y);
                insertNode(y, index, first->size - 1, first, second);

                return first;
            }
            else
            {
                root = new b_tree_node<T>();
                root->init(m);
                //TODO
                if (res == -1)
                    first->size -= m;
                else
                    first->size -= (m + 1);
                root->values[0] = (T &&) y;
                root->children[0] = first;
                root->children[1] = second;
                root->size = 1;

                return root;
            }
        }


        int read(const char *fname)
        {
            FILE *f;
            int res;
            T x;

            if (!(f = fopen(fname, "r")))
            {
                return student::OPEN_ERROR;
            }

            while ((res = x.read(f)) == student::SUCCESS)
            {
                root = add(x);
            }

            if (!feof(f))
            {
                fclose(f);
                return student::READ_ERROR;
            }

            fclose(f);
            return student::SUCCESS;
        }


        void printNode(int r, int level, b_tree_node<T> *p)
        {
            int spaces;

            spaces = level * 2;

            if (r < level)
            {
                return;
            }

            for (int i = 0; i < p->size; i++)
            {
                (p->values[i]).print(spaces);

                if (p->children[i])
                {
                    printNode(r, level + 1, p->children[i]);
                }
            }

            if (p->children[p->size])
            {
                printNode(r, level + 1, p->children[p->size]);
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


        int numOfElementsWithKChildsRoot(int k)
        {
            int num;

            num = 0;

            numOfElementsWithKChilds(root, &num, k);
            return num;
        }


        void numOfElementsWithKChilds(b_tree_node<T> *p, int *num, int k) // task1
        {
            int child_tree = 0;

            if (!p)
            {
                return;
            }

            for (int i = 0; i <= p->size; i++)
            {
                numOfElementsWithKChilds(p->children[i], num, k);
                if (p->children[i])
                    child_tree += 1;
            }

            if (child_tree == k)
            {
                (*num) += p->size;
            }
        }


        int numOfSubtreesWithNotMoreThanKNodesRoot(int k)
        {
            int num;
            int nodes;

            num = 0;
            nodes = 0;

            numOfSubtreesWithNotMoreThanKNodes(root, &num, &nodes, k);
            return num;
        }


        int numOfSubtreesWithNotMoreThanKNodes(b_tree_node<T> *p, int *num, int *nodes, int k) // task2
        {
            int child_tree = 0;
            int child_nodes;

            if (!p)
            {
                return 0;
            }

            for (int i = 0; i <= p->size; i++)
            {
                child_nodes = 0;

                child_tree += numOfSubtreesWithNotMoreThanKNodes(p->children[i], num, &child_nodes, k);
                *nodes += child_nodes;
            }

            if (*nodes + 1 <= k)
            {
                (*num) += child_tree + p->size;
            }

            (*nodes) += 1;

            return child_tree + p->size;
        }


        int numOfSubtreesWithNotMoreThanKLevelsRoot(int k)
        {
            int num;
            int levels;

            num = 0;
            levels = 0;

            numOfSubtreesWithNotMoreThanKLevels(root, &num, &levels, k);
            return num;
        }


        int numOfSubtreesWithNotMoreThanKLevels(b_tree_node<T> *p, int *num, int *levels, int k) // task3
        {
            int child_tree = 0;
            int child_levels;

            if (!p)
            {
                return 0;
            }

            for (int i = 0; i <= p->size; i++)
            {
                child_levels = 0;

                child_tree += numOfSubtreesWithNotMoreThanKLevels(p->children[i], num, &child_levels, k);
                if (child_levels > *levels)
                    *levels = child_levels;
            }

            if (*levels + 1 <= k)
            {
                (*num) += child_tree + p->size;
            }

            (*levels) += 1;

            return child_tree + p->size;
        }


        int numOfSubtreesWithNotMoreThanKNodesOnAnyLevelRoot(int k)
        {
            return numOfSubtreesWithNotMoreThanKNodesOnAnyLevel(root, k);
        }


        int maxNumOfNodesOnLevel(b_tree_node<T> *p, int k)
        {
            int max;
            int num;
            int res;
            int i;

            max = 0;
            i = 0;
            res = -1;

            while (res != 0)
            {
                num = 0;
                res = numOfElementsOnKLevel(p, &num, 0, i);

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


        int numOfElementsInSubtrees(b_tree_node<T> *p, int *num)
        {
            int child_tree = 0;

            if (!p)
            {
                return 0;
            }

            for (int i = 0; i <= p->size; i++)
            {
                child_tree += numOfElementsInSubtrees(p->children[i], num);
            }

            (*num) += child_tree + p->size;

            return child_tree + p->size;
        }


        int numOfSubtreesWithNotMoreThanKNodesOnAnyLevel(b_tree_node<T> *p, int k) // task4
        {
            int max;
            int child_tree = 0;

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

            for (int i = 0; i <= p->size; i++)
            {
                child_tree += numOfSubtreesWithNotMoreThanKNodesOnAnyLevel(p->children[i], k);
            }

            return child_tree;
        }


        int numOfElementsOnKLevelRoot(int k)
        {
            int num;

            num = 0;

            numOfElementsOnKLevel(root, &num, 0, k);

            return num;
        }


        int numOfElementsOnKLevel(b_tree_node<T> *p, int *num, int i_level, int k) // task5
        {
            int child_tree = 0;

            if (!p)
            {
                return 0;
            }

            if (i_level == k)
            {
                (*num) += p->size;
                return 1;
            }

            for (int i = 0; i <= p->size; i++)
            {
                child_tree += numOfElementsOnKLevel(p->children[i], num, i_level + 1, k);
            }

            return child_tree;
        }


        int numOfElementsInKBranchesRoot(int k)
        {
            int num;

            num = 0;

            numOfElementsInKBranches(root, &num, 0, 0, k);

            return num;
        }


        void numOfElementsInKBranches(b_tree_node<T> *p, int *num, int len, int sum, int k) // task6
        {
            int flag = 0;

            if (!p)
            {
                return;
            }

            for (int i = 0; i <= p->size; i++)
            {
                if (!p->children[i])
                {
                    flag = 1;
                    break;
                }

                numOfElementsInKBranches(p->children[i], num, len + 1, sum + p->size, k);
            }

            if (flag == 1 && (len + 1) == k)
            {
                (*num) += sum + p->size;
                return;
            }
        }

};
