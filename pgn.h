#ifndef __LIBPGN_PGN_H
#define __LIBPGN_PGN_H

#include <stdio.h>
#include <stdlib.h>

#include "metadata.h"
#include "piece.h"
#include "annotation.h"
#include "coordinate.h"
#include "score.h"
#include "check.h"
#include "moves.h"

#include "utils/export.h"

#define PGN_UNUSED(x) ((void)x)
#define PGN_NOT_IMPLEMENTED()                                                                                      \
    do {                                                                                                           \
        fprintf(stderr, "libpgn: function `%s` is not implemented yet, at %s:%d\n", __func__, __FILE__, __LINE__); \
        exit(EXIT_FAILURE);                                                                                        \
    } while (0)

typedef struct pgn_t {
    pgn_metadata_t *metadata;
    pgn_moves_t *moves;
    pgn_score_t score;
} pgn_t;

PGN_EXPORT pgn_t *pgn_init(void);
PGN_EXPORT void pgn_cleanup(pgn_t *pgn);

PGN_EXPORT pgn_metadata_t *pgn_parse_metadata(char *str);
PGN_EXPORT pgn_move_t pgn_parse_move(char *str);
PGN_EXPORT pgn_moves_t *pgn_parse_moves(char *str);
PGN_EXPORT pgn_score_t pgn_parse_score(char *str);

PGN_EXPORT size_t pgn_parse(pgn_t *pgn, char *str);

#endif // __LIBPGN_PGN_H
