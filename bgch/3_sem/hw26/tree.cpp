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
        delete root;
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


/*int tree::maxNumOfElementsOnLevelRoot()
{
    return maxNumOfElementsOnLevel(root);
}


int tree::maxNumOfElementsOnLevel(tree_node *p) // 3
{

}*/


int tree::maxDifferenceBetwenDepthsRoot()
{
    int x;
    x = 0;

    maxDifferenceBetwenDepths(root, &x);

    return x;
}


void tree::maxDifferenceBetwenDepths(tree_node *p, int *max_depth) // 4
{
    int left_depth;
    int right_depth;
    int diff_depth;
    tree_node *left;
    tree_node *right;

    if (!p)
    {
        return;
    }

    left = p->getLeft();
    right = p->getRight();

    if (left || right)
    {
        left_depth = maxLenOfBranch(left);
        right_depth = maxLenOfBranch(right);

        diff_depth = abs(left_depth - right_depth);

        //printf("p = %d diff = %d\n", p->getVal(), diff_depth);

        if (diff_depth > *max_depth)
        {
            *max_depth = diff_depth;
        }

        maxDifferenceBetwenDepths(left, max_depth);
        maxDifferenceBetwenDepths(right, max_depth);
    }
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

