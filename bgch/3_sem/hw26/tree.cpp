#include "tree.h"

tree::~tree()
{
    del(root);
}


void tree::del(tree_node *p)
{
    tree_node *left;
    tree_node *right;

    left = p->getLeft();
    right = p->getRight();

    if (left == nullptr && right == nullptr)
    {
        p->remove();
        delete p;
        return;
    }

    if (left)
    {
        return del(left);
    }

    if (right)
    {
        return del(right);
    }
}



void tree::addNode(tree_node *x, tree_node *p)
{
    if (p == nullptr)
    {
        p = root;
    }

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
        tree_node *curr = new tree_node((tree_node &&) tmp);

        if (!curr)
        {
            fclose(f);
            return student::MEMORY_ERROR;
        }

        /*if (root == nullptr)
        {
            printf("root = %d\n", root->getVal());
            root = curr;
        }*/
        addNode(curr, root);
    }

    if (feof(f))
    {
        fclose(f);
        return student::SUCCESS;
    }

    if (res != student::SUCCESS)
    {
        fclose(f);
        return student::READ_ERROR;
    }

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
}

void tree::print(int max_print)
{
    printNode(max_print, 0, root);
}


int tree::numOfLeafsRoot()
{
    return numOfLeafs(root);
}

int tree::numOfLeafs(tree_node *p) // 1
{
    tree_node *left;
    tree_node *right;

    left = p->getLeft();
    right = p->getRight();

    if (left == nullptr && right == nullptr)
    {
        return 0;
    }

    if (left)
    {
        return numOfLeafs(left) + 1;
    }

    if (right)
    {
        return numOfLeafs(right) + 1;
    }

    return 0;
}
