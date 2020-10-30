#include "list.h"

int list::read(const char *fname)
{
    FILE *f;
    int res;
    list_node *end;
    list_node *curr;
    list_node tmp;

    head = new list_node();

    if (!(f = fopen(fname, "r")))
    {
        del();
        return student::OPEN_ERROR;
    }

    if (head->readFileStudent(f) != student::SUCCESS)
    {
        del();
        fclose(f);
        return student::READ_ERROR;
    }

    head->setNext(nullptr);
    end = head;

    while((res = tmp.readFileStudent(f)) == student::SUCCESS)
    {
        curr = new list_node();

        curr->swap(tmp);
        curr->setNext(nullptr);
        end->setNext(curr);
        end = curr;
    }

    if (feof(f))
    {
        fclose(f);
        return student::SUCCESS;
    }

    if (res != student::SUCCESS)
    {
        del();
        fclose(f);
        return student::READ_ERROR;
    }

    return student::SUCCESS;
}


void list::del()
{
    list_node *curr;
    list_node *next;

    for(curr = head; curr; curr = next)
    {
        next = curr->getNext();

        curr->remove();
        delete curr;
    }
}


void list::print(int max_print)
{
    int i;
    list_node *curr;

    for (i = 0, curr = head; i < max_print && curr; i++, curr = curr->getNext())
    {
        curr->print();
    }

    printf("\n");
}


void printList(list_node *head)
{
    list_node *curr;

    for (curr = head; curr; curr = curr->getNext())
    {
        curr->print();
    }

    printf("\n");
}



int list::getLength()
{
    list_node *curr;
    int len;

    len = 0;

    for (curr = head; curr; curr = curr->getNext())
    {
        len++;
    }

    return len;
}


int list::getLessThanPrevious()
{
    int ans;
    int res;
    list_node *curr;

    ans = 0;

    for (curr = head; curr->getNext(); curr = curr->getNext())
    {
        res = (*curr->getNext() < *curr);

        if (res == 1)
        {
            ans++;
        }
    }

    return ans;
}


