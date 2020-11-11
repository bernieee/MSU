#include "tree.h"

tree::~tree()
{
    del(root);
}

void tree::del(tree_node *p)
{
    tree_node *left;
    tree_node *right;

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



void tree::addNode(tree_node *x, tree_node *p)
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


int tree::read(const char *fname)
{
   FILE *f;
    int res;
    tree_node tmp;

    root = new tree_node();

    if (!(f = fopen(fname, "r")))
    {
        return student::OPEN_ERROR;
    }

    if (root->readFileStudent(f) != student::SUCCESS)
    {
        fclose(f);
        return student::READ_ERROR;
    }

    while ((res = tmp.readFileStudent(f)) == student::SUCCESS)
    {
        //tree_node *curr = new tree_node((tree_node &&) tmp);
        tree_node *curr = new tree_node();

        curr->swap(tmp);

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


void tree::printNode(int max_print, int level, tree_node *p)
{
    int spaces;

    spaces = level * 2;

    if (max_print < level)
    {
        return;
    }

    for (int i = 0; i < spaces; i++)
    {
        printf(" ");
    }

    p->print();

    if (p->left)
    {
        printNode(max_print, level + 1, p->left);
    }

    if (p->right)
    {
        printNode(max_print, level + 1, p->right);
    }

    return;
}

void tree::print(int max_print)
{
    printNode(max_print, 0, root);
}


int tree::numOfNodes(tree_node *p)
{
    int left_tree;
    int right_tree;
    tree_node *left;
    tree_node *right;

    if (!p)
    {
        return 0;
    }

    left = p->getLeft();
    right = p->getRight();

    left_tree = numOfNodes(left);
    right_tree = numOfNodes(right);

    return left_tree + right_tree + 1;
}


int tree::maxLenOfBranchRoot()
{
    return maxLenOfBranch(root);
}


int tree::maxLenOfBranch(tree_node *p)
{
    int left_tree;
    int right_tree;
    tree_node *left;
    tree_node *right;

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
        return left_tree + 1;
    }
    else
    {
        return right_tree + 1;
    }
}


int tree::maxNumOfElementsOnLevelRoot(tree_node *p, int *num_on_levels, int depth)
{
    //int *num_on_levels;
    int max_num;
    int num;

    max_num = 0;
    //num_on_levels = new int[depth];

    if (!num_on_levels)
    {
        for (int i = 0; i < depth; i++)
        {
            num = numOfNodesOnKLevel(p, i, 0);

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

    maxNumOfElementsOnLevel(p, 0, num_on_levels, &max_num);

    //delete [] num_on_levels;

    return max_num;
}


void tree::maxNumOfElementsOnLevel(tree_node *p, int level, int *num_on_levels, int *max)
{
    tree_node *left;
    tree_node *right;

    if (!p)
    {
        return;
    }

    left = p->getLeft();
    right = p->getRight();

    if (left)
    {
        num_on_levels[level]++;

        if (num_on_levels[level] > *max)
        {
            *max = num_on_levels[level];
        }
        maxNumOfElementsOnLevel(left, level + 1, num_on_levels, max);
    }

    if (right)
    {
        num_on_levels[level]++;

        if (num_on_levels[level] > *max)
        {
            *max = num_on_levels[level];
        }
        maxNumOfElementsOnLevel(right, level + 1, num_on_levels, max);
    }
}


int tree::numOfSubtreesWithNotMoreThanKNodesRoot(int k)
{
    int num;

    num= 0;

    numOfSubtreesWithNotMoreThanKNodes(root, &num, k);
    return num;
}


int tree::numOfSubtreesWithNotMoreThanKNodes(tree_node *p, int *num, int k) // 1
{
    int left_tree;
    int right_tree;
    int sum_tree;
    tree_node *left;
    tree_node *right;

    if (!p)
    {
        return 0;
    }

    left = p->getLeft();
    right = p->getRight();

    left_tree = numOfSubtreesWithNotMoreThanKNodes(left, num, k);
    right_tree = numOfSubtreesWithNotMoreThanKNodes(right, num, k);

    sum_tree = left_tree + right_tree + 1;

    if (sum_tree <= k)
    {
        (*num) += 1;
    }

    return sum_tree;
}


int tree::numOfElementsInSubtreesWithNotMoreThanKNodesRoot(int k)
{
    int num;

    num = 0;

    numOfElementsInSubtreesWithNotMoreThanKNodes(root, &num, k);
    return num;
}


int tree::numOfElementsInSubtreesWithNotMoreThanKNodes(tree_node *p, int *num, int k) // 2
{
    int left_tree;
    int right_tree;
    int sum_tree;
    tree_node *left;
    tree_node *right;

    if (!p)
    {
        return 0;
    }

    left = p->getLeft();
    right = p->getRight();

    left_tree = numOfElementsInSubtreesWithNotMoreThanKNodes(left, num, k);
    right_tree = numOfElementsInSubtreesWithNotMoreThanKNodes(right, num, k);

    sum_tree = left_tree + right_tree + 1;
    //printf("p = %d  sum = %d\n", p->getVal(), sum_tree);

    if (sum_tree <= k)
    {
        (*num) += sum_tree;
    }

    return sum_tree;
}


int tree::numOfSubtreesWithNotMoreThanKLevelsRoot(int k)
{
    int num;

    num = 0;

    numOfSubtreesWithNotMoreThanKLevels(root, &num, k);
    return num;
}


int tree::numOfSubtreesWithNotMoreThanKLevels(tree_node *p, int *num, int k) // 3
{
    tree_node *left;
    tree_node *right;
    int left_tree;
    int right_tree;
    int depth_tree;

    if (!p)
    {
        return 0;
    }

    left = p->getLeft();
    right = p->getRight();

    left_tree = numOfSubtreesWithNotMoreThanKLevels(left, num, k);
    right_tree = numOfSubtreesWithNotMoreThanKLevels(right, num, k);

    if (left_tree > right_tree)
    {
        depth_tree = left_tree + 1;
    }
    else
    {
        depth_tree = right_tree + 1;
    }

    if (depth_tree <= k)
    {
        (*num) += 1;
    }

    return depth_tree;
}


int tree::numOfSubtreesWithNotMoreThanKElementsOnAnyLevelRoot(int depth, int k)
{
    int max_num;
    int ans;
    int *num_on_levels;

    num_on_levels = new int[depth];
    //num_on_levels = nullptr;

    max_num = maxNumOfElementsOnLevelRoot(root, num_on_levels, depth);

    ans = numOfSubtreesWithNotMoreThanKElementsOnAnyLevel(root, num_on_levels, depth, max_num, k);
    delete [] num_on_levels;

    return ans;
}


int tree::numOfSubtreesWithNotMoreThanKElementsOnAnyLevel(tree_node *p, int *num_on_levels, int depth, int max_num, int k) // 4
{
    tree_node *left;
    tree_node *right;
    int left_tree;
    int left_max_num;
    int right_tree;
    int right_max_num;

    if (!p)
    {
        return 0;
    }

    left = p->getLeft();
    right = p->getRight();

    if (max_num <= k)
    {
        int res = numOfNodes(p);
        return res;
    }

    left_max_num = maxNumOfElementsOnLevelRoot(left, num_on_levels, depth);
    right_max_num = maxNumOfElementsOnLevelRoot(right, num_on_levels, depth);

    left_tree = numOfSubtreesWithNotMoreThanKElementsOnAnyLevel(left, num_on_levels, depth, left_max_num, k);
    right_tree = numOfSubtreesWithNotMoreThanKElementsOnAnyLevel(right, num_on_levels, depth, right_max_num, k);

    return left_tree + right_tree;
}


int tree::numOfNodesOnKLevelRoot(int k)
{
    return numOfNodesOnKLevel(root, k, 0);
}


int tree::numOfNodesOnKLevel(tree_node *p, int level, int i_level) // 5
{
    tree_node *left;
    tree_node *right;

    int count = 0;

    if (p == nullptr)
    {
       return 0;
    }

    left = p->getLeft();
    right = p->getRight();

    if (i_level == level)
    {
       return 1;
    }

    count += numOfNodesOnKLevel(left, level, i_level + 1);
    count += numOfNodesOnKLevel(right, level, i_level + 1);

    return count;
}

