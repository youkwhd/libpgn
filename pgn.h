#ifndef __LIBPGN_PGN_H
#define __LIBPGN_PGN_H

#include <stdio.h>
#include <stdlib.h>

#include "table.h"
#include "string.h"
#include "piece.h"
#include "annotation.h"
#include "coordinate.h"
#include "moves.h"

#define PGN_UNUSED(x) ((void)x)
#define PGN_NOT_IMPLEMENTED() \
    do { \
        fprintf(stderr, "libpgn: function `%s` is not implemented yet, at %s:%d\n", __func__, __FILE__, __LINE__); \
        exit(EXIT_FAILURE); \
    } while (0)

typedef struct pgn_t {
    pgn_table_t *metadata;
    pgn_moves_t moves;
} pgn_t;

pgn_t *pgn_init();
void pgn_cleanup(pgn_t *pgn);
void pgn_parse_from_file(pgn_t *pgn, FILE *file);
void pgn_parse_from_string(pgn_t *pgn, char *str);

#endif // __LIBPGN_PGN_H
