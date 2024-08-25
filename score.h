#ifndef __LIBPGN_SCORE_H
#define __LIBPGN_SCORE_H

#include <stdint.h>
#include <stdlib.h>

typedef struct pgn_score_t {
    uint8_t white, black;
} pgn_score_t;

pgn_score_t __pgn_score_from_string(char *str, size_t *consumed);
pgn_score_t pgn_score_from_string(char *str);

#endif // __LIBPGN_SCORE_H
