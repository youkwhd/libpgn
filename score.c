#include "score.h"

#include <assert.h>
#include <ctype.h>

pgn_score_t __pgn_score_from_string(char *str, size_t *consumed)
{
    pgn_score_t score = {
        .white = 0,
        .black = 0,
    };

    size_t cursor = 0;

    if (str[cursor] == '*') {
        cursor++;
    } else if (str[cursor] == '1' && str[cursor + 1] == '/') {
        assert(str[cursor++] == '1');
        assert(str[cursor++] == '/');
        assert(str[cursor++] == '2');
        assert(str[cursor++] == '-');
        assert(str[cursor++] == '1');
        assert(str[cursor++] == '/');
        assert(str[cursor++] == '2');
    } else if (isdigit(str[cursor])) {
        /* TODO: this does not have the capability
         * to parse multiple digit.
         */
        score.white = str[cursor++] - '0';
        assert(str[cursor++] == '-');
        score.black = str[cursor++] - '0';
    }

    *consumed += cursor;
    return score;
}

pgn_score_t pgn_score_from_string(char *str)
{
    size_t consumed = 0;
    return __pgn_score_from_string(str, &consumed);
}
