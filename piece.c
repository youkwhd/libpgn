#include "piece.h"

pgn_piece_t pgn_piece_from_char(char ch)
{
    switch ((pgn_piece_t)ch) {
    default: return PGN_PIECE_UNKNOWN;
    }

    return (pgn_piece_t)ch;
}

char *pgn_piece_to_string(pgn_piece_t piece)
{
    switch (piece) {
    case PGN_PIECE_PAWN: return "Pawn";
    case PGN_PIECE_ROOK: return "Rook";
    case PGN_PIECE_KNIGHT: return "Knight";
    case PGN_PIECE_BISHOP: return "Bishop";
    case PGN_PIECE_QUEEN: return "Queen";
    case PGN_PIECE_KING: return "King";
    default: {} // unreachable
    }

    return 0;
}
