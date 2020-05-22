int maxlen_between_local_max(list *head) //4 not strictly
{
    int res1;
    int res2;
    int len;
    int flag;
    int max_len;
    list *curr1;
    list *curr;

    flag = 0;
    len = 0;
    max_len = -1;

    res1 = strcmp(head->string, head->next->string);

    curr1 = head->next;

    while (curr1->next && res1 < 0)//find first max
    {
        curr1 = curr1->next;
        res1 = strcmp(curr1->string, curr1->next->string);
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
}
