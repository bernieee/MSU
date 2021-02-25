#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

enum class query_replace
{
    NONE,
    ONE_SYMBOL,
    NONE_OR_MORE_SYMBOLS,
    ANY_SYMBOL_IN_INTERVAL,
    ANY_SYMBOL_NOT_IN_INTERVAL,
};

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
        query_replace replace = query_replace::NONE;
        char *s = nullptr;
        char *t = nullptr;

    public:
        enum ERRORS
        {
            SUCCESS=0,
            ERROR=-1,
            OPEN_ERROR=-2,
            READ_ERROR=-3,
            MEMORY_ERROR=-4,
            PARSE_ERROR=-5,
            TYPE_ERROR=-6,
        };

        query() = default;
        ~query();
        int parse(int task_num, char *s_new, char *t_new);
        int readNumber(int &j, int &count);
        compare checkCompare(int cmp, query_operation operation);
        compare checkReplace(query_replace replace, int j);
        compare makeReplace(query_replace replace, char *str, int &i, int &j);
        compare applyFindOneWord(char *str, char *buf);
        compare applyFindAllWords(char *str);
        int processQuery(char *a_fname, char *b_fname);
};
