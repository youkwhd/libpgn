#ifndef __LIBPGN_PIECE_H
#define __LIBPGN_PIECE_H

#include "export.h"

/* types that represent
 * chess pieces
 */

#define PGN_PIECE_PAWN_CHAR 'P'
#define PGN_PIECE_ROOK_CHAR 'R'
#define PGN_PIECE_KNIGHT_CHAR 'N'
#define PGN_PIECE_BISHOP_CHAR 'B'
#define PGN_PIECE_QUEEN_CHAR 'Q'
#define PGN_PIECE_KING_CHAR 'K'

typedef enum pgn_piece_t {
    PGN_PIECE_UNKNOWN = 0,
    PGN_PIECE_PAWN,
    PGN_PIECE_ROOK,
    PGN_PIECE_KNIGHT,
    PGN_PIECE_BISHOP,
    PGN_PIECE_QUEEN,
    PGN_PIECE_KING,
} pgn_piece_t;

PGN_EXPORT pgn_piece_t pgn_piece_from_char(char ch);
PGN_EXPORT char pgn_piece_to_char(pgn_piece_t piece);
PGN_EXPORT char *pgn_piece_to_string(pgn_piece_t piece);

#endif // __LIBPGN_PIECE_H
