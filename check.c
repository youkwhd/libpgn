#include <assert.h>

#include "check.h"

pgn_check_t __pgn_check_from_string(char *str, size_t *consumed)
{
    size_t cursor = 0;
    pgn_check_t check = PGN_CHECK_NONE;

    while (str[cursor] == '+') {
        check++;
        cursor++;
    }
    assert(check <= 2);

    if (str[cursor] == '#') {
        assert(check == PGN_CHECK_NONE);
        check = PGN_CHECK_MATE;
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
