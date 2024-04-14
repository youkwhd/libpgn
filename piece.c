#include "piece.h"

pgn_piece_t pgn_piece_from_alphabet(char ch)
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

char pgn_piece_to_alphabet(pgn_piece_t piece)
{
    switch (piece) {
    case PGN_PIECE_PAWN: return PGN_PIECE_PAWN_ALPHABET;
    case PGN_PIECE_ROOK: return PGN_PIECE_ROOK_ALPHABET;
    case PGN_PIECE_KNIGHT: return PGN_PIECE_KNIGHT_ALPHABET;
    case PGN_PIECE_BISHOP: return PGN_PIECE_BISHOP_ALPHABET;
    case PGN_PIECE_QUEEN: return PGN_PIECE_QUEEN_ALPHABET;
    case PGN_PIECE_KING: return PGN_PIECE_KING_ALPHABET;
    default: {} // unreachable
    }
}

char *pgn_piece_to_string(pgn_piece_t piece)
{
    switch (piece) {
    case PGN_PIECE_PAWN: return PGN_PIECE_PAWN_STR;
    case PGN_PIECE_ROOK: return PGN_PIECE_ROOK_STR;
    case PGN_PIECE_KNIGHT: return PGN_PIECE_KNIGHT_STR;
    case PGN_PIECE_BISHOP: return PGN_PIECE_BISHOP_STR;
    case PGN_PIECE_QUEEN: return PGN_PIECE_QUEEN_STR;
    case PGN_PIECE_KING: return PGN_PIECE_KING_STR;
    default: {} // unreachable
    }
}
