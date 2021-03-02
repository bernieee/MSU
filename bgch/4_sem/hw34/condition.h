# ifndef condition_H
# define condition_H

enum class symbol_replace
{
    none,
    one_symbol,
    none_or_more_symbols,
    any_symbol_in_interval,
    any_symbol_not_in_interval,
};


enum class field
{
    none,
    name,
    phone,
    group,
};

enum class condition
{
    none,
    eq,
    ne,
    lt,
    gt,
    le,
    ge,
    like,
};

# endif
