#include "list2.h"

int list2::read(FILE *f)
{
    int res;
    int i;
    list2_node *end;
    list2_node *curr;
    list2_node tmp;

    head = new list2_node();

    if (head->read(f) != student::SUCCESS)
    {
        return student::READ_ERROR;
    }

    head->setNext(nullptr);
    head->setPrev(nullptr);
    end = head;
    i = 1;

    while ((i < m) && ((res = tmp.read(f)) == student::SUCCESS))
    {
        curr = new list2_node();

        curr->swap(tmp);
        curr->setNext(nullptr);
        curr->setPrev(end);
        end->setNext(curr);
        end = curr;
        i++;
    }

    if (feof(f))
    {
        return student::SUCCESS;
    }

    if (res != student::SUCCESS)
    {
        return student::READ_ERROR;
    }

    return student::SUCCESS;
}


void list2::del()
{
    list2_node *curr;
    list2_node *next;

    for(curr = head; curr; curr = next)
    {
        next = curr->getNext();

        curr->remove();
        delete curr;
    }
}


void list2::print()
{
    int i;
    list2_node *curr;

    for (i = 0, curr = head; i < r && curr; i++, curr = curr->getNext())
    {
        curr->print();
    }

    //printf("\n");
}


int list2::getLength() const
{
    list2_node *curr;
    int len;

    len = 0;

    for (curr = head; curr; curr = curr->getNext())
    {
        len++;
    }

    return len;
}

int list2::operator<(const list2 &x)
{
    int cmp;

    if (x.head == nullptr)
    {
        return -1;
    }

    cmp = (*head < *x.head);

    return cmp;
}
