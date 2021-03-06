#include"command.h"
#include"list2.h"
#define LEN 1234


int main(int argc, char *argv[])
{
    time_t time;
    int res = 0;
    read_status read_res;
    char buf[LEN];
    FILE *fa;

    if (argc != 2)
    {
        printf("Usage %s [input.txt]\n", argv[0]);
        return -1;
    }

    if (!(fa = fopen(argv[1], "r")))
    {
        printf("Can not open input file!\n");
        return -1;
    }

    list2<record> *head = new list2<record>;
    read_res = head->read(fa);

    if (read_res != read_status::success)
    {
        switch(read_res)
        {
            case read_status::eof:
                printf("End of file!\n");
                break;
            case read_status::memory:
                printf("Can not allocate memory!\n");
                break;
            case read_status::read:
                printf("Can not read an element!\n");
                break;
            case read_status::format:
                printf("Wrong input format!\n");
                break;
            default:
                printf("Unknown error!\n");

        }

        fclose(fa);
        delete head;
        return -1;
    }

    time = clock();

    while (fgets(buf, LEN, stdin))
    {
        command *x = new command;

        for (int i = 0; buf[i] != '\0'; i++)
        {
            if (buf[i] == '\n')
            {
                buf[i] = '\0';
                break;
            }
        }

        read_res = x->parse(buf);

        if (read_res != read_status::success)
        {
            switch(read_res)
            {
                case read_status::eof:
                    printf("End of file!\n");
                    break;
                case read_status::memory:
                    printf("Can not allocate memory!\n");
                    break;
                case read_status::read:
                    printf("Can not read an element!\n");
                    break;
                case read_status::format:
                    printf("Wrong input format!\n");
                    break;
                default:
                    printf("Unknown error!\n");
            }

            fclose(fa);
            delete head;
            delete x;
            return -1;
        }

        res += head->processCommand(x);
        delete x;
    }

    time = clock() - time;

    printf("%s : Result = %d Elapsed = %.2f\n", argv[0], res, (double)time / CLOCKS_PER_SEC);

    fclose(fa);
    delete head;
    return 0;
}
