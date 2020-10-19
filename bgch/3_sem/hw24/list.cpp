#include "list.h"

int list::read(const char *fname)
{
    FILE *f;
    list_node *end;
    list_node *curr;

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
    head->setPrev(nullptr);
    end = head;

    while(!feof(f))
    {
        curr = new list_node();

        if (curr->readFileStudent(f) != student::SUCCESS)
        {
            delete curr;
            del();
            fclose(f);
            return student::READ_ERROR;
        }

        curr->setNext(nullptr);
        curr->setPrev(end);
        end->setNext(curr);
        end = curr;
    }

    fclose(f);
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


list_node* list::getElement(int j)
{
    int i;
    list_node *curr;

    for (i = 0, curr = head; i < j && curr; i++, curr = curr->getNext())
    {
        continue;
    }

    return curr;
}


int list::move(int n, int k, int j, int steps)// 1
{
    list_node *tmp;

    tmp = getElement(j);

    for (int i = 0; i < steps; i++)
    {
        j = (j + k) % n;

        if (j < 0)
        {
            j = n + j;
        }

        tmp->swap(*getElement(j));
    }

    return 0;
}


static int gcd(int m, int n)// 1
{
    while (m > 0)
    {
        n %= m;
        n += m;
        m = n - m;
        n -= m;
    }
    return n;
}


void list::cycle(int k)// to the right 1
{
    int i;
    int n;
    int gcd_res;
    int steps;

    n = getLength();
    i = 0;
    k = (k % n);
    gcd_res = gcd(n, abs(k));

    if (gcd_res == 1)
    {
        if (k >= 0)
        {
            move(n, k, 0, n);
        }
        else
        {
            move(n, k, n - 1, n);
        }
    }
    else
    {
        steps = n / gcd_res;

        while (i < gcd_res)
        {
            if (k >= 0)
            {
                move(n, k, i, steps);
            }
            else
            {
                move(n, k, n - i - 1, steps);
            }

            i++;
        }
    }
}


void list::removeElemsGreaterThanAnyOfKPrevious(int k)// 2
{
    int i;
    int j;
    int len;
    list_node *prev;;
    list_node *next;
    list_node *curr_i;
    list_node *curr_j;
    list_node *min;
    list_node *end;

    len = getLength();

    if (k == 0 || k >= len)
        return;

    for (curr_i = head; curr_i->getNext(); curr_i = curr_i->getNext())
    {
        continue;
    }

    end = curr_i;
    next = nullptr;
    min = end->getPrev();

    for (i = 0, curr_i = end->getPrev(); i < k && curr_i; i++, curr_i = curr_i->getPrev())
    {
        if ((*curr_i < *min) == 1)
        {
            min = curr_i;
        }
    }

    for (j = 0, curr_j = end; j < len - k && curr_j; j++, curr_j = prev)
    {
        prev = curr_j->getPrev();

        if ((*curr_j < *min) == 1)
        {
            next = curr_j;
        }
        else
        {
            if (next != nullptr)
            {
                next->setPrev(prev);
                prev->setNext(next);
            }
            else
            {
                end = prev;
                end->setNext(nullptr);
            }

            curr_j->remove();
            delete curr_j;
        }

        min = prev->getPrev();

        for (i = 0, curr_i = prev->getPrev(); i < k && curr_i; i++, curr_i = curr_i->getPrev())
        {
            if ((*curr_i < *min) == 1)
            {
                min = curr_i;
            }
        }
    }
}


void list::removeElemsGreaterThanAnyOfKNext(int k)// 3
{
    int i;
    int j;
    int len;
    list_node *prev;;
    list_node *next;
    list_node *curr_i;
    list_node *curr_j;
    list_node *min;

    min = head->getNext();

    len = getLength();

    if (k == 0 || k >= len)
        return;

    for (i = 0, curr_i = head->getNext(); i < k && curr_i; i++, curr_i = curr_i->getNext())
    {
        if ((*curr_i < *min) == 1)
        {
            min = curr_i;
        }
    }

    prev = nullptr;

    for (j = 0, curr_j = head; j < len - k && curr_j; j++, curr_j = next)
    {
        next = curr_j->getNext();

        if ((*curr_j < *min) == 1)
        {
            prev = curr_j;
        }
        else
        {
            if (prev != nullptr)
            {
                prev->setNext(next);
                next->setPrev(prev);
            }
            else
            {
                head = next;
                next->setPrev(nullptr);
            }

            curr_j->remove();
            delete curr_j;
        }

        min = next->getNext();

        for (i = 0, curr_i = next->getNext(); i < k && curr_i; i++, curr_i = curr_i->getNext())
        {
            if ((*curr_i < *min) == 1)
            {
                min = curr_i;
            }
        }
    }
}


//void list::removeLocalMax(int k)// k on the right and on the left; 4



static void deleteSeq(list_node *start, int len)
{
    int i;
    list_node *curr;
    list_node *next;

    for (i = 0, curr = start; i <= len && curr; i++, curr = next)
    {
        next = curr->getNext();

        curr->remove();
        delete curr;
    }

}


void list::removeConstSeq(int k)// not strictly; len not less than k; 5
{
    int len;
    list_node *curr;
    list_node *start;
    list_node *next;
    list_node *prev;

    len = 0;
    start = nullptr;
    prev = nullptr;

    for (curr = head; curr->getNext(); curr = next)
    {
        next = curr->getNext();

        if ((*curr < *next) == 0)
        {
            if (len == 0)
            {
                start = curr;
            }

            len++;
        }
        else
        {
            if (len >= k)
            {
                if (prev != nullptr)
                {
                    prev->setNext(next);
                    next->setPrev(next);
                }
                else
                {
                    head = next;
                }

                deleteSeq(start, len);
            }
            else
            {
                prev = curr;
            }

            len = 0;
        }
    }

    if (len >= k)
    {
        if (prev != nullptr)
        {
            prev->setNext(nullptr);
        }
        else
        {
            head = nullptr;
        }

        deleteSeq(start, len);
    }
}


void list::removeDownSeq(int k)// not strictly; len not less than k; 6
{
    int len;
    list_node *curr;
    list_node *start;
    list_node *next;
    list_node *prev;

    len = 0;
    start = nullptr;
    prev = nullptr;

    for (curr = head; curr->getNext(); curr = next)
    {
        next = curr->getNext();

        if ((*curr < *next) <= 0)
        {
            if (len == 0)
            {
                start = curr;
            }

            len++;
        }
        else
        {
            if (len >= k)
            {
                if (prev != nullptr)
                {
                    prev->setNext(next);
                    next->setPrev(prev);
                }
                else
                {
                    head = next;
                }

                deleteSeq(start, len);
            }
            else
            {
                prev = curr;
            }

            len = 0;
        }
    }

    if (len >= k)
    {
        if (prev != nullptr)
        {
            prev->setNext(nullptr);
        }
        else
        {
            head = nullptr;
        }

        deleteSeq(start, len);
    }
}


void list::removeSeqBetweenConstSeq(int k)// len not less than k; 7
{
    int len;
    list_node *curr;
    list_node *start;
    list_node *next;
    list_node *prev;

    len = 0;
    start = nullptr;
    prev = nullptr;

    for (curr = head; curr->getNext(); curr = next)
    {
        next = curr->getNext();

        if ((*curr < *next) == 0)
        {
            if (len >= k)
            {
                if (prev != nullptr)
                {
                    prev->setNext(curr);
                    curr->setPrev(prev);
                }
                else
                {
                    head = next;
                }

                deleteSeq(start, len - 2);
            }
            else
            {
                prev = curr;
            }

            len = 0;

        }
        else
        {
            if (len == 0)
            {
                prev = curr;
                start = next;
            }

            len++;
        }
    }

    if (len >= k)
    {
        if (prev != nullptr)
        {
            prev->setNext(nullptr);
        }
        else
        {
            head = nullptr;
        }

        deleteSeq(start, len - 2);
    }
}


void list::removeSeqBetweenUpSeq(int k)// not strictly; len not less than k; 8
{
    int len;
    list_node *curr;
    list_node *start;
    list_node *next;
    list_node *prev;

    len = 0;
    start = nullptr;
    prev = nullptr;

    for (curr = head; curr->getNext(); curr = next)
    {
        next = curr->getNext();

        if ((*curr < *next) >= 0)
        {
            if (len >= k)
            {
                if (prev != nullptr)
                {
                    prev->setNext(curr);
                    curr->setPrev(prev);
                }
                else
                {
                    head = next;
                }

                deleteSeq(start, len - 2);
            }
            else
            {
                prev = curr;
            }

            len = 0;

        }
        else
        {
            if (len == 0)
            {
                prev = curr;
                start = next;
            }

            len++;
        }
    }

    if (len >= k)
    {
        if (prev != nullptr)
        {
            prev->setNext(nullptr);
        }
        else
        {
            head = nullptr;
        }

        deleteSeq(start, len - 2);
    }
}

