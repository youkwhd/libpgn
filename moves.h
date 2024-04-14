#ifndef __LIBPGN_MOVES_H
#define __LIBPGN_MOVES_H

#include "piece.h"
#include "coordinate.h"
#include "annotation.h"

#include <stdlib.h>
#include <stdbool.h>

#define PGN_MOVES_INITIAL_SIZE 32
#define PGN_MOVES_GROW_SIZE 32

typedef struct pgn_move_t {
    pgn_piece_t piece;
    bool captures;
    pgn_coordinate_t to;
    pgn_annotation_t annotation;
} pgn_move_t;

typedef struct pgn_moves_t {
    pgn_move_t *values;
    size_t length;
    size_t size;
} pgn_moves_t;

pgn_moves_t *pgn_moves_init();
void pgn_moves_push(pgn_moves_t *moves, pgn_move_t move);
void pgn_moves_cleanup(pgn_moves_t *moves);

#endif // __LIBPGN_MOVES_H
