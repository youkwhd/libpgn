#ifndef __LIBPGN_PIECE_H
#define __LIBPGN_PIECE_H

/* types that represent
 * chess pieces
 */

#define PGN_PIECE_PAWN_ALPHABET 'P'
#define PGN_PIECE_ROOK_ALPHABET 'R'
#define PGN_PIECE_KNIGHT_ALPHABET 'N'
#define PGN_PIECE_BISHOP_ALPHABET 'B'
#define PGN_PIECE_QUEEN_ALPHABET 'Q'
#define PGN_PIECE_KING_ALPHABET 'K'

typedef enum pgn_piece_t {
    PGN_PIECE_PAWN = 0,
    PGN_PIECE_ROOK,
    PGN_PIECE_KNIGHT,
    PGN_PIECE_BISHOP,
    PGN_PIECE_QUEEN,
    PGN_PIECE_KING,
} pgn_piece_t;

pgn_piece_t pgn_piece_parse_from_alphabet(char ch);

#endif // __LIBPGN_PIECE_H
