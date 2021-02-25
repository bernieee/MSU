#include "query.h"
#define LEN 1234

query::~query()
{
    if (s)
        delete [] s;
    if (t)
        delete [] t;
    if (x)
        delete [] x;
}


int query::parse(int task_num, char *s_new, char *t_new, char *x_new)
{
    int s_len = strlen(s_new);
    int t_len = strlen(t_new);
    int x_len = strlen(x_new);

    switch (task_num)
    {
        case 1:
            type = query_type::FIND;
            num_of_words = query_num_of_words::ONE_WORD;
            operation = query_operation::EQUAL;
            break;
        case 2:
            type = query_type::FIND;
            num_of_words = query_num_of_words::ALL_WORDS;
            operation = query_operation::EQUAL;
            break;
        case 3:
            type = query_type::REPLACE;
            num_of_words = query_num_of_words::ALL_WORDS;
            operation = query_operation::EQUAL;
            x = new char[x_len + 1];
            strcpy(x, x_new);
            x[x_len] = '\0';
            break;
        case 4:
            type = query_type::FIND;
            num_of_words = query_num_of_words::ONE_WORD;
            operation = checkOperation(x_new);
            break;
        case 5:
            type = query_type::FIND;
            num_of_words = query_num_of_words::ALL_WORDS;
            operation = checkOperation(x_new);
            break;
        default:
            return PARSE_ERROR;
    }

    s = new char[s_len + 1];
    t = new char[t_len + 1];
    strcpy(s, s_new);
    strcpy(t, t_new);

    s[s_len] = '\0';
    t[t_len] = '\0';

    /*int i = 0;
    while (i <= s_len && s[i] != '\0')
    {
        printf("s[i] = %c\n", s[i]);
        i++;
    }*/

    return SUCCESS;
}


query_operation query::checkOperation(char *x)
{
    if (strcmp(x, "<") == 0)
        return query_operation::LESS;
    if (strcmp(x, ">") == 0)
        return query_operation::MORE;
    if (strcmp(x, "<=") == 0)
        return query_operation::LESS_OR_EQUAL;
    if (strcmp(x, ">=") == 0)
        return query_operation::MORE_OR_EQUAL;
    if (strcmp(x, "=") == 0)
        return query_operation::EQUAL;
    if (strcmp(x, "<>") == 0)
        return query_operation::NOT_EQUAL;
    return query_operation::NONE;
}


compare query::checkCompare(int cmp, query_operation operation)
{
    switch (operation)
    {
        case query_operation::LESS:
            return (compare)(cmp < 0);
        case query_operation::MORE:
            return (compare)(cmp > 0);
        case query_operation::LESS_OR_EQUAL:
            return (compare)(cmp <= 0);
        case query_operation::MORE_OR_EQUAL:
            return (compare)(cmp >= 0);
        case query_operation::EQUAL:
            return (compare)(cmp == 0);
        case query_operation::NOT_EQUAL:
            return (compare)(cmp != 0);
        default:
            return compare::NOT_SATISFIES_CONDITION;
    }
}


compare query::applyFind(char *str, char *buf)
{
    int n = strlen(str);
    //int s_len = strlen(s);
    //char *buf;
    int count = 0;
    int cmp;
    char *found;
    compare res;

    if (num_of_words == query_num_of_words::ALL_WORDS)
    {
        res = compare::SATISFIES_CONDITION;
    }
    else
    {
        res = compare::NOT_SATISFIES_CONDITION;
    }

    //buf = new char[n + 1];

    for (int i = 0; i < n; i++)
    {
        if (strchr(t, str[i]))
        {
            if (count != 0)
            {
                int j = 0;
                buf[count] = '\0';

                //cmp = strcmp(buf, s);
                while (s[j] != '\0')
                {
                    int k = 0;

                    while (s[j] != '\0' && strchr(t, s[j]))
                    {
                        j++;
                    }

                    if (s[j] == '\0')
                    {
                        break;
                    }

                    //printf("buf = %s  s = %s\n", buf, s + j);

                    while (buf[k] != '\0' && s[k + j] != '\0' && !(found = strchr(t, s[k + j])))
                    {
                        if (buf[k] < s[k + j])
                        {
                            cmp = -1;
                            break;
                        }

                        if (buf[k] > s[k + j])
                        {
                            cmp = 1;
                            break;
                        }

                        k++;
                    }

                    found = strchr(t, s[k + j]);

                    if ((buf[k] == '\0' && found) || (buf[k] == '\0' && s[k + j] == '\0'))
                    {
                        cmp = 0;
                    }
                    else if (buf[k] == '\0')
                    {
                        cmp = -1;
                    }
                    else if (s[k + j] == '\0' || found)
                    {
                        cmp = 1;
                    }

                    j += k;

                    //printf("j = %d\n", j);

                    while (s[j] != '\0' && !strchr(t, s[j]))
                    {
                        j++;
                    }

                    res = checkCompare(cmp, operation);

                    //printf("j = %d\n", j);

                    //printf("cmp = %d  res = %d\n", cmp, (int)res);

                    if (res == compare::SATISFIES_CONDITION && num_of_words == query_num_of_words::ALL_WORDS)
                    {
                        break;
                    }

                    if (res == compare::SATISFIES_CONDITION && num_of_words == query_num_of_words::ONE_WORD)
                    {
                        //delete [] buf;
                        return compare::SATISFIES_CONDITION;
                    }
                }

                if (res == compare::NOT_SATISFIES_CONDITION && num_of_words == query_num_of_words::ALL_WORDS)
                {
                    //delete [] buf;
                    return compare::NOT_SATISFIES_CONDITION;
                }

            }

            count = 0;
        }
        else
        {
            buf[count] = str[i];
            count++;
        }
    }

    if (count != 0)
    {
        int j = 0;
        buf[count] = '\0';

        //cmp = strcmp(buf, s);
        while (s[j] != '\0')
        {
            int k = 0;

            while (s[j] != '\0' && strchr(t, s[j]))
            {
                j++;
            }

            if (s[j] == '\0')
            {
                break;
            }

            while (buf[k] != '\0' && s[k + j] != '\0' && !(found = strchr(t, s[k + j])))
            {
                if (buf[k] < s[k + j])
                {
                    cmp = -1;
                    break;
                }

                if (buf[k] > s[k + j])
                {
                    cmp = 1;
                    break;
                }

                k++;
            }

            found = strchr(t, s[k + j]);

            if ((buf[k] == '\0' && found) || (buf[k] == '\0' && s[k + j] == '\0'))
            {
                cmp = 0;
            }
            else if (buf[k] == '\0')
            {
                cmp = -1;
            }
            else if (s[k + j] == '\0' || found)
            {
                cmp = 1;
            }

            j += k;

            while (s[j] != '\0' && !strchr(t, s[j]))
            {
                j++;
            }

            res = checkCompare(cmp, operation);

            if (res == compare::SATISFIES_CONDITION && num_of_words == query_num_of_words::ALL_WORDS)
            {
                break;
            }

            if (res == compare::SATISFIES_CONDITION && num_of_words == query_num_of_words::ONE_WORD)
            {
                //delete [] buf;
                return compare::SATISFIES_CONDITION;
            }
        }

        if (res == compare::NOT_SATISFIES_CONDITION && num_of_words == query_num_of_words::ALL_WORDS)
        {
            //delete [] buf;
            return compare::NOT_SATISFIES_CONDITION;
        }
    }

    if (res == compare::NOT_SATISFIES_CONDITION)
    {
        //delete [] buf;
        return compare::NOT_SATISFIES_CONDITION;
    }
    else
    {
        //delete [] buf;
        return compare::SATISFIES_CONDITION;
    }
}


int query::applyReplace(char *str, char *buf, FILE *f)
{
    int n = strlen(str);
    //char *buf;
    int count = 0;
    int cmp;
    int ans = 0;
    char *found;
    compare res = compare::NOT_SATISFIES_CONDITION;

    //buf = new char[n + 1];

    for (int i = 0; i < n; i++)
    {
        if (strchr(t, str[i]))
        {
            if (count != 0)
            {
                int j = 0;
                int x_start = 0;
                int x_end = 0;
                buf[count] = '\0';

                //cmp = strcmp(buf, s);
                while (s[j] != '\0')
                {
                    int k = 0;

                    while (s[j] != '\0' && strchr(t, s[j]))
                    {
                        j++;
                    }

                    if (s[j] == '\0')
                    {
                        break;
                    }

                    while (x[x_start] != '\0' && strchr(t, x[x_start]))
                    {
                        x_start++;
                    }

                    x_end = x_start;

                    while (x[x_end] != '\0' && !strchr(t, x[x_end]))
                    {
                        x_end++;
                    }

                    //printf("buf = %s  s = %s\n", buf, s + j);

                    while (buf[k] != '\0' && s[k + j] != '\0' && !(found = strchr(t, s[k + j])))
                    {
                        if (buf[k] < s[k + j])
                        {
                            cmp = -1;
                            break;
                        }

                        if (buf[k] > s[k + j])
                        {
                            cmp = 1;
                            break;
                        }

                        k++;
                    }

                    found = strchr(t, s[k + j]);

                    if ((buf[k] == '\0' && found) || (buf[k] == '\0' && s[k + j] == '\0'))
                    {
                        cmp = 0;
                    }
                    else if (buf[k] == '\0')
                    {
                        cmp = -1;
                    }
                    else if (s[k + j] == '\0' || found)
                    {
                        cmp = 1;
                    }

                    j += k;

                    while (s[j] != '\0' && !strchr(t, s[j]))
                    {
                        j++;
                    }

                    res = checkCompare(cmp, operation);
                    //printf("j = %d\n", j);

                    //printf("cmp = %d  res = %d\n", cmp, (int)res);


                    if (res == compare::SATISFIES_CONDITION)
                    {
                        ans = 1;
                        for (int p = x_start; p < x_end; p++)
                        {
                            fprintf(f, "%c", x[p]);
                        }

                        break;
                    }
                }

                if (res == compare::NOT_SATISFIES_CONDITION)
                {
                    fprintf(f, "%s", buf);
                }
            }

            fprintf(f, "%c", str[i]);

            count = 0;
        }
        else
        {
            buf[count] = str[i];
            count++;
        }
    }

    if (count != 0)
    {
        int j = 0;
        int x_start = 0;
        int x_end = 0;
        buf[count] = '\0';

        while (s[j] != '\0')
        {
            int k = 0;

            while (s[j] != '\0' && strchr(t, s[j]))
            {
                j++;
            }

            if (s[j] == '\0')
            {
                break;
            }

            while (x[x_start] != '\0' && strchr(t, x[x_start]))
            {
                x_start++;
            }

            x_end = x_start;

            while (x[x_end] != '\0' && !strchr(t, x[x_end]))
            {
                x_end++;
            }

            while (buf[k] != '\0' && s[k + j] != '\0' && !(found = strchr(t, s[k + j])))
            {
                if (buf[k] < s[k + j])
                {
                    cmp = -1;
                    break;
                }

                if (buf[k] > s[k + j])
                {
                    cmp = 1;
                    break;
                }

                k++;
            }

            found = strchr(t, s[k + j]);

            if ((buf[k] == '\0' && found) || (buf[k] == '\0' && s[k + j] == '\0'))
            {
                cmp = 0;
            }
            else if (buf[k] == '\0')
            {
                cmp = -1;
            }
            else if (s[k + j] == '\0' || found)
            {
                cmp = 1;
            }

            j += k;

            while (s[j] != '\0' && !strchr(t, s[j]))
            {
                j++;
            }

            res = checkCompare(cmp, operation);

            if (res == compare::SATISFIES_CONDITION)
            {
                ans = 1;
                for (int p = x_start; p < x_end; p++)
                {
                    fprintf(f, "%c", x[p]);
                }

                break;
            }
        }

        if (res == compare::NOT_SATISFIES_CONDITION)
        {
            fprintf(f, "%s", buf);
        }
    }

    //delete [] buf;
    return ans;
}


int query::processQuery(char *a_fname, char *b_fname)
{
    FILE *fa;
    FILE *fb;
    char buf[LEN];
    char tmp[LEN];
    int res = 0;
    int i;
    int n = 0;

    if (!(fa = fopen(a_fname, "r")))
    {
        return OPEN_ERROR;
    }

    if (!(fb = fopen(b_fname, "w")))
    {
        fclose(fa);
        return OPEN_ERROR;
    }

    while (fgets(buf, LEN, fa))
    {
        n++;
        i = 0;

        while (buf[i] != '\n')
        {
            i++;
            if (buf[i] == '\n')
            {
                buf[i] = '\0';
                break;
            }
        }

        switch (type)
        {
            case query_type::FIND:
                if (applyFind(buf, tmp) == compare::SATISFIES_CONDITION)
                {
                    res++;
                    fprintf(fb, "%s\n", buf);
                }
                break;
            case query_type::REPLACE:
                res += applyReplace(buf, tmp, fb);
                fprintf(fb, "\n");
                break;
            default:
                fclose(fa);
                fclose(fb);
                return TYPE_ERROR;
        }
    }

    fclose(fa);
    fclose(fb);
    return res;
}
