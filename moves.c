#include <ctype.h>
#include <assert.h>
#include <stdio.h>
#include "moves.h"

pgn_move_t __pgn_move_from_string(char *str, size_t *consumed)
{
    /* TODO: wip reverse parsing
     */
    pgn_move_t move = {0};
    move.piece = PGN_PIECE_UNKNOWN;
    // move.? = ..

    int cursor = 0;

    while (str[cursor] != '\0' && !isspace(str[cursor])) cursor++;
    *consumed += cursor;
    cursor--;

    while (str[cursor] == '?' || str[cursor] == '!' || str[cursor] == '#') cursor--;
    move.annotation = pgn_annotation_from_string(str + (++cursor));
    cursor--;

    move.checks = false;
    if (str[cursor] == '+') {
        move.checks = true;
        cursor--;
    }

    for (move.castles = PGN_CASTLING_NONE; cursor >= 0 && str[cursor] == 'O'; cursor -= 2)
        move.castles++;

    if (cursor <= 0) return move;

    move.promoted_to = pgn_piece_from_char(str[cursor]);
    if (move.promoted_to == PGN_PIECE_UNKNOWN) {
        if (str[cursor] == ')') {
            move.promoted_to = pgn_piece_from_char(str[--cursor]);
            assert(str[--cursor] == '(');
            cursor--;
        }
    } else {
        cursor--;
        if (str[cursor] == '=' || str[cursor] == '/')
            cursor--;
    }

    if (isdigit(str[cursor])) move.dest.y = str[cursor--] - '0';
    if (islower(str[cursor]) && str[cursor] != 'x') move.dest.x = str[cursor--];

    move.captures = false;
    if (str[cursor] == 'x') {
        move.captures = true;
        cursor--;
    }

    if (isdigit(str[cursor])) move.from.y = str[cursor--] - '0';
    if (islower(str[cursor])) move.from.x = str[cursor--];

    move.piece = PGN_PIECE_PAWN;
    if (cursor >= 0) move.piece = pgn_piece_from_char(str[cursor]);

    return move;
}

pgn_move_t pgn_move_from_string(char *str)
{
    size_t consumed = 0;
    return __pgn_move_from_string(str, &consumed);
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
