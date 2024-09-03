#ifndef __LIBPGN_ANNOTATION_H
#define __LIBPGN_ANNOTATION_H

#include <stdlib.h>

/* See:
 *   http://www.saremba.de/chessgml/standards/pgn/pgn-complete.htm#c10
 *   https://en.wikipedia.org/wiki/Numeric_Annotation_Glyphs#Standard_NAGs
 */
typedef enum pgn_annotation_t {
    PGN_ANNOTATION_UNKNOWN = -1,    //
    PGN_ANNOTATION_NULL = 0,        //
    PGN_ANNOTATION_GOOD_MOVE,       // !
    PGN_ANNOTATION_MISTAKE,         // ?
    PGN_ANNOTATION_BRILLIANT_MOVE,  // !!
    PGN_ANNOTATION_BLUNDER,         // ??
    PGN_ANNOTATION_INTRESTING_MOVE, // !?
    PGN_ANNOTATION_DUBIOUS_MOVE,    // ?!
} pgn_annotation_t;

pgn_annotation_t __pgn_annotation_nag_from_string(char *str, size_t *consumed);
pgn_annotation_t __pgn_annotation_from_string(char *str, size_t *consumed);
pgn_annotation_t pgn_annotation_from_string(char *str);
size_t pgn_annotation_to_string(pgn_annotation_t annotation, char *dest);

#endif // __LIBPGN_ANNOTATION_H
