#include <ctype.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "moves.h"

int __pgn_comment_length(char *str)
{
    int cursor = 0;

    assert(str[cursor++] == '{');
    while (str[cursor++] != '}');

    return cursor;
}

int __pgn_whitespace_length(char *str)
{
    int cursor = 0;

    while (isspace(str[cursor])) cursor++;

    return cursor;
}

pgn_move_t __pgn_move_from_string(char *str, size_t *consumed)
{
    /* TODO: wip reverse parsing
     *
     * case with en passant
     */
    pgn_move_t move = {0};
    int cursor = 0;

    int __open_paren = 0;
    int __close_paren = 0;

    while (str[cursor] != '\0' && !isspace(str[cursor])) {
        if (str[cursor] == '(') __open_paren++;
        if (str[cursor] == ')' && ++__close_paren > __open_paren) break;

        cursor++;
    }

    /* trying to parse the nth best move
     *
     * TODO: check for '\0'
     */
    int __cursor = cursor;
    if (isspace(str[__cursor])) {
        __cursor += __pgn_whitespace_length(str + __cursor);

        if (str[__cursor] == '$') {
            assert(isdigit(str[++__cursor]));
            /* TODO: what about 10th best move and beyond
             *
             * (this will only take the first digit)
             */
            move.nth_best = str[__cursor] - '0';

            /* TODO: don't discard the rest.
             */
            while (isdigit(str[__cursor])) __cursor++;
        }
    }

    *consumed += cursor;
    if (move.nth_best)
        *consumed += (__cursor - cursor);

    cursor--;

    while (pgn_annotation_from_string(str + cursor) != PGN_ANNOTATION_NONE) cursor--;
    move.annotation = pgn_annotation_from_string(str + (cursor + 1));

    while (str[cursor] == '+') cursor--;
    move.check = pgn_check_from_string(str + (cursor + 1));

    for (move.castles = PGN_CASTLING_NONE; cursor >= 0 && str[cursor] == 'O'; cursor -= 2) {
        if (cursor - 1 >= 0)
            assert(str[cursor - 1] == '-');

        move.castles++;
    }
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

__pgn_moves_item_t *__pgn_moves_item_init()
{
    __pgn_moves_item_t *moves = malloc(sizeof *moves);
    moves->alternatives = NULL;
    return moves;
}

void __pgn_moves_item_cleanup(__pgn_moves_item_t *moves)
{
    if (moves->alternatives) {
        pgn_moves_cleanup(moves->alternatives);
    }

    free(moves);
}

pgn_moves_t *__pgn_moves_from_string_recurse(char *str, size_t *consumed, pgn_moves_t *moves)
{
    if (str[0] == ')' || str[0] == '\0')
        return moves;

    size_t cursor = 0;
    __pgn_moves_item_t *move = __pgn_moves_item_init();

    /* TODO: maybe isolate into a function
     *
     * checking if it's the score.
     */
    if ((isdigit(str[cursor]) && (str[cursor + 1] == '-' || str[cursor + 1] == '/')) || str[cursor] == '*') {
        *consumed += cursor;
        return moves;
    }

    int dots_count = 0;
    if (isdigit(str[cursor])) {
        while (isdigit(str[cursor])) cursor++;
        while (str[cursor] == '.') {
            cursor++;
            dots_count++;
        }
    }
    cursor += __pgn_whitespace_length(str + cursor);

    assert(dots_count == 0 || dots_count == 1 || dots_count == 3);
    if (dots_count == 0 || dots_count == 1) {
        move->white = __pgn_move_from_string(str + cursor, &cursor);
    } else if (dots_count == 3) {
        move->black = __pgn_move_from_string(str + cursor, &cursor);
        /* TODO: remove pgn comments */
        pgn_moves_push(moves, move);
        __pgn_moves_from_string_recurse(str + cursor, &cursor, moves);
        *consumed += cursor;
        return moves;
    }

    cursor += __pgn_whitespace_length(str + cursor);
    while (str[cursor] == '{') cursor += __pgn_comment_length(str + cursor);
    cursor += __pgn_whitespace_length(str + cursor);

    if (str[cursor] == '(') {
        cursor++;
        cursor += __pgn_whitespace_length(str + cursor);
        move->alternatives = __pgn_moves_from_string_recurse(str + cursor, &cursor, pgn_moves_init());
        cursor += __pgn_whitespace_length(str + cursor);
        assert(str[cursor++] == ')');

        cursor += __pgn_whitespace_length(str + cursor);
    }

    /* TODO: maybe isolate into a function
     *
     * checking if it's the score.
     */
    if ((isdigit(str[cursor]) && (str[cursor + 1] == '-' || str[cursor + 1] == '/')) || str[cursor] == '*') {
        *consumed += cursor;
        return moves;
    }

    /* We're at the end of pgn, no black move present.
     *
     * TODO: investigate (might be a corrupt file?)
     */
    if (str[cursor] == ')' || str[cursor] == '\0') {
        pgn_moves_push(moves, move);
        *consumed += cursor;
        return moves;
    }

    if (isdigit(str[cursor])) {
        while (isdigit(str[cursor])) cursor++;

        for (int i = 0; i < 3; i++)
            assert(str[cursor++] == '.');
    }
    cursor += __pgn_whitespace_length(str + cursor);

    move->black = __pgn_move_from_string(str + cursor, &cursor);

    cursor += __pgn_whitespace_length(str + cursor);
    while (str[cursor] == '{') cursor += __pgn_comment_length(str + cursor);
    cursor += __pgn_whitespace_length(str + cursor);

    pgn_moves_push(moves, move);

    if (str[cursor] == '(') {
        cursor++;
        cursor += __pgn_whitespace_length(str + cursor);
        move->alternatives = __pgn_moves_from_string_recurse(str + cursor, &cursor, pgn_moves_init());
        cursor += __pgn_whitespace_length(str + cursor);
        assert(str[cursor++] == ')');

        cursor += __pgn_whitespace_length(str + cursor);
    }

    __pgn_moves_from_string_recurse(str + cursor, &cursor, moves);
    *consumed += cursor;
    return moves;
}

pgn_moves_t *__pgn_moves_from_string(char *str, size_t *consumed)
{
    return __pgn_moves_from_string_recurse(str, consumed, pgn_moves_init());
}

pgn_moves_t *pgn_moves_from_string(char *str)
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

void pgn_moves_push(pgn_moves_t *moves, __pgn_moves_item_t *__moves)
{
    if (moves->length >= moves->size) {
        moves->size += PGN_MOVES_GROW_SIZE;
        moves->values = realloc(moves->values, moves->size);
    }

    moves->values[moves->length++] = __moves;
}

void pgn_moves_cleanup(pgn_moves_t *moves)
{
    for (size_t i = 0; i < moves->length; i++) {
        __pgn_moves_item_cleanup(moves->values[i]);
    }

    free(moves->values);
    free(moves);
}
