#include "io_hw20.h"
#include "solve_hw20.h"


int number_of_max_elems(list *head) //1
{
    int ans;
    int res;
    list *curr;
    list *max;

    max = head;

    ans = 0;

    for (curr = head; curr; curr = curr->next)
    {
        res = strcmp(max->string, curr->string);

        if (res == 0)
        {
            ans++;
        }
        else if (res < 0)
        {
            ans = 1;
            max = curr;
        }
    }

    return ans;
}


int number_of_elems_greater_than_previous(list *head) //2
{
    int ans;
    list *curr;

    ans = 0;

    for (curr = head; curr->next; curr = curr->next)
    {
        if (strcmp(curr->next->string, curr->string) > 0)
        {
            ans++;
        }
    }

    return ans;
}


int number_of_local_max(list *head) //3 not strictly
{
    int ans;
    int res1;
    int res2;
    list *curr;

    ans = 0;

    if (!head->next)
    {
        return 1;
    }

    res1 = strcmp(head->string, head->next->string);

    if (res1 >= 0)
    {
        ans++;
    }

    for (curr = head->next; curr->next; curr = curr->next)
    {
        res2 = strcmp(curr->string, curr->next->string);

        if (res1 <= 0 && res2 >= 0)
        {
            ans++;
        }

        if (curr->next->next == NULL && res2 <= 0)
        {
            ans++;
        }

        res1 = res2;
    }

    return ans;
}


int maxlen_between_local_max(list *head) //4 not strictly
{
    int res1;
    int res2;
    int len;
    int flag;
    int max_len;
    list *curr1;
    list *curr;

    if (!head->next)
    {
        return 1;
    }

    flag = 0;
    len = 0;
    max_len = -1;

    res1 = strcmp(head->string, head->next->string);

    curr1 = head->next;

    while (curr1->next && res1 < 0)//find first max
    {
        //curr1 = curr1->next;
        res1 = strcmp(curr1->string, curr1->next->string);
        curr1 = curr1->next;
    }

    for (curr = curr1; curr->next; curr = curr->next)
    {
        res2 = strcmp(curr->string, curr->next->string);

        if (!(res1 <= 0 && res2 >= 0))
        {
            len++;
        }
        else
        {
            max_len = fmax(len, max_len);
            len = 0;
        }

        if (curr->next->next == NULL && res2 <= 0)
        {
            flag = 1;
        }

        res1 = res2;
    }

    if (max_len != -1 && flag == 1)
    {
        max_len = fmax(len, max_len);
    }

    return max_len;
}


int maxlen_up_seqence(list *head) //5 strictly
{
    int res;
    int len;
    int max_len;
    list *curr;

    len = 0;
    max_len = 0;

    for (curr = head; curr->next; curr = curr->next)
    {
        res = strcmp(curr->string, curr->next->string);

        if (res < 0)
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


int number_of_const_seqence(list *head) //6 strictly
{
    int ans;
    int res;
    int len;
    list *curr;

    ans = 0;
    len = 0;

    for (curr = head; curr->next; curr = curr->next)
    {
        res = strcmp(curr->string, curr->next->string);

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

    return ans;
}


int maxlen_between_const_seqence(list *head) //7 strictly
{
    int res;
    int len_const;
    int len;
    int max_len;
    list *curr;
    list *curr1;

    if (!head->next)
    {
        return 1;
    }

    len_const = 0;
    len = 0;
    max_len = -1;

    res = strcmp(head->string, head->next->string);

    curr1 = head->next;

    while (curr1->next && res != 0)//find first
    {
        res = strcmp(curr1->string, curr1->next->string);
        curr1 = curr1->next;
    }

    for (curr = curr1; curr->next; curr = curr->next)
    {
        res = strcmp(curr->string, curr->next->string);

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


list *list_without_elems_not_greater_then_next(list *head) //8
{
    int res;
    list *curr;
    list *prev;

    if (!head->next)
    {
        return head;
    }

    res = 0;

    while (head->next && strcmp(head->string, head->next->string) >= 0)
    {
        curr = head;
        head = head->next;
        free(curr->string);
        free(curr);
    }

    prev = head;

    for (curr = head; curr && curr->next; curr = prev->next)
    {
        res = strcmp(curr->string, curr->next->string);

        if (res >= 0)
        {
            prev->next = curr->next;

            free(curr->string);
            free(curr);
        }
        else
        {
            prev = curr;
        }
    }

    return head;
}


list *list_without_elems_not_greater_then_neighbours(list *head) //9
{
    int res1;
    int res2;
    list *curr;
    list *prev;

    if (!head->next)
    {
        return head;
    }

    prev = head;

    res1 = strcmp(head->string, head->next->string);

    for (curr = head->next; curr && curr->next; curr = prev->next)
    {
        res2 = strcmp(curr->string, curr->next->string);

        if (res1 <= 0 && res2 >= 0)
        {
            prev->next = curr->next;

            free(curr->string);
            free(curr);
        }
        else
        {
            prev = curr;
        }

        res1 = res2;
    }

    return head;
}


list *list_without_down_sequences(list *head) //10 not strictly
{
    int res1;
    int res2;
    list *curr;
    list *prev;

    if (!head->next)
    {
        return head;
    }

    prev = NULL;

    res1 = res2 = strcmp(head->string, head->next->string);

    while (head->next->next && res1 >= 0)
    {
        res1 = strcmp(head->next->string, head->next->next->string);
        curr = head;
        head = head->next;
        free(curr->string);
        free(curr);
    }

    prev = head;

    for (curr = head->next; curr && curr->next; curr = prev->next)
    {
        res2 = strcmp(curr->string, curr->next->string);

        if (res1 >= 0 || res2 >= 0)
        {
            prev->next = curr->next;

            free(curr->string);
            free(curr);
        }
        else
        {
            prev = curr;
        }

        res1 = res2;
    }

    if (res1 >= 0 || res2 >= 0)
    {
        prev->next = curr->next;

        free(curr->string);
        free(curr);
    }

    return head;
}

