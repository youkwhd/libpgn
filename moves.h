#ifndef __LIBPGN_MOVES_H
#define __LIBPGN_MOVES_H

#include "piece.h"
#include "coordinate.h"
#include "annotation.h"
#include "check.h"

#include "utils/export.h"

#include <stdlib.h>
#include <stdbool.h>

/* TODO: move this somewhere
 */
#define PGN_CASTLING_NONE 0
#define PGN_CASTLING_KINGSIDE 2
#define PGN_CASTLING_QUEENSIDE 3

#define PGN_MOVES_INITIAL_SIZE 32
#define PGN_MOVES_GROW_SIZE 32

#define __PGN_MOVE_NOTATION_SIZE 16

#define PGN_ALTERNATIVE_MOVES_INITIAL_SIZE 1
#define PGN_ALTERNATIVE_MOVES_GROW_SIZE 1

typedef struct pgn_moves_t pgn_moves_t;
typedef struct __pgn_moves_item_t __pgn_moves_item_t;

typedef struct pgn_alternative_moves_t {
    pgn_moves_t **values;
    size_t length;
    size_t size;
} pgn_alternative_moves_t;

typedef struct pgn_move_t {
    pgn_piece_t piece, promoted_to;
    char notation[__PGN_MOVE_NOTATION_SIZE];
    int castles;
    bool captures;
    bool en_passant;
    pgn_check_t check;
    pgn_coordinate_t from, dest;
    pgn_annotation_t annotation;
    pgn_alternative_moves_t *alternatives;
} pgn_move_t;

struct __pgn_moves_item_t {
    pgn_move_t white;
    pgn_move_t black;
};

struct pgn_moves_t {
    __pgn_moves_item_t *values;
    size_t length;
    size_t size;
};

pgn_move_t __pgn_move_from_string(char *str, size_t *consumed);
pgn_move_t pgn_move_from_string(char *str);

pgn_moves_t *__pgn_moves_from_string(char *str, size_t *consumed);
pgn_moves_t *pgn_moves_from_string(char *str);

pgn_alternative_moves_t *pgn_alternative_moves_init(void);
void pgn_alternative_moves_push(pgn_alternative_moves_t *alt, pgn_moves_t *moves);
void pgn_alternative_moves_cleanup(pgn_alternative_moves_t *alt);

PGN_EXPORT pgn_moves_t *pgn_moves_init(void);
PGN_EXPORT void pgn_moves_push(pgn_moves_t *moves, __pgn_moves_item_t __moves);
PGN_EXPORT void pgn_moves_cleanup(pgn_moves_t *moves);

#endif // __LIBPGN_MOVES_H
