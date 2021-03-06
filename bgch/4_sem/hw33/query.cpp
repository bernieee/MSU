#include "query.h"
#define LEN 1234

query::~query()
{
    if (s)
        delete [] s;
    if (t)
        delete [] t;
}


void query::table()
{
    for (int i = 0; i < 256; i++)
    {
        table_t[i] = 0;
    }

    for (int i = 0; i < t_len; i++)
    {
        table_t[(int)t[i]] = 1;
    }
}

int query::parse(int task_num, char *s_new, char *t_new)
{
    s_len = strlen(s_new);
    t_len = strlen(t_new);

    switch (task_num)
    {
        case 1:
            type = query_type::FIND;
            num_of_words = query_num_of_words::ONE_WORD;
            operation = query_operation::EQUAL;
            replace = query_replace::ONE_SYMBOL;
            break;
        case 2:
            type = query_type::FIND;
            num_of_words = query_num_of_words::ALL_WORDS;
            operation = query_operation::EQUAL;
            replace = query_replace::ONE_SYMBOL;
            break;
        case 3:
            type = query_type::FIND;
            num_of_words = query_num_of_words::ONE_WORD;
            operation = query_operation::EQUAL;
            replace = query_replace::NONE_OR_MORE_SYMBOLS;
            break;
        case 4:
            type = query_type::FIND;
            num_of_words = query_num_of_words::ALL_WORDS;
            operation = query_operation::EQUAL;
            replace = query_replace::NONE_OR_MORE_SYMBOLS;
            break;
        case 5:
            type = query_type::FIND;
            num_of_words = query_num_of_words::ONE_WORD;
            operation = query_operation::EQUAL;
            replace = query_replace::ANY_SYMBOL_IN_INTERVAL;
            break;
        case 6:
            type = query_type::FIND;
            num_of_words = query_num_of_words::ONE_WORD;
            operation = query_operation::EQUAL;
            replace = query_replace::ANY_SYMBOL_NOT_IN_INTERVAL;
            break;
        default:
            return PARSE_ERROR;
    }

    s = new char[s_len + 1];
    t = new char[t_len + 1];
    strcpy(s, s_new);
    strcpy(t, t_new);
    table();

    return SUCCESS;
}


compare query::checkCompare(int cmp, query_operation operation)
{
    switch (operation)
    {
        case query_operation::EQUAL:
            return (compare)(cmp == 0);
        default:
            return compare::NOT_SATISFIES_CONDITION;
    }
}


/*compare query::applyFindOneWord(char *str, char *buf)
{
    int n = strlen(str);
    int count = 0;
    int cmp;
    compare res = compare::NOT_SATISFIES_CONDITION;
    compare check = compare::NOT_SATISFIES_CONDITION;
    compare make;

    for (int i = 0; i < n; i++)
    {
        //if (strchr(t, str[i]))
        if (table_t[(int)str[i]] == 1)
        {
            if (count != 0)
            {
                int j = 0;
                int k = 0;
                buf[count] = '\0';

                while (buf[k] != '\0' && s[j] != '\0')
                {
                    if (s[j] == '\\')
                    {
                        j++;
                    }
                    else
                    {
                        //printf("buf = %s  s[j] = %c\n", buf, s[j]);
                        check = checkReplace(replace, j);
                    }

                    if (check == compare::SATISFIES_CONDITION)
                    {
                        //printf("buf = %s  s[j] = %c\n", buf, s[j]);
                        make = makeReplace(replace, buf, k, j); //TODO
                        check = compare::NOT_SATISFIES_CONDITION;

                        if (make == compare::NOT_SATISFIES_CONDITION)
                        {
                            cmp = -1;
                            break;
                        }

                        k++;
                        j++;
                        continue;
                    }

                    if (buf[k] != s[j])
                    {
                        cmp = -1;
                        break;
                    }

                    k++;
                    j++;
                }

                if (buf[k] == '\0' && s[j] == '\0')
                {
                    cmp = 0;
                }
                else
                {
                    cmp = -1;
                }

                res = checkCompare(cmp, operation);

                if (res == compare::SATISFIES_CONDITION)
                {
                    return compare::SATISFIES_CONDITION;
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
        int k = 0;
        buf[count] = '\0';

        printf("buf = %s  s = %s\n", buf, s);

        while (buf[k] != '\0' && s[j] != '\0')
        {
            if (s[j] == '\\')
            {
                printf("!!\n");
                j++;
            }
            else
            {
                printf("buf = %s  s[j] = %c\n", buf, s[j]);
                check = checkReplace(replace, j);
            }

            if (check == compare::SATISFIES_CONDITION)
            {
                printf("buf = %s  s[j] = %c\n", buf, s[j]);
                make = makeReplace(replace, buf, k, j);
                check = compare::NOT_SATISFIES_CONDITION;

                if (make == compare::NOT_SATISFIES_CONDITION)
                {
                    //printf("1\n");
                    cmp = -1;
                    break;
                }

                k++;
                j++;
                continue;
            }

            if (buf[k] != s[j])
            {
                printf("k = %c j = %c\n", buf[k], s[j]);
                cmp = -1;
                break;
            }

            k++;
            j++;
        }

        if (buf[k] == '\0' && s[j] == '\0')
        {
            cmp = 0;
        }
        else
        {
            //printf("k = %c j = %c\n", buf[k], s[j]);
            cmp = -1;
        }

        res = checkCompare(cmp, operation);

        if (res == compare::SATISFIES_CONDITION)
        {
            return compare::SATISFIES_CONDITION;
        }
    }

    return res;
}*/


compare query::applyFindOneWord(char *str, char *s, char *buf)
{
    int n = strlen(str);
    int count = 0;
    int cmp;
    compare res = compare::NOT_SATISFIES_CONDITION;
    compare check = compare::NOT_SATISFIES_CONDITION;
    compare make;

    for (int i = 0; i < n; i++)
    {
        if (table_t[(int)str[i]] == 1)
        {
            if (count != 0)
            {
                int j = 0;
                buf[count] = '\0';

                while (s[j] != '\0')
                {
                    int k = 0;

                    while (s[j] != '\0' && table_t[(int)s[j]] == 1)
                    {
                        j++;
                    }

                    if (s[j] == '\0')
                    {
                        break;
                    }

                    while (buf[k] != '\0' && s[j] != '\0' && table_t[(int)s[j]] == 0)
                    {
                        if (s[j] == '\\')
                        {
                            j++;
                        }
                        else
                        {
                            check = checkReplace(replace, s[j]);
                        }

                        if (check == compare::SATISFIES_CONDITION)
                        {
                            make = makeReplace(replace, buf, s, k, j);
                            check = compare::NOT_SATISFIES_CONDITION;

                            if (make == compare::NOT_SATISFIES_CONDITION)
                            {
                                cmp = -1;
                                break;
                            }

                            k++;
                            j++;
                            continue;
                        }

                        if (buf[k] != s[j])
                        {
                            cmp = -1;
                            break;
                        }

                        k++;
                        j++;
                    }

                    if (replace == query_replace::NONE_OR_MORE_SYMBOLS)
                    {
                        while (s[j] != '\0' && s[j] == '%')
                        {
                            j++;
                        }
                    }

                    if ((buf[k] == '\0' && table_t[(int)s[j]] == 1) || (buf[k] == '\0' && s[j] == '\0'))
                    {
                        cmp = 0;
                    }
                    else
                    {
                        cmp = -1;
                    }

                    while (s[j] != '\0' && table_t[(int)s[j]] == 0)
                    {
                        j++;
                    }

                    res = checkCompare(cmp, operation);

                    if (res == compare::SATISFIES_CONDITION)
                    {
                        return compare::SATISFIES_CONDITION;
                    }
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

        while (s[j] != '\0')
        {
            int k = 0;

            while (s[j] != '\0' && table_t[(int)s[j]] == 1)
            {
                j++;
            }

            if (s[j] == '\0')
            {
                break;
            }

            while (buf[k] != '\0' && s[j] != '\0' && table_t[(int)s[j]] == 0)
            {
                if (s[j] == '\\')
                {
                    j++;
                }
                else
                {
                    check = checkReplace(replace, s[j]);
                }

                if (check == compare::SATISFIES_CONDITION)
                {
                    make = makeReplace(replace, buf, s, k, j);
                    check = compare::NOT_SATISFIES_CONDITION;

                    if (make == compare::NOT_SATISFIES_CONDITION)
                    {
                        cmp = -1;
                        break;
                    }

                    k++;
                    j++;

                    continue;
                }

                if (buf[k] != s[j])
                {
                    cmp = -1;
                    break;
                }

                k++;
                j++;
            }

            if (replace == query_replace::NONE_OR_MORE_SYMBOLS)
            {
                while (s[j] != '\0' && s[j] == '%')
                {
                    j++;
                }
            }

            if ((buf[k] == '\0' && table_t[(int)s[j]] == 1) || (buf[k] == '\0' && s[j] == '\0'))
            {
                cmp = 0;
            }
            else
            {
                cmp = -1;
            }

            while (s[j] != '\0' && table_t[(int)s[j]] == 0)
            {
                j++;
            }

            res = checkCompare(cmp, operation);

            if (res == compare::SATISFIES_CONDITION)
            {
                return compare::SATISFIES_CONDITION;
            }
        }
    }

    return res;
}


compare query::checkReplace(query_replace replace, char x)
{
    switch (replace)
    {
        case query_replace::ONE_SYMBOL:
            return (compare)(x == '_');
        case query_replace::NONE_OR_MORE_SYMBOLS:
            return (compare)(x == '%');
        case query_replace::ANY_SYMBOL_IN_INTERVAL:
            return (compare)(x == '[');
        case query_replace::ANY_SYMBOL_NOT_IN_INTERVAL:
            return (compare)(x == '[');
        default:
            return compare::NOT_SATISFIES_CONDITION;
    }
}


compare query::makeReplace(query_replace replace, char *str, char *s, int &i, int &j)
{
    switch (replace)
    {
        case query_replace::ONE_SYMBOL:
        {
            return compare::SATISFIES_CONDITION;
        }
        case query_replace::NONE_OR_MORE_SYMBOLS:
        {
            char buf[LEN];
            int k = 0;
            char *found;

            while (s[j] != '\0' && checkReplace(replace, s[j]) == compare::SATISFIES_CONDITION)
            {
                j++;
            }

            while (s[j] != '\0' && checkReplace(replace, s[j]) == compare::NOT_SATISFIES_CONDITION)
            {
                if (s[j] == '\\')
                {
                    j++;
                }

                buf[k] = s[j];
                k++;
                j++;
            }

            buf[k] = '\0';

            if ((s[j] == '\0') && k == 0)
            {
                while (str[i] != '\0')
                {
                    i++;
                }

                i--;
                j--;

                return compare::SATISFIES_CONDITION;
            }

            if ((s[j] == '\0') && k != 0)
            {
                while ((found = strstr(str + i, buf)))
                {
                    while ((str + i) != found)
                    {
                        i++;
                    }

                    i += k;
                }

                i--;
                j--;

                return compare::SATISFIES_CONDITION;
            }

            found = strstr(str + i, buf);

            if (!found)
            {
                return compare::NOT_SATISFIES_CONDITION;
            }

            while ((str + i) != found)
            {
                i++;
            }

            i += k;

            i--;
            j--;

            return compare::SATISFIES_CONDITION;
        }
        case query_replace::ANY_SYMBOL_IN_INTERVAL:
        {
            int n;
            int m;

            j++;
            n = s[j];
            j += 2;
            m = s[j];
            j += 1;

            if ((int)str[i] >= n && (int)str[i] <= m)
            {
                return compare::SATISFIES_CONDITION;
            }
            else
            {
                return compare::NOT_SATISFIES_CONDITION;
            }
        }
        case query_replace::ANY_SYMBOL_NOT_IN_INTERVAL:
        {
            int n;
            int m;

            j += 2;
            n = s[j];
            j += 2;
            m = s[j];
            j += 1;

            if ((int)str[i] < (int)n || (int)str[i] > (int)m)
            {
                return compare::SATISFIES_CONDITION;
            }
            else
            {
                return compare::NOT_SATISFIES_CONDITION;
            }
        }
        default:
            return compare::NOT_SATISFIES_CONDITION;
    }
}


compare query::applyFindAllWords_1(char *str, char *buf_s, char *buf_str)
{
    int i = 0;
    int j = 0;
    int i_str = 0;
    int j_s = 0;
    char tmp[LEN];
    compare res = compare::SATISFIES_CONDITION;


    while (str[i] != '\0' && s[j] != '\0')
    {
        while (str[i] != '\0' && table_t[(int)str[i]] == 1)
        {
            i++;
        }

        while (s[j] != '\0' && table_t[(int)s[j]] == 1)
        {
            j++;
        }

        if (str[i] == '\0' || s[j] == '\0')
        {
            return res;
        }

        i_str = 0;
        j_s = 0;

        while (str[i] != '\0' && table_t[(int)str[i]] == 0)
        {
            buf_str[i_str] = str[i];
            i_str++;
            i++;
        }

        while (s[j] != '\0' && table_t[(int)s[j]] == 0)
        {
            buf_s[j_s] = s[j];
            j_s++;
            j++;
        }

        buf_str[i_str] = '\0';
        buf_s[j_s] = '\0';

        if (applyFindOneWord(buf_str, buf_s, tmp) == compare::NOT_SATISFIES_CONDITION)
        {
            return compare::NOT_SATISFIES_CONDITION;
        }

        if ((str[i] == '\0' && table_t[(int)s[j]] == 1) || (s[j] == '\0' && table_t[(int)str[i]] == 1) || (str[i] == '\0' && s[j] == '\0'))
        {
            return compare::SATISFIES_CONDITION;
        }
    }

    return res;
}



compare query::applyFindAllWords_2(char *str)
{
    int i = 0;
    int j = 0;
    compare res = compare::SATISFIES_CONDITION;
    compare check = compare::NOT_SATISFIES_CONDITION;
    compare make;


    while (str[i] != '\0' && s[j] != '\0')
    {
        while (str[i] != '\0' && table_t[(int)str[i]] == 1)
        {
            i++;
        }

        while (s[j] != '\0' && table_t[(int)s[j]] == 1)
        {
            j++;
        }

        if (str[i] == '\0' || s[j] == '\0')
        {
            return res;
        }

        while (str[i] != '\0' && s[j] != '\0' && table_t[(int)str[i]] == 0 && table_t[(int)s[j]] == 0)
        {
            if (s[j] == '\\')
            {
                j++;
            }
            else
            {
                check = checkReplace(replace, s[j]);
            }

            if (check == compare::SATISFIES_CONDITION)
            {
                make = makeReplace(replace, str, s, i, j);
                check = compare::NOT_SATISFIES_CONDITION;

                if (make == compare::NOT_SATISFIES_CONDITION)
                {
                    return compare::NOT_SATISFIES_CONDITION;
                }

                j++;
                i++;

                continue;
            }

            if (str[i] != s[j])
            {
                return compare::NOT_SATISFIES_CONDITION;
            }

            i++;
            j++;
        }

        if (replace == query_replace::NONE_OR_MORE_SYMBOLS)
        {
            while (s[j] != '\0' && s[j] == '%')
            {
                j++;
            }
        }

        if ((str[i] == '\0' && table_t[(int)s[j]] == 1) || (s[j] == '\0' && table_t[(int)str[i]] == 1) || (str[i] == '\0' && s[j] == '\0'))
        {
            return compare::SATISFIES_CONDITION;
        }
        else if (table_t[(int)str[i]] == 1 && table_t[(int)s[j]] == 1)
        {
            continue;
        }
        else
        {
            return compare::NOT_SATISFIES_CONDITION;
        }
    }

    return res;
}


int query::processQuery(char *a_fname, char *b_fname)
{
    FILE *fa;
    FILE *fb;
    char buf[LEN];
    char tmp1[LEN];
    char tmp2[LEN];
    int res = 0;

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
        for (int i = 0; buf[i] != '\0'; i++)
        {
            if (buf[i] == '\n')
            {
                buf[i] = '\0';
                break;
            }
        }

        switch (num_of_words)
        {
            case query_num_of_words::ONE_WORD:
                if (applyFindOneWord(buf, s, tmp1) == compare::SATISFIES_CONDITION)
                {
                    res++;
                    fprintf(fb, "%s\n", buf);
                }
                break;
            case query_num_of_words::ALL_WORDS:
                if (replace == query_replace::NONE_OR_MORE_SYMBOLS)
                {
                    if (applyFindAllWords_1(buf, tmp1, tmp2) == compare::SATISFIES_CONDITION)
                    {
                        res++;
                        fprintf(fb, "%s\n", buf);
                    }
                    break;
                }
                else
                {
                    if (applyFindAllWords_2(buf) == compare::SATISFIES_CONDITION)
                    {
                        res++;
                        fprintf(fb, "%s\n", buf);
                    }
                    break;
                }
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
