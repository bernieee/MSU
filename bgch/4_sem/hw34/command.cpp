#include "command.h"
#define LEN 1234


read_status command::parse(char *string)
{
    int i = 0;
    field which_field = field::none;
    int space_field = 0;
    int space_op = 0;
    int space = 0;

    while (string[i] != '\0')
    {
        if (string[i] == ' ')
        {
            if (space == 0)
            {
                string[i] = '\0';
                which_field = checkField(string);
                space_field = i;
                string[i] = ' ';
            }

            if (space == 1)
            {
                condition res;
                int n;

                space_op = i;

                if (string + space_op + 1)
                {
                    string[i] = '\0';
                    n = strlen(string + space_op + 1);
                    res = checkOperation(string + space_field + 1);
                    string[i] = ' ';
                }
                else
                {
                    return read_status::format;
                }

                switch (which_field)
                {
                    case field::name:
                    {
                        c_name = res;
                        this->init(string + space_op + 1, 0, 0);

                        return read_status::success;
                    }
                    case field::phone:
                    {
                        if (res == condition::like)
                        {
                            return read_status::format;
                        }

                        c_phone = res;
                        int p = readNumber(string + space_op + 1, n);
                        this->init(nullptr, p, 0);

                        return read_status::success;
                    }
                    case field::group:
                    {
                        if (res == condition::like)
                        {
                            return read_status::format;
                        }

                        c_group = res;
                        int g = readNumber(string + space_op + 1, n);
                        this->init(nullptr, 0, g);

                        return read_status::success;
                    }
                    default:
                        return read_status::format;
                }

                break;
            }

            space++;
        }

        i++;
    }

    return read_status::success;
}


int command::readNumber(char *x, int n)
{
    int dec = 1;
    int num = 0;

    for (int i = 1; i < n; i++)
    {
        dec *= 10;
    }

    for (int i = 0; i < n; i++)
    {
        num += ((int)x[i] - 48) * dec;
        dec /= 10;
    }

    return num;
}


field command::checkField(char *x)
{
    if (strcmp(x, "name") == 0)
        return field::name;
    if (strcmp(x, "phone") == 0)
        return field::phone;
    if (strcmp(x, "group") == 0)
        return field::group;
    return field::none;
}


condition command::checkOperation(char *x)
{
    if (strcmp(x, "<") == 0)
        return condition::lt;
    if (strcmp(x, ">") == 0)
        return condition::gt;
    if (strcmp(x, "<=") == 0)
        return condition::le;
    if (strcmp(x, ">=") == 0)
        return condition::ge;
    if (strcmp(x, "=") == 0)
        return condition::eq;
    if (strcmp(x, "<>") == 0)
        return condition::ne;
    if (strcmp(x, "like") == 0)
        return condition::like;
    return condition::none;
}


symbol_replace command::checkReplace(int j)
{
    char *y_name = this->get_name();
    if (y_name[j] == '_')
        return symbol_replace::one_symbol;
    if (y_name[j] == '%')
        return symbol_replace::none_or_more_symbols;
    if (y_name[j] == '[' && y_name[j + 1] == '^')
        return symbol_replace::any_symbol_not_in_interval;
    if (y_name[j] == '[')
        return symbol_replace::any_symbol_in_interval;
    return symbol_replace::none;
}


bool command::makeReplace(symbol_replace replace, char *str, int &i, int &j)
{
    char *y_name = this->get_name();

    switch (replace)
    {
        case symbol_replace::one_symbol:
        {
            return true;
        }
        case symbol_replace::none_or_more_symbols:
        {
            char buf[LEN];
            int k = 0;
            char *found;

            while (y_name[j] != '\0' && y_name[j] == '%')
            {
                j++;
            }

            while (y_name[j] != '\0' && checkReplace(j) == symbol_replace::none) // TODO
            {
                if (y_name[j] == '\\')
                {
                    j++;
                }

                buf[k] = y_name[j];
                k++;
                j++;
            }

            buf[k] = '\0';

            if ((y_name[j] == '\0') && k == 0)
            {
                while (str[i] != '\0')
                {
                    i++;
                }

                i--;
                j--;

                return true;
            }

            if ((y_name[j] == '\0') && k != 0)
            {
                while ((found = strstr(str + i, buf)))
                {
                    while (str + i != found)
                    {
                        i++;
                    }

                    i += k;
                }

                i--;
                j--;

                return true;
            }

            found = strstr(str + i, buf);

            if (!found)
            {
                return false;
            }

            while ((str + i) != found)
            {
                i++;
            }

            i += k - 1;

            i--;
            j--;

            return true;
        }
        case symbol_replace::any_symbol_in_interval:
        {
            int n;
            int m;

            j++;
            n = y_name[j];
            j += 2;
            m = y_name[j];
            j += 1;

            if ((int)str[i] >= n && (int)str[i] <= m)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        case symbol_replace::any_symbol_not_in_interval:
        {
            int n;
            int m;

            j += 2;
            n = y_name[j];
            j += 2;
            m = y_name[j];
            j += 1;

            if ((int)str[i] < (int)n || (int)str[i] > (int)m)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        default:
            return false;
    }
}


bool command::applyReplace(record &x)
{
    int cmp;
    symbol_replace check = symbol_replace::none;
    bool make;
    int j = 0;
    int k = 0;
    char *x_name = x.get_name();
    char *y_name = this->get_name();

    while (x_name[k] != '\0' && y_name[j] != '\0')
    {
        if (y_name[j] == '\\')
        {
            j++;
        }
        else
        {
            check = checkReplace(j);
        }

        if (check != symbol_replace::none)
        {
            make = makeReplace(check, x_name, k, j);
            check = symbol_replace::none;

            if (!make)
            {
                cmp = -1;
                break;
            }

            k++;
            j++;
            continue;
        }

        if (x_name[k] != y_name[j])
        {
            cmp = -1;
            break;
        }

        k++;
        j++;
    }

    if (x_name[k] == '\0' && y_name[j] == '\0')
    {
        cmp = 0;
    }
    else
    {
        cmp = -1;
    }

    return (cmp == 0);
}


bool command::applyCompare(record &x)
{
    if (c_name != condition::none)
    {
        return x.compare_name(c_name, *this);
    }

    if (c_phone != condition::none)
    {
        return x.compare_phone(c_phone, *this);
    }

    if (c_group != condition::none)
    {
        return x.compare_group(c_group, *this);
    }

    return false;
}


bool command::apply(record& x)
{
    if (c_name == condition::like)
    {
        return applyReplace(x);
    }
    else
    {
        return applyCompare(x);
    }
}


// Print parsed structure
//void command::print(FILE *fp = stdout) const;




