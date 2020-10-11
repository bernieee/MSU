#include "list.h"

int readList(const char *fname, list **new_head)
{
    FILE *f;
    int size;
    list *head;
    list *end;
    list *curr;

    size = 0;
    head = new list();

    if (!(f = fopen(fname, "r")))
    {
        delList(head);
        return student::OPEN_ERROR;
    }

    if (head->readFileStudent(f) != student::SUCCESS)
    {
        delList(head);
        fclose(f);
        return student::READ_ERROR;
    }

    head->setNext(nullptr);
    end = head;

    while(!feof(f))
    {
        curr = new list();

        if (curr->readFileStudent(f) != student::SUCCESS)
        {
            delete curr;
            delList(head);
            fclose(f);
            return student::READ_ERROR;
        }

        curr->setNext(nullptr);
        end->setNext(curr);
        end = curr;
        size++;
    }

    *new_head = head;

    fclose(f);
    return size;
}


void delList(list *head)
{
    list *curr;
    list *next;

    for(curr = head; curr; curr = next)
    {
        next = curr->getNext();

        curr->remove();
        delete curr;
    }
}


void printList(list *head, int max_print)
{
    int i;
    list *curr;

    for (i = 0, curr = head; i < max_print && curr; i++, curr = curr->getNext())
    {
        curr->print();
    }

    printf("\n");
}


