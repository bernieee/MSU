#include "list.h"


static void swap(list_node *a, list_node *b)
{
    list_node *tmp;

    tmp = b->getNext();
    b->setNext(a);
    a->setNext(tmp);
}


void list::bubbleSort()
{
    list_node *new_head;

    list_node *curr;
    list_node *next;
    list_node *prev;
    int flag;

    new_head = head;
    head = nullptr;

    while (new_head)
    {
        prev = nullptr;
        curr = new_head;
        next = new_head->getNext();
        flag = 0;

        if ((*next < *curr) == 1)
        {
            swap(curr, next);

            new_head = next;
            flag = 1;
        }

        prev = new_head;
        curr = new_head->getNext();

        for (curr = curr; curr->getNext(); curr = next)
        {
            next = curr->getNext();

            if ((*next < *curr) == 1)
            {
                swap(curr, next);

                prev->setNext(next);
                flag = 1;
            }

            prev = curr;
        }

        next = curr->getNext();
        next = head;

        if (flag == 1)
        {
            head = curr;
            curr = nullptr;
        }
        else
        {
            head = new_head;
            return;
        }
    }
}


void list::minSort()
{
    list_node *new_head;
    list_node *end;

    list_node *curr;
    list_node *next;
    list_node *prev;
    list_node *min_next;
    list_node *min_prev;
    list_node *min;

    new_head = head;
    head = end = nullptr;

    while (new_head)
    {
        prev = nullptr;
        min_prev = nullptr;
        min_next = new_head->getNext();
        min = new_head;

        for (curr = new_head; curr; curr = next)
        {
            next = curr->getNext();

            if ((*curr < *min) == 1)
            {
                min = curr;
                min_prev = prev;
                min_next = next;
            }

            prev = curr;
        }

        if (head == nullptr)
        {
            head = min;
            end = head;
        }
        else
        {
            end->setNext(min);
            end = end->getNext();
        }

        min = nullptr;
        if (min_prev)
        {
            min_prev->setNext(min_next);
        }
        else
        {
            new_head = min_next;
        }
    }
}

/*
void insertSort();
void mergeSort();
void quickSort();
*/
