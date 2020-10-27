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
            //printf("0 %d  %d\n", new_head->getVal(), new_head->getNext()->getVal());
            flag = 1;
        }

        prev = new_head;
        curr = new_head->getNext();

        //printf("1 %d  %d  %d\n", prev->getVal(), curr->getVal(), curr->getNext()->getVal());

        for (curr = curr; curr->getNext(); curr = next)
        {
            next = curr->getNext();

            //printf("2 %d  %d  %d\n", prev->getVal(), curr->getVal(), next->getVal());

            if ((*next < *curr) == 1)
            {
                swap(curr, next);

                prev->setNext(next);
                //next = curr->getNext();
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

/*void bubbleSort(student *obj, int n)//4
{
    int flag;

    for (int i = 0; i <= n; i++)
    {
        flag = 0;

        for (int j = 0; j < n - i - 1; j++)
        {
            if (obj[j] > obj[j + 1])
            {
                obj[j].swap(obj[j + 1]);
                flag = 1;
            }
        }

        if (flag == 0)
        {
            return;
        }
    }
}


void minSort(student *obj, int n)//5
{
    int min;

    for (int i = 0; i < n; i++)
    {
        min = i;

        for (int j = i + 1; j < n; j++)
        {
            if (obj[j] < obj[min])
            {
                min = j;
            }
        }

        obj[i].swap(obj[min]);
    }
}



void minSort();
void insertSort();
void mergeSort();
void quickSort();
*/
