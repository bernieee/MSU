#ifndef list2_H
#define list2_H
#include "list2_node.h"
#include "command.h"

template <class T>
class list2
{
    private:
        list2_node<T> *head = nullptr;

    public:
        list2() = default;
        ~list2()
        {
            del();
        }

        read_status read(FILE *f)
        {
            read_status res;
            int i;
            list2_node<T> *end;
            list2_node<T> tmp;

            head = new list2_node<T>();

            if ((res = head->read(f)) != read_status::success)
            {
                return read_status::read;
            }

            head->next = nullptr;
            head->prev = nullptr;
            end = head;

            while (((res = tmp.read(f)) == read_status::success)) //TODO ????
            {
                list2_node<T> *curr = new list2_node<T>((list2_node<T> &&) tmp);

                curr->next = nullptr;
                curr->prev = end;
                end->next = curr;
                end = curr;
                i++;
            }

            if (feof(f))
            {
                return read_status::success;
            }

            if (res != read_status::success)
            {
                return res;
            }

            return read_status::success;
        }


        void del()
        {
            list2_node<T> *curr;
            list2_node<T> *next;

            for(curr = head; curr; curr = next)
            {
                next = curr->next;

                //curr->remove();
                delete curr;
            }
        }


        int processCommand(command *x)
        {
            list2_node<T> *curr;
            int res = 0;

            for (curr = head; curr; curr = curr->next)
            {
                if (x->apply(*curr)) // TODO
                {
                    res++;
                    printf("%s %d %d\n", curr->get_name(), curr->get_phone(), curr->get_group());
                }
            }

            return res;
        }
};

#endif
