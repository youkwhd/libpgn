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

#define PGN_PIECE_PAWN_STR "Pawn"
#define PGN_PIECE_ROOK_STR "Rook"
#define PGN_PIECE_KNIGHT_STR "Knight"
#define PGN_PIECE_BISHOP_STR "Bishop"
#define PGN_PIECE_QUEEN_STR "Queen"
#define PGN_PIECE_KING_STR "King"

typedef enum pgn_piece_t {
    PGN_PIECE_UNKNOWN = -1,
    PGN_PIECE_PAWN,
    PGN_PIECE_ROOK,
    PGN_PIECE_KNIGHT,
    PGN_PIECE_BISHOP,
    PGN_PIECE_QUEEN,
    PGN_PIECE_KING,
} pgn_piece_t;

pgn_piece_t pgn_piece_from_alphabet(char ch);
char pgn_piece_to_alphabet(pgn_piece_t piece);
char *pgn_piece_to_string(pgn_piece_t piece);

#endif // __LIBPGN_PIECE_H
