#include"query.h"


int main(int argc, char *argv[])
{
    int task = 1;
    time_t time;
    int res;
    query q;
    char *s;
    char *t;
    char *x;

    if (argc != 5)
    {
        printf("Usage %s [input.txt] [output.txt] s t\n", argv[0]);
        return -1;
    }

    s = argv[3];
    t = argv[4];
    x = nullptr;

    time = clock();

    if (q.parse(task, s, t, x) != query::SUCCESS)
    {
        return query::PARSE_ERROR;
    }

    res = q.processQuery(argv[1], argv[2]);

    time = clock() - time;

    if (res < 0)
    {
        switch(res)
        {
            case query::OPEN_ERROR:
                printf("Can not open file!\n");
                break;
            case query::MEMORY_ERROR:
                printf("Can not allocate memory!\n");
                break;
            case query::READ_ERROR:
                printf("Can not read an element!\n");
                break;
            default:
                printf("Unknown error!\n");

        }

        return query::ERROR;
    }

    printf ("%s : Task = %d Result = %d Elapsed = %.2f\n", argv[0], task, res, (double)time / CLOCKS_PER_SEC);

    return query::SUCCESS;
}
