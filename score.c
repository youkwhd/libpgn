#include "score.h"

#include <assert.h>
#include <string.h>

typedef enum pgn_score_single_t {
    ZERO = 0,
    ONE,
    HALF,
} pgn_score_single_t;

/* only parses the score one sided
 */
pgn_score_single_t __pgn_score_single_from_string(char *str, size_t *consumed)
{
    if (strncmp(str, "1/2", 3) == 0) {
        *consumed += 3;
        return HALF;
    } else if (*str == '0') {
        *consumed += 1;
        return ZERO;
    } else if (*str == '1') {
        *consumed += 1;
        return ONE;
    }

    return -1;
}

pgn_score_t __pgn_score_from_string(char *str, size_t *consumed)
{
    size_t cursor = 0;

    if (str[cursor] == '*') {
        cursor++;
        *consumed += cursor;
        return PGN_SCORE_ONGOING;
    }

    pgn_score_single_t white = __pgn_score_single_from_string(str + cursor, &cursor);
    if ((int)white == -1) return PGN_SCORE_UNKNOWN;

    if (str[cursor++] != '-') return PGN_SCORE_UNKNOWN;

    pgn_score_single_t black = __pgn_score_single_from_string(str + cursor, &cursor);
    if ((int)black == -1) return PGN_SCORE_UNKNOWN;

    *consumed += cursor;

    if (white == HALF && black == HALF)   return PGN_SCORE_DRAW;
    else if (white == 1 && black == 0)    return PGN_SCORE_WHITE_WON;
    else if (white == 0 && black == 1)    return PGN_SCORE_BLACK_WON;
    else if (white == 0 && black == 0)    return PGN_SCORE_FORFEIT;
    else if (white == 0 && black == HALF) return PGN_SCORE_WHITE_FORFEIT;
    else if (white == HALF && black == 0) return PGN_SCORE_BLACK_FORFEIT;
    else                                  return PGN_SCORE_UNKNOWN;
}

pgn_score_t pgn_score_from_string(char *str)
{
    size_t consumed = 0;
    return __pgn_score_from_string(str, &consumed);
}
