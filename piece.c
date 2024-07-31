#include "piece.h"

#include <stddef.h>

pgn_piece_t pgn_piece_from_char(char ch)
{
    switch (ch) {
    case PGN_PIECE_PAWN:
    case PGN_PIECE_ROOK:
    case PGN_PIECE_KNIGHT:
    case PGN_PIECE_BISHOP:
    case PGN_PIECE_QUEEN:
    case PGN_PIECE_KING:
        return ch;
    default: return PGN_PIECE_UNKNOWN;
    }
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
    default: return NULL;
    }
}
