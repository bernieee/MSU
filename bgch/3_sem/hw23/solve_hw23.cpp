#include "solve_hw23.h"
#include "student.h"


int numOfMaxElems(list *head) //1
{
    int ans;
    int res;
    list *curr;
    list *max;

    max = head;

    ans = 0;

    for (curr = head; curr; curr = curr->getNext())
    {
        res = (*max < *curr);

        if (res == 0)//(!(*max > *curr) && !(*max < *curr))
        {
            ans++;
        }
        else if (res == 1)//(*max < *curr)
        {
            ans = 1;
            max = curr;
        }
    }

    //printf("3%s\n", max->getName());

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

        if (res == 1)//(*curr->getNext() > *curr)
        {
            //printf("%s  %s\n", curr->getNext()->getName(), curr->getName());
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

    res1 = (*head < *head->getNext());//!(*head < *head->getNext());

    if (res1 <= 0)//(res1 >= 0)// >=
    {
        ans++;
    }

    for (curr = head->getNext(); curr->getNext(); curr = curr->getNext())
    {
        res2 = (*curr < *curr->getNext()); //!(*curr < *curr->getNext());

        if (res1 >= 0 && res2 <= 0)//(res1 <= 0 && res2 >= 0)
        {
            ans++;
        }

        if ((curr->getNext())->getNext() == nullptr && res2 >= 0)//res2 <= 0)
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

        if (res == 1)//(*prev < *curr)
        {
            up++;
        }
        else if (res == -1)//(*prev > *curr)
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

        if (res == 1)//(res < 0)??
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
    list *curr;

    ans = 0;
    len = 0;

    for (curr = head; curr->getNext(); curr = curr->getNext())
    {
        res = (*curr < *curr->getNext());
        //(!(*curr > *curr->getNext()) && (!(*curr < *curr->getNext())));

        if (res == 0)
        {
            len++;
        }
        else if (len != 0)
        {
            ans++;
            len = 0;
        }
    }

    return ans + 1;
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
    //res = (!(*head < *head->getNext()) && !(*head > *head->getNext()));

    curr1 = head->getNext();

    while (curr1->getNext() && res != 0)//find first
    {
        res = (*curr1 < *curr1->getNext());
        //res = (!(*curr1 < *curr1->getNext()) && !(*curr1 > *curr1->getNext()));
        curr1 = curr1->getNext();
    }

    for (curr = curr1; curr->getNext(); curr = curr->getNext())
    {
        res = (*curr < *curr->getNext());
        //res = (!(*curr < *curr->getNext()) && !(*curr > *curr->getNext())) ;

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
                if (len + len_const != 1)
                {
                    max_len = fmax(len + len_const + 1, max_len);
                    len = 1;
                }

                if (flag == -1)
                {
                    flag_const = 0;
                }
                flag = 1;//down
            }
            len++;
        }
        else if (res > 0)//up
        {
            if (flag != 0)
            {
                if (len + len_const  != 1)
                {
                    max_len = fmax(len + len_const + 1, max_len);
                    len = 1;
                }

                if (flag == -1)
                {
                    flag_const = 0;
                }

                flag = 0;//up
            }
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
    }

    return max_len;
}


