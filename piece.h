#ifndef __LIBPGN_PIECE_H
#define __LIBPGN_PIECE_H

/* types that represent
 * chess pieces
 */

typedef enum pgn_piece_t {
    PGN_PIECE_PAWN = 0,
    PGN_PIECE_ROOK,
    PGN_PIECE_KNIGHT,
    PGN_PIECE_BISHOP,
    PGN_PIECE_QUEEN,
    PGN_PIECE_KING,
} pgn_piece_t;

#endif // __LIBPGN_PIECE_H
