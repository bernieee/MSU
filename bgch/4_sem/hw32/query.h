#include<stdio.h>
#include<string.h>
#include<time.h>

enum class query_type
{
    NONE,
    FIND,
    REPLACE,
};

enum class query_num_of_words
{
    NONE,
    ONE_WORD,
    ALL_WORDS,
};

enum class query_operation
{
    NONE,
    EQUAL,
    NOT_EQUAL,
    LESS,
    LESS_OR_EQUAL,
    MORE,
    MORE_OR_EQUAL,
};

enum class compare
{
    NOT_SATISFIES_CONDITION,
    SATISFIES_CONDITION,
};

class query
{
    private:
        query_type type = query_type::NONE;
        query_num_of_words num_of_words = query_num_of_words::NONE;
        query_operation operation = query_operation::NONE;
        char *s = nullptr;
        char *t = nullptr;
        char *x = nullptr;

    public:
        enum ERRORS
        {
            SUCCESS,
            ERROR,
            OPEN_ERROR,
            READ_ERROR,
            MEMORY_ERROR,
            PARSE_ERROR,
            TYPE_ERROR,
        };

        query() = default;
        ~query();
        int parse(int task_num, char *s_new, char *t_new, char *x_new);
        query_operation checkOperation(char *x);
        compare checkCompare(int cmp, query_operation operation);
        compare applyFind(char *str, char *buf);
        int applyReplace(char *str, char *buf, FILE *f);
        int processQuery(char *a_fname, char *b_fname);
};
