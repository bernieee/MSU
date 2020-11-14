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
        //delete root;
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


int tree::numOfLeavesRoot()
{
    return numOfLeaves(root);
}

int tree::numOfLeaves(tree_node *p) // 1
{
    int left_leaves;
    int right_leaves;
    tree_node *left;
    tree_node *right;

    if (!p)
    {
        return 0;
    }

    left = p->getLeft();
    right = p->getRight();

    if (left == nullptr && right == nullptr)
    {
        return 1;
    }

    left_leaves = numOfLeaves(left);

    right_leaves = numOfLeaves(right);

    return left_leaves + right_leaves;
}


int tree::maxLenOfBranchRoot()
{
    return maxLenOfBranch(root);
}


int tree::maxLenOfBranch(tree_node *p) // 2
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


int tree::maxNumOfElementsOnLevelRoot(int depth)
{
    int *num_on_levels;
    int max_num;

    num_on_levels = new int[depth];

    for (int i = 0; i < depth; i++)
    {
        num_on_levels[i] = 0;
    }

    max_num = 0;

    maxNumOfElementsOnLevel(root, 0, num_on_levels, &max_num);

    delete [] num_on_levels;

    return max_num;
}


void tree::maxNumOfElementsOnLevel(tree_node *p, int level, int *num_on_levels, int *max) // 3
{
    tree_node *left;
    tree_node *right;

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


int tree::maxDifferenceBetwenDepthsRoot()
{
    int x;
    x = 0;

    return maxDifferenceBetwenDepths(root, &x);
}


int tree::maxDifferenceBetwenDepths(tree_node *p, int *depth) // 4
{
    int left_depth;
    int diff_left_depth;
    int right_depth;
    int diff_right_depth;
    int diff_depth;
    tree_node *left;
    tree_node *right;

    left = p->getLeft();
    right = p->getRight();

    left_depth = 0;
    right_depth = 0;
    diff_depth = 0;
    diff_left_depth = 0;
    diff_right_depth = 0;

    if (!left && !right)
    {
        *depth = 1;
        return 0;
    }

    if (left)
    {
        diff_left_depth = maxDifferenceBetwenDepths(left, &left_depth);
    }

    if (right)
    {
        diff_right_depth = maxDifferenceBetwenDepths(right, &right_depth);
    }

    diff_depth = abs(left_depth - right_depth);

    if (left_depth > right_depth)
    {
        *depth = left_depth + 1;
    }
    else
    {
        *depth = right_depth + 1;
    }

    if (diff_left_depth > diff_depth)
    {
        diff_depth = diff_left_depth;
    }

    if (diff_right_depth > diff_depth)
    {
        diff_depth = diff_right_depth;
    }

    return diff_depth;
}


int tree::numOfElementsWithOnlyChildRoot()
{
    return numOfElementsWithOnlyChild(root);
}


int tree::numOfElementsWithOnlyChild(tree_node *p) // 5
{
    int if_left_child;
    int if_right_child;
    int left_only_child;
    int right_only_child;
    tree_node *left;
    tree_node *right;

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
        if_left_child++;
    }

    if (right && left == nullptr)
    {
        if_right_child++;
    }

    left_only_child = numOfElementsWithOnlyChild(left) + if_left_child;
    right_only_child = numOfElementsWithOnlyChild(right) + if_right_child;

    return left_only_child + right_only_child;
}

