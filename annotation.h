#ifndef __LIBPGN_ANNOTATION_H
#define __LIBPGN_ANNOTATION_H

#include "export.h"
#include <stdlib.h>

typedef enum pgn_annotation_t {
    PGN_ANNOTATION_NONE = 0,
    PGN_ANNOTATION_CHECKMATE,
    PGN_ANNOTATION_GOOD_MOVE,
    PGN_ANNOTATION_EXCELLENT_MOVE,
    PGN_ANNOTATION_INTRESTING_MOVE,
    PGN_ANNOTATION_DUBIOUS_MOVE,
    PGN_ANNOTATION_MISTAKE,
    PGN_ANNOTATION_BLUNDER,
} pgn_annotation_t;

PGN_EXPORT pgn_annotation_t __pgn_annotation_from_string(char *str, size_t *consumed);
PGN_EXPORT pgn_annotation_t pgn_annotation_from_string(char *str);

#endif // __LIBPGN_ANNOTATION_H
