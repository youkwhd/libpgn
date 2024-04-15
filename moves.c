#include "moves.h"

pgn_move_t pgn_move_from_string(char *str, size_t *consumed)
{
    pgn_move_t move = {0};

    move.piece = pgn_piece_from_alphabet(str[(*consumed)++]);
    if (move.piece == PGN_PIECE_UNKNOWN) move.piece = PGN_PIECE_PAWN;

    move.captures = false;
    if (str[*consumed] == 'x') {
        move.captures = true;
        (*consumed)++;
    }

    move.to.x = str[(*consumed)++];
    move.to.y = str[(*consumed)++] - '0';

    move.annotation = pgn_annotation_from_string(str, consumed);

    return move;
}

pgn_moves_t *pgn_moves_init()
{
    pgn_moves_t *moves = malloc(sizeof *moves);
    moves->values = malloc(sizeof *moves->values * PGN_MOVES_INITIAL_SIZE);
    moves->size = PGN_MOVES_INITIAL_SIZE;
    moves->length = 0;

    return moves;
}

void pgn_moves_push(pgn_moves_t *moves, pgn_move_t move)
{
    if (moves->length >= moves->size) {
        moves->size += PGN_MOVES_GROW_SIZE;
        moves->values = realloc(moves->values, moves->size);
    }

    moves->values[moves->length++] = move;
}

void pgn_moves_cleanup(pgn_moves_t *moves)
{
    free(moves->values);
    free(moves);
}
