#include "list.h"

static inline void swap(list_node *a, list_node *b)
{
    list_node *tmp;

    tmp = b->getNext();
    b->setNext(a);
    a->setNext(tmp);
}


void list::bubbleSort() // 1
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


void list::minSort() // 2
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


void list::insertSort() // 3
{
    list_node *new_head;

    list_node *curr;
    list_node *prev;
    list_node *tmp;

    new_head = head->getNext();
    head->setNext(nullptr);

    while (new_head)
    {
        prev = nullptr;
        tmp = new_head;
        new_head = new_head->getNext();
        tmp->setNext(nullptr);

        for (curr = head; curr; curr = curr->getNext())
        {
            if ((*tmp < *curr) == 1)
            {
                break;
            }

            prev = curr;
        }

        if (prev)
        {
            prev->setNext(tmp);
            tmp->setNext(curr);
        }
        else
        {
            head = tmp;
            head->setNext(curr);
        }
    }
}


static void merge(list_node **start1, list_node **end1, list_node **start2, list_node **end2)
{
    list_node *curr1;
    list_node *curr2;
    list_node *end;
    list_node *tmp;

    if ((**start1 < **start2) == -1) // check if start2's first node is higher than start1's
    {
        tmp = *start1;
        *start1 = *start2;
        *start2 = tmp;

        tmp = *end1;
        *end1 = *end2;
        *end2 = tmp;
    }

    curr1 = *start1;
    curr2 = *start2;
    end = (*end2)->getNext();

    while ((curr1 != (*end1)) && (curr2 != end))
    {
        if ((*curr2 < *curr1->getNext()) == 1)
        {
            tmp = curr2->getNext();
            curr2->setNext(curr1->getNext());
            curr1->setNext(curr2);
            curr2 = tmp;
        }

        curr1 = curr1->getNext();
    }

    if (curr1 == (*end1))
    {
        curr1->setNext(curr2);
    }
    else
    {
        *end2 = *end1;
    }
}


void list::mergeSort() // 4
{
    int len;
    int step;
    int counter;
    int first_in;
    list_node *start1;
    list_node *end1;
    list_node *start2;
    list_node *end2;
    list_node *prev;
    list_node *next;

    prev = nullptr;

    len = getLength();

    for (step = 1; step < len; step *= 2)
    {
        start1 = head;

        while (start1)
        {
            first_in = 0;

            if (start1 == head)
            {
                first_in = 1;
            }

            counter = step;
            end1 = start1;

            while (counter != 1 && end1->getNext())
            {
                end1 = end1->getNext();
                counter--;
            }

            counter = step;
            start2 = end1->getNext();
            end2 = start2;

            if (start2 == nullptr)
            {
                break;
            }

            while (counter != 1 && end2->getNext())
            {
                end2 = end2->getNext();
                counter--;
            }

            next = end2->getNext();

            merge(&start1, &end1, &start2, &end2);

            if (first_in == 1)
            {
                head = start1;
            }
            else
            {
                prev->setNext(start1);
            }

            prev = end2;
            start1 = next;
        }

        prev->setNext(start1);
    }
}






/*
void quickSort();
*/
