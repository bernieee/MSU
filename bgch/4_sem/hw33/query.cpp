#include "query.h"
#define LEN 1234

query::~query()
{
    if (s)
        delete [] s;
    if (t)
        delete [] t;
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

    s[s_len] = '\0';
    t[t_len] = '\0';

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


compare query::applyFindOneWord(char *str, char *buf)
{
    int n = strlen(str);
    int count = 0;
    int cmp;
    compare res = compare::NOT_SATISFIES_CONDITION;
    compare check = compare::NOT_SATISFIES_CONDITION;
    compare make;

    for (int i = 0; i < n; i++)
    {
        if (strchr(t, str[i]))
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
                        check = checkReplace(replace, j);
                    }

                    if (check == compare::SATISFIES_CONDITION)
                    {
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

        while (buf[k] != '\0' && s[j] != '\0')
        {
            if (s[j] == '\\')
            {
                j++;
            }
            else
            {
                check = checkReplace(replace, j);
            }

            if (check == compare::SATISFIES_CONDITION)
            {
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

    return res;
}


/*compare query::applyFindOneWord(char *str)
{
    int n = strlen(str);
    char *buf;
    int count = 0;
    int cmp;
    char *found;
    compare res = compare::NOT_SATISFIES_CONDITION;
    compare check = compare::NOT_SATISFIES_CONDITION;
    compare make;

    buf = new char[n + 1];

    for (int i = 0; i < n; i++)
    {
        if (strchr(t, str[i]))
        {
            if (count != 0)
            {
                int j = 0;
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

                    //printf("buf = %s  s = %s\n", buf, s + j);

                    while (buf[k] != '\0' && s[j] != '\0' && !(found = strchr(t, s[j])))
                    {
                        //printf("    buf[k] = %c s[j] = %c\n", buf[k], s[j]);
                        if (s[j] == '\\')
                        {
                            j++;
                        }
                        else
                        {
                            check = checkReplace(replace, j);
                        }

                        if (check == compare::SATISFIES_CONDITION)
                        {
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

                    found = strchr(t, s[j]);

                    if ((buf[k] == '\0' && found) || (buf[k] == '\0' && s[j] == '\0'))
                    {
                        cmp = 0;
                    }
                    else
                    {
                        cmp = -1;
                    }

                    while (s[j] != '\0' && !strchr(t, s[j]))
                    {
                        j++;
                    }

                    res = checkCompare(cmp, operation);

                    if (res == compare::SATISFIES_CONDITION)
                    {
                        //printf("        buf = %s s = %s\n", buf, s);
                        delete [] buf;
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

            while (s[j] != '\0' && strchr(t, s[j]))
            {
                j++;
            }

            if (s[j] == '\0')
            {
                break;
            }

            //printf("buf = %s  s = %s\n", buf, s + j);

            while (buf[k] != '\0' && s[j] != '\0' && !(found = strchr(t, s[j])))
            {
                //printf("    buf[k] = %c s[j] = %c\n", buf[k], s[j]);
                if (s[j] == '\\')
                {
                    j++;
                }
                else
                {
                    check = checkReplace(replace, j);
                }

                if (check == compare::SATISFIES_CONDITION)
                {
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

            found = strchr(t, s[j]);

            if ((buf[k] == '\0' && found) || (buf[k] == '\0' && s[j] == '\0'))
            {
                cmp = 0;
            }
            else
            {
                cmp = -1;
            }

            while (s[j] != '\0' && !strchr(t, s[j]))
            {
                j++;
            }

            res = checkCompare(cmp, operation);

            if (res == compare::SATISFIES_CONDITION)
            {
                delete [] buf;
                return compare::SATISFIES_CONDITION;
            }
        }
    }

    delete [] buf;
    return res;
}*/


compare query::checkReplace(query_replace replace, int j)
{
    switch (replace)
    {
        case query_replace::ONE_SYMBOL:
            return (compare)(s[j] == '_');
        case query_replace::NONE_OR_MORE_SYMBOLS:
            return (compare)(s[j] == '%');
        case query_replace::ANY_SYMBOL_IN_INTERVAL:
            return (compare)(s[j] == '[');
        case query_replace::ANY_SYMBOL_NOT_IN_INTERVAL:
            return (compare)(s[j] == '[');
        default:
            return compare::NOT_SATISFIES_CONDITION;
    }
}


compare query::makeReplace(query_replace replace, char *str, int &i, int &j)
{
    /*

    abcacbacb

    a%bacb%


    0 -- 48
    9 -- 57

    */

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

            while (s[j] != '\0' && checkReplace(replace, j) == compare::SATISFIES_CONDITION)
            {
                j++;
            }

            while (s[j] != '\0' && checkReplace(replace, j) == compare::NOT_SATISFIES_CONDITION)
            {
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
                    while (str + i != found)
                    {
                        i++;
                    }

                    i += k - 1;
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

            i += k - 1;

            i--;
            j--;

            //TODO
            // идея: взять слово, начиная со следующего элемента строки s и до пробельного/процента, и проверить
            // его вхождение в str -- начало и будет новым значением переменной i
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


compare query::applyFindAllWords(char *str)
{
    int i = 0;
    int j = 0;
    char *found_str;
    char *found_s;
    compare res = compare::SATISFIES_CONDITION;
    compare check = compare::NOT_SATISFIES_CONDITION;
    compare make;


    while (str[i] != '\0' && j < s_len)//s[j] != '\0')
    {
        while (str[i] != '\0' && strchr(t, str[i]))
        {
            i++;
        }

        while (j < s_len && strchr(t, s[j]))
        {
            j++;
        }

        if (str[i] == '\0' || j >= s_len)
        {
            return res;
        }

        while (str[i] != '\0' && s[j] != '\0' && !(strchr(t, str[i])) && !(strchr(t, s[j])))
        {
            if (s[j] == '\\')
            {
                j++;
            }
            else
            {
                check = checkReplace(replace, j);
            }

            if (check == compare::SATISFIES_CONDITION)
            {
                make = makeReplace(replace, str, i, j);
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

        found_str = strchr(t, str[i]);
        found_s = strchr(t, s[j]);

        if (replace == query_replace::NONE_OR_MORE_SYMBOLS)
        {
            if (j < s_len && s[j] == '\0')
            {
                found_s = strchr(t, t[0]);
                j++;
            }
        }

        if ((str[i] == '\0' && found_s) || (s[j] == '\0' && found_str) || (str[i] == '\0' && s[j] == '\0'))
        {
            return compare::SATISFIES_CONDITION;
        }
        else if (found_str && found_s)
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
    char tmp[LEN];
    int res = 0;
    int i;
    int j = 0;
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

    if (replace == query_replace::NONE_OR_MORE_SYMBOLS && num_of_words == query_num_of_words::ALL_WORDS)
    {
        while (j < s_len)
        {
            while (s[j] != '\0' && strchr(t, s[j]))
            {
                j++;
            }

            while (s[j] != '\0' && !(strchr(t, s[j])))
            {
                j++;
            }

            s[j] = '\0';
            j++;
        }
    }

    j = 0;

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

        switch (num_of_words)
        {
            case query_num_of_words::ONE_WORD:
                if (applyFindOneWord(buf, tmp) == compare::SATISFIES_CONDITION)
                {
                    res++;
                    fprintf(fb, "%s\n", buf);
                }
                break;
            case query_num_of_words::ALL_WORDS:
                if (applyFindAllWords(buf) == compare::SATISFIES_CONDITION)
                {
                    res++;
                    fprintf(fb, "%s\n", buf);
                }
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
