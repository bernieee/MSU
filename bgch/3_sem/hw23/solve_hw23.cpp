#include "solve_hw23.h"
#include "student.h"


int numOfMaxElems(list *head) //1
{
    int ans;
    int res;
    list *curr;
    list *max;

    max = nullptr;

    max = head;

    ans = 0;

    for (curr = head; curr; curr = curr->getNext())
    {
        res = (*max < *curr);

        if (res == 0)
        {
            ans++;
        }
        else if (res == 1)
        {
            ans = 1;
            max = curr;
        }
    }

    return ans;
}


int numOfElemsGreaterThanPrevious(list *head) //2
{
    int ans;
    int res;
    list *curr;

    ans = 0;

    for (curr = head; curr->getNext(); curr = curr->getNext())
    {
        res = (*curr < *curr->getNext());

        if (res == 1)
        {
            ans++;
        }
    }

    return ans;
}


int numberOfLocalMax(list *head) //3 not strictly
{
    int ans;
    int res1;
    int res2;
    list *curr;

    ans = 0;

    if (!head->getNext())
    {
        return 1;
    }

    res1 = (*head < *head->getNext());

    if (res1 <= 0)// >=
    {
        ans++;
    }

    for (curr = head->getNext(); curr->getNext(); curr = curr->getNext())
    {
        res2 = (*curr < *curr->getNext());

        if (res1 >= 0 && res2 <= 0)
        {
            ans++;
        }

        if ((curr->getNext())->getNext() == nullptr && res2 >= 0)
        {
            ans++;
        }

        res1 = res2;
    }

    return ans;
}


int whatSequence(list *head)
{
    list *prev;
    list *curr;
    int up;
    int down;
    int no;
    int res;

    if (!head->getNext())
    {
        return 4;
    }

    prev = head;
    up = down = no = 0;

    for(curr = head->getNext(); curr; curr = curr->getNext())
    {
        res = (*prev < *curr);

        if (res == 1)
        {
            up++;
        }
        else if (res == -1)
        {
            down++;
        }
        else
        {
            no++;
        }
    }

    if ((up > 0) && (down > 0))
    {
        return 0;
    }
    else if (up > 0)
    {
        return 1;
    }
    else if (down > 0)
    {
        return 2;
    }
    else
    {
        return 3;
    }
}


int maxlenUpSeqence(list *head) //5 strictly
{
    int res;
    int len;
    int max_len;
    list *curr;

    len = 0;
    max_len = 0;

    for (curr = head; curr->getNext(); curr = curr->getNext())
    {
        res = (*curr < *curr->getNext());

        if (res == 1)
        {
            len++;
        }
        else if (len != 0)
        {
            max_len = fmax(len + 1, max_len);
            len = 0;
        }

    }

    return max_len;
}


int numOfConstSeqence(list *head) //6 strictly
{
    int ans;
    int res;
    int len;
    int flag;
    list *curr;

    flag = 0;

    ans = 0;
    len = 0;

    for (curr = head; curr->getNext(); curr = curr->getNext())
    {
        res = (*curr < *curr->getNext());

        if (res == 0)
        {
            flag++;
            len++;
        }
        else if (len != 0)
        {
            ans++;
            len = 0;
        }
    }

    if (flag == 0)
    {
        return 0;
    }

    return ans;
}


int maxlenBetweenConstSeqence(list *head) //7 strictly
{
    int res;
    int len_const;
    int len;
    int max_len;
    list *curr;
    list *curr1;

    if (!head->getNext())
    {
        return 1;
    }

    len_const = 0;
    len = 0;
    max_len = -1;

    res = (*head < *head->getNext());

    curr1 = head->getNext();

    while (curr1->getNext() && res != 0)//find first
    {
        res = (*curr1 < *curr1->getNext());
        curr1 = curr1->getNext();
    }

    for (curr = curr1; curr->getNext(); curr = curr->getNext())
    {
        res = (*curr < *curr->getNext());

        if (res == 0)
        {
            if (len != 0)
            {
                max_len = fmax(len - 1, max_len);
                len = 0;
                len_const = 0;
            }

            len_const = 1;
        }
        else if (len_const != 0)
        {
            len++;
        }
    }

    return max_len;
}


int maxlenMonotonSeqence(list *head) //8 not strictly
{
    int res;
    int len;
    int max_len;
    int flag; //0 - up, 1, down
    int flag_const;
    int len_const;
    list *curr;

    len = 0;
    flag = -1;
    flag_const = 0;
    len_const = 0;
    max_len = 0;

    for (curr = head; curr->getNext(); curr = curr->getNext())
    {
        res = *curr < *curr->getNext();

        if (res < 0)//down
        {
            if (flag != 1)
            {
                if (len + len_const != 0)
                {
                    max_len = fmax(len + len_const, max_len);
                    len = 0;
                }

                if (flag_const == 1)
                {
                    len = len_const;
                    len_const = 0;
                }

                if (flag == -1)
                {
                    len_const = 0;
                }

                flag = 1;//down
            }

            flag_const = 0;
            len++;
        }
        else if (res > 0)//up
        {
            if (flag != 0)
            {
                if (len + len_const != 0)
                {
                    max_len = fmax(len + len_const, max_len);
                    len = 0;
                }

                if (flag_const == 1)
                {
                    len = len_const;
                    len_const = 0;
                }

                if (flag == -1)
                {
                    len_const = 0;
                }

                flag = 0;//up
            }

            flag_const = 0;
            len++;
        }
        else
        {
            if (flag_const == 0)
            {
                len_const = 0;
                flag_const = 1;
            }

            len_const++;
        }

        //printf("%d  %d  %d  %d\n", len, max_len, len_const, flag);
    }

    if (len + len_const != 0)
    {
        max_len = fmax(len + len_const, max_len);
    }

    if (len == 0)
    {
        return len_const;
    }

    return max_len + 1;
}
