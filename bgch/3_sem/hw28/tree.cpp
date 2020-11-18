#include "tree.h"

tree::~tree()
{
    del(root);
}

void tree::del(tree_node *p)
{
    tree_node *down;
    tree_node *level;

    if (!p)
    {
        return;
    }

    down = p->down;
    level = p->level;

    if (down)
    {
        del(down);
    }

    if (level)
    {
        del(level);
    }

    delete p;
}


void tree::addNode(tree_node *x, tree_node *p)
{
    int res;
    tree_node *next;

    next = p->down;

    res = (*x < *p);

    if (p->down == nullptr)
    {
        p->down = x;
        return;
    }


    if (res == 1)
    {
        int res1;

        res1 = (*next < *p);

        if (res1 == 1)
        {
            addNode(x, next);
        }
        else
        {
            p->down = x;
            x->level = next;
        }
    }
    else if (res == -1)
    {
        int res1;

        res1 = (*next < *p);

        while (next->level && res1 >= 0)
        {
            next = next->level;
            res1 = (*next < *p);
        }

        if (res1 < 0)
        {
            addNode(x, next);
        }
        else
        {
            next->level = x;
        }
    }
    else
    {
        int res1;

        res1 = (*next < *p);

        if (res1 == 1)
        {
            tree_node *tmp;

            tmp = next->level;
            next->level = x;
            x->level = tmp;
        }
        else
        {
            p->down = x;
            x->level = next;
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
        {
            addNode(curr, root);
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


void tree::printNode(int max_print, int level, tree_node *p)
{
    int spaces;

    spaces = 2 * level;

    if (max_print < level)
    {
        return;
    }

    for (int i = 0; i < spaces; i++)
    {
        printf(" ");
    }

    p->print();

    if (p->down)
    {
        printNode(max_print, level + 1, p->down);
    }

    if (p->level)
    {
        printNode(max_print, level, p->level);
    }

    return;
}


void tree::print(int max_print)
{
    printNode(max_print, 0, root);
}


int tree::numOfElementsInNodesWithKChildsRoot(int k)
{
    int num;
    num = 0;

    numOfElementsInNodesWithKChilds(root, 1, &num, k);

    return num;
}


void tree::numOfElementsInNodesWithKChilds(tree_node *p, int num_on_level, int *num, int k) // 1
{
    tree_node *down;
    tree_node *level;

    if (!p)
    {
        return;
    }

    down = p->getDown();
    level = p->getLevel();

    numOfElementsInNodesWithKChilds(down, 1, num, k);
    numOfElementsInNodesWithKChilds(level, num_on_level + 1, num, k);

    if (!level && num_on_level == k)
    {
        (*num) += 1;
    }
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
    tree_node *down;
    tree_node *level;
    int num_down;
    int num_level;
    int num_sum;

    if (!p)
    {
        return 0;
    }

    down = p->getDown();
    level = p->getLevel();

    num_down = numOfElementsInSubtreesWithNotMoreThanKNodes(down, num, k);
    num_level = numOfElementsInSubtreesWithNotMoreThanKNodes(level, num, k);

    num_sum = num_down + num_level;

    if ((num_down + 1) <= k)
    {
        (*num) += num_down + 1;
    }

    //printf("p = %d  num_down = %d  num_level = %d\n", p->getVal(), num_down, num_level);

    return num_sum + 1;
}


int tree::numOfElementsInSubtreesWithNotMoreThanKLevelsRoot(int k)
{
    int num;
    int levels;
    //int num_levels;

    num = 0;
    levels = 1;
    //num_levels = 1;

    //numOfElementsInSubtreesWithNotMoreThanKLevels(root, &num, &max_levels, 1, 1, k);
    numOfElementsInSubtreesWithNotMoreThanKLevels(root, &num, &levels, k);

    return num;
}


/*int tree::numOfElementsInSubtreesWithNotMoreThanKLevels(tree_node *p, int *num, int *max_levels, int num_levels, int levels, int k) // 3
{
    tree_node *down;
    tree_node *level;
    int num_down;
    int num_level;
    int num_sum;

    if (!p)
    {
        return 0;
    }

    down = p->getDown();
    level = p->getLevel();

    num_down = numOfElementsInSubtreesWithNotMoreThanKLevels(down, num, max_levels, num_levels, *max_levels, k);

    if (num_down > 0)
    {
        levels = levels + 1;
        //num_levels = levels;

        if (levels >= *max_levels)
        {
            *max_levels = levels;
        }

        //check = *levels;
    }

    if (num_down == 0)
    {
        (*num) += 1;
    }
    else if (levels <= k)
    {
        (*num) += num_down + 1;
        //printf("2 p = %d  num_down = %d  check = %d  levels = %d\n", p->getVal(), num_down, check, *levels);
    }

    printf("p = %d  num_down = %d  levels = %d  max_levels = %d\n", p->getVal(), num_down + 1, levels, *max_levels);

    num_level = numOfElementsInSubtreesWithNotMoreThanKLevels(level, num, max_levels, num_levels, levels, k);

    num_sum = num_down + num_level;

    if (num_down > 0)
    {
        levels = levels + 1;

        if (levels >= *max_levels)
        {
            *max_levels = levels;
        }

        //check = *levels;
    }

    if (num_down == 0)
    {
        (*num) += 1;
    }
    else if (levels <= k)
    {
        (*num) += num_down + 1;
        //printf("2 p = %d  num_down = %d  check = %d  levels = %d\n", p->getVal(), num_down, check, *levels);
    }

    printf("p = %d  num_down = %d  levels = %d  max_levels = %d\n", p->getVal(), num_down + 1, levels, *max_levels);
    


    return num_sum + 1;
}*/


int tree::numOfElementsInSubtreesWithNotMoreThanKLevels(tree_node *p, int *num, int *levels, int k) // 3
{
    tree_node *down;
    tree_node *level;
    int num_down;
    int max_levels;
    int num_level = 0;
    int num_sum;

    if (!p)
    {
        return 0;
    }

    down = p->getDown();
    level = p->getLevel();

    num_down = numOfElementsInSubtreesWithNotMoreThanKLevels(down, num, levels, k);

    if (*levels <= k)
    {
        (*num) += num_down + 1;
    }

    //printf("p = %d  num_down = %d  levels = %d  num = %d\n", p->getVal(), num_down, *levels, *num);

    max_levels = *levels;

    while (level)
    {
        *levels = 1;
        if (level->getDown())
        {
            num_level += numOfElementsInSubtreesWithNotMoreThanKLevels(level, num, levels, k);

            if (*levels > max_levels)
            {
                max_levels = *levels;
            }
        }
        else
        {
            num_level++;
            (*num) += 1;
        }

        level = level->getLevel();

    }

    *levels = max_levels + 1;

    num_sum = num_down + num_level;

    //printf("p = %d  num_down = %d  num_level = %d  levels = %d  max_levels = %d\n", p->getVal(), num_down, num_level, *levels, max_levels);

    /*if (*levels <= k)
    {
        (*num) += num_down + 1;
    }
    else if (down_levels <= k)
    {
        (*num) += num_down + 1;
    }*/

    return num_sum + 1;
}


int tree::numOfElementsOnKLevelRoot(int k)
{
    int num;

    num = 0;

    numOfElementsOnKLevel(root, &num, 0, k);

    return num;
}


void tree::numOfElementsOnKLevel(tree_node *p, int *num, int i_level, int k) // 5
{
    tree_node *down;
    tree_node *level;

    if (!p)
    {
        return;
    }

    down = p->getDown();
    level = p->getLevel();

    if (i_level == k)
    {
        level = p;
        while (level)
        {
            (*num) += 1;
            level = level->getLevel();
        }

        return;
    }

    numOfElementsOnKLevel(down, num, i_level + 1, k);
    numOfElementsOnKLevel(level, num, i_level, k);
}

