#ifndef __LIBPGN_MOVES_H
#define __LIBPGN_MOVES_H

#include "piece.h"
#include "coordinate.h"
#include "annotation.h"
#include "check.h"

#include <stdlib.h>
#include <stdbool.h>

/* TODO: move this somewhere
 */
#define PGN_CASTLING_NONE 0
#define PGN_CASTLING_KINGSIDE 2
#define PGN_CASTLING_QUEENSIDE 3

#define PGN_MOVES_INITIAL_SIZE 32
#define PGN_MOVES_GROW_SIZE 32

typedef struct pgn_move_t {
    pgn_piece_t piece, promoted_to;
    unsigned int nth_best;
    int castles;
    bool captures;
    pgn_check_t check;
    pgn_coordinate_t from, dest;
    pgn_annotation_t annotation;
} pgn_move_t;

#define PGN_MOVES_ALTERNATIVES_INITIAL_SIZE 6

typedef struct pgn_moves_t pgn_moves_t;
typedef struct __pgn_moves_item_t __pgn_moves_item_t;

struct __pgn_moves_item_t {
    pgn_move_t white;
    pgn_move_t black;
    pgn_moves_t *alternatives;
};

struct pgn_moves_t {
    __pgn_moves_item_t **values;
    size_t length;
    size_t size;
};

pgn_move_t __pgn_move_from_string(char *str, size_t *consumed);
pgn_move_t pgn_move_from_string(char *str);

pgn_moves_t *__pgn_moves_from_string(char *str, size_t *consumed, bool parsing_for_alternatives);
pgn_moves_t *pgn_moves_from_string(char *str);

/* __pgn_moves_t *__pgn_moves_init(); */
/* void __pgn_moves_cleanup(__pgn_moves_t *__moves); */

pgn_moves_t *pgn_moves_init();
void pgn_moves_push(pgn_moves_t *moves, __pgn_moves_item_t *__moves);
void pgn_moves_cleanup(pgn_moves_t *moves);

#endif // __LIBPGN_MOVES_H
