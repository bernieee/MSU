# ifndef command_H
# define command_H
# include <stdio.h>
# include "record.h"

class command : public record
{
    private:
        condition c_name = condition::none;
        condition c_phone = condition::none;
        condition c_group = condition::none;
    public:
        command() = default;
        ~command() = default;
        // Convert string command to data structure
        // Example 1: "phone = 1234567" parsed to
        // (command::phone = 1234567, command::c_phone = condition::eq)
        // other fields are unspecified
        // Example 2: "name like St%" parsed to
        // (command::name = "St%", command::c_name = condition::like)
        // other fields are unspecified
        read_status parse (char *string);
        condition checkOperation(char *x);
        field checkField(char *x);
        symbol_replace checkReplace(int j);
        bool makeReplace(symbol_replace replace, char *str, int &i, int &j);
        int readNumber(char *x, int n);
        // Print parsed structure
        void print (FILE *fp = stdout) const; // TODO
        // Apply command, return comparision result for record ’x’
        bool apply (record& x);
        bool applyReplace(record &x);
        bool applyCompare(record &x);
    };

# endif
