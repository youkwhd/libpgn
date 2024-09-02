#ifndef __LIBPGN_PIECE_H
#define __LIBPGN_PIECE_H

typedef enum pgn_piece_t {
    PGN_PIECE_UNKNOWN = 0,
    PGN_PIECE_PAWN    = 'P',
    PGN_PIECE_ROOK    = 'R',
    PGN_PIECE_KNIGHT  = 'N',
    PGN_PIECE_BISHOP  = 'B',
    PGN_PIECE_QUEEN   = 'Q',
    PGN_PIECE_KING    = 'K',
} pgn_piece_t;

pgn_piece_t pgn_piece_from_char(char ch);
char *pgn_piece_to_string(pgn_piece_t piece);

#endif // __LIBPGN_PIECE_H
