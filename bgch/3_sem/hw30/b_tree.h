#include "b_tree_node.h"
#include <time.h>


/*
    del // 44
    addNode // 70
    read // 98
    printNode // 144
    print // 176

*/


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


        int addNode(const T &x, b_tree_node<T> *&first, b_tree_node<T> *&second, T &y)
        {
            int index;
            b_tree_node<T> *p;

            index = first->search(x);

            //printf("x = %s  index = %d\n", x.getName(), index);

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
                y = x;
            }

            if (first->size < 2 * m)
            {
                insertNode(y, index, first->size - 1, first, second);

                return 1;
            }
            else
            {
                p = new b_tree_node<T>();
                p->init(m);
                //TODO


                if (index > m)
                {
                    index -= (m + 1);

                    for (int i = 0; i < m - 1; i++) // m -- middle
                    {
                        if (first != root)
                            first->size -= 1;

                        p->size += 1;
                        p->values[i] = first->values[i + m + 1];
                        p->children[i] = first->children[i + m + 1];
                    }

                    if (first != root)
                        first->size -= 1;

                    p->children[m - 1] = first->children[2 * m];

                    insertNode(y, index, p->size - 1, p, second);

                    y = first->values[m];
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
                        p->values[i] = first->values[i + m];
                        p->children[i] = first->children[i + m];
                    }

                    if (first != root)
                        first->size -= 1;


                    p->children[m] = first->children[2 * m];

                    T rem = first->values[m - 1];
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

                    y = rem;
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
                        p->values[i] = first->values[i + m];
                        p->children[i] = first->children[i + m];
                    }

                    p->children[m] = first->children[2 * m];
                    p->children[0] = second;

                    second = p;

                    return -1;
                }
            }
        }


        void insertNode(const T &x, int index, int size, b_tree_node<T> *&first, b_tree_node<T> *&second)
        {
            //printf("x = %s  index = %d  size = %d\n", x.getName(), index, size);
            for (int i = size; i >= index; i--)
            {
                first->values[i + 1] = first->values[i];
                first->children[i + 2] = first->children[i + 1];
            }

            //first->children[index + 1] = first->children[index];

            first->values[index] = x;
            first->children[index + 1] = second;
            first->size += 1;
        }


        b_tree_node<T> *add(const T &x)
        {
            int res;

            if (!root)
            {
                root = new b_tree_node<T>();
                root->init(m);
                //TODO
                root->values[0] = x;
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
                root->values[0] = y;
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
                //printf("x = %s\n", x.getName());
                root = add(x);
                //print(6);
                //printf("\n");
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
                printf("%d) ", p->size);
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

            //return child_tree + 1;
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
            int num;
            int max_nodes_on_level;

            num = 0;
            max_nodes_on_level = 0;

            numOfSubtreesWithNotMoreThanKNodesOnAnyLevel(root, &num, &max_nodes_on_level, k);
            return num;
        }


        int numOfSubtreesWithNotMoreThanKNodesOnAnyLevel(b_tree_node<T> *p, int *num, int *max_nodes_on_level, int k) // task4
        {
            int child_tree = 0;
            int child_max_nodes_on_level;

            if (!p)
            {
                return 0;
            }

            for (int i = 0; i <= p->size; i++)
            {
                child_max_nodes_on_level = 0;

                child_tree += numOfSubtreesWithNotMoreThanKNodesOnAnyLevel(p->children[i], num, &child_max_nodes_on_level, k);
                if (child_max_nodes_on_level > *max_nodes_on_level)
                    *max_nodes_on_level = child_max_nodes_on_level;
            }

            if (*max_nodes_on_level + 1 <= k)
            {
                (*num) += child_tree + p->size;
            }

            *max_nodes_on_level = 1;

            if ((*max_nodes_on_level) != 0)
            {
                if (p->size + 1 > *max_nodes_on_level)
                    *max_nodes_on_level = p->size;
            }

            return child_tree + p->size;
        }



        int numOfElementsOnKLevelRoot(int k)
        {
            int num;

            num = 0;

            numOfElementsOnKLevel(root, &num, 0, k);

            return num;
        }


        void numOfElementsOnKLevel(b_tree_node<T> *p, int *num, int i_level, int k) // task5
        {
            if (!p)
            {
                return;
            }

            if (i_level == k)
            {
                (*num) += p->size;
                return;
            }

            for (int i = 0; i <= p->size; i++)
            {
                numOfElementsOnKLevel(p->children[i], num, i_level + 1, k);
            }
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
                //printf("num = %d  p = %s\n", *num, p->values[0].getName());
                return;
            }
        }

};
