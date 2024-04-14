#ifndef __LIBPGN_MOVES_H
#define __LIBPGN_MOVES_H

#include "piece.h"
#include "coordinate.h"
#include "annotation.h"

#include <stdbool.h>

typedef struct pgn_move_t {
    pgn_piece_t piece;
    bool captured;
    pgn_coordinate_t to;
    pgn_annotation_t annotation;
} pgn_move_t;

#endif // __LIBPGN_MOVES_H
