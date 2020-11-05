#include "list.h"

int readList(const char *fname, list **new_head)
{
    FILE *f;
    int size;
    int res;
    list *head;
    list *end;
    list *curr;
    list tmp;

    size = 0;
    curr = nullptr;
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

    while((res = tmp.readFileStudent(f)) == student::SUCCESS)
    {
        curr = new list();

        curr->swap(tmp);
        curr->setNext(nullptr);
        end->setNext(curr);
        end = curr;
        size++;
    }

    if (feof(f))
    {
        *new_head = head;

        fclose(f);
        return size;
    }

    if (res != student::SUCCESS)
    {
        delList(head);
        fclose(f);
        return student::READ_ERROR;
    }

    return student::SUCCESS;
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


