#ifndef __LIBPGN_PGN_H
#define __LIBPGN_PGN_H

#include <stdio.h>
#include <stdlib.h>

#include "table.h"
#include "string.h"
#include "piece.h"
#include "annotation.h"
#include "coordinate.h"
#include "score.h"
#include "moves.h"

#define PGN_UNUSED(x) ((void)x)
#define PGN_NOT_IMPLEMENTED() \
    do { \
        fprintf(stderr, "libpgn: function `%s` is not implemented yet, at %s:%d\n", __func__, __FILE__, __LINE__); \
        exit(EXIT_FAILURE); \
    } while (0)

typedef struct pgn_t {
    pgn_table_t *metadata;
    pgn_moves_t *moves;
    pgn_score_t score;
} pgn_t;

pgn_t *pgn_init();
void pgn_cleanup(pgn_t *pgn);
void pgn_parse(pgn_t *pgn, char *str);

#define pgn_parse_metadata(str) pgn_table_from_string(str)
#define pgn_parse_moves(str) pgn_moves_from_string(str)

#endif // __LIBPGN_PGN_H
