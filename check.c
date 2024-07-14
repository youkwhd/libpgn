#include <assert.h>

#include "check.h"

pgn_check_t __pgn_check_from_string(char *str, size_t *consumed)
{
    int cursor = 0;
    pgn_check_t check = PGN_CHECK_NONE;

    while (str[cursor] == '+') {
        assert(check < 2);
        check++;
        cursor++;
    }

    *consumed += cursor;
    return check;
}

pgn_check_t pgn_check_from_string(char *str)
{
    size_t consumed = 0;
    return __pgn_check_from_string(str, &consumed);
}
