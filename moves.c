#include <ctype.h>
#include <assert.h>
#include <stdio.h>
#include "moves.h"

pgn_move_t __pgn_move_from_string(char *str, size_t *consumed)
{
    /* TODO: wip reverse parsing
     *
     * case with en passant
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
    if (str[cursor] == 'x' || str[cursor] == ':') {
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

__pgn_moves_t *__pgn_moves_init()
{
    __pgn_moves_t *__moves = malloc(sizeof *__moves);
    // __moves->alternatives = {0};
    __moves->alternatives.values = malloc(sizeof *__moves->alternatives.values * PGN_MOVES_ALTERNATIVES_INITIAL_SIZE);
    __moves->alternatives.length = 0;
    __moves->alternatives.size = PGN_MOVES_ALTERNATIVES_INITIAL_SIZE;

    return __moves;
}

void __pgn_moves_cleanup(__pgn_moves_t *__moves)
{
    free(__moves->alternatives.values);
    free(__moves);
}

__pgn_moves_t *__pgn_moves_from_string(char *str, size_t *consumed)
{
    size_t cursor = 0;
    __pgn_moves_t *__moves = __pgn_moves_init();

    if (isdigit(str[cursor]) && str[cursor + 1] == '.') {
        cursor += 2;
    }
    while (str[cursor] == ' ') cursor++;

    __moves->white = __pgn_move_from_string(str + cursor, &cursor);

remove_whitespaces:
    while (str[cursor] == ' ') cursor++;
    if (str[cursor] == '{') {
        while (str[cursor] != '}') cursor++;
        cursor++;
        goto remove_whitespaces;
    }

    if (isdigit(str[cursor]) && str[cursor + 1] == '.') {
        cursor += 4;
    }
    while (str[cursor] == ' ') cursor++;

    __moves->black = __pgn_move_from_string(str + cursor, &cursor);

    return __moves;
}

__pgn_moves_t *pgn_moves_from_string(char *str)
{
    size_t consumed = 0;
    return __pgn_moves_from_string(str, &consumed);
}

pgn_moves_t *pgn_moves_init()
{
    pgn_moves_t *moves = malloc(sizeof *moves);
    moves->values = malloc(sizeof *moves->values * PGN_MOVES_INITIAL_SIZE);
    moves->size = PGN_MOVES_INITIAL_SIZE;
    moves->length = 0;

    return moves;
}

void pgn_moves_push(pgn_moves_t *moves, __pgn_moves_t __moves)
{
    if (moves->length >= moves->size) {
        moves->size += PGN_MOVES_GROW_SIZE;
        moves->values = realloc(moves->values, moves->size);
    }

    moves->values[moves->length++] = __moves;
}

void pgn_moves_cleanup(pgn_moves_t *moves)
{
    free(moves->values->alternatives.values);
    free(moves->values);
    free(moves);
}
