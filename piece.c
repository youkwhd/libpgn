#include "piece.h"

pgn_piece_t pgn_piece_parse_from_alphabet(char ch)
{
    switch (ch) {
    case PGN_PIECE_PAWN_ALPHABET: return PGN_PIECE_PAWN;
    case PGN_PIECE_ROOK_ALPHABET: return PGN_PIECE_ROOK;
    case PGN_PIECE_KNIGHT_ALPHABET: return PGN_PIECE_KNIGHT;
    case PGN_PIECE_BISHOP_ALPHABET: return PGN_PIECE_BISHOP;
    case PGN_PIECE_QUEEN_ALPHABET: return PGN_PIECE_QUEEN;
    case PGN_PIECE_KING_ALPHABET: return PGN_PIECE_KING;
    default: return PGN_PIECE_PAWN;
    }
}
