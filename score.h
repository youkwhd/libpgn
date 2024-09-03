#ifndef __LIBPGN_SCORE_H
#define __LIBPGN_SCORE_H

#include <stdint.h>
#include <stdlib.h>

typedef enum pgn_score_t {
    PGN_SCORE_UNKNOWN = 0,
    PGN_SCORE_ONGOING, // From wikipedia: Recorded as White score, dash, then Black score, or * (other, e.g., the game is ongoing).
    PGN_SCORE_DRAW,
    PGN_SCORE_WHITE_WON,
    PGN_SCORE_BLACK_WON,
    PGN_SCORE_FORFEIT,
    PGN_SCORE_WHITE_FORFEIT,
    PGN_SCORE_BLACK_FORFEIT,
} pgn_score_t;

pgn_score_t __pgn_score_from_string(char *str, size_t *consumed);
pgn_score_t pgn_score_from_string(char *str);

#endif // __LIBPGN_SCORE_H
