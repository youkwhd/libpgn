#include <ctype.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "moves.h"
#include "annotation.h"
#include "check.h"
#include "piece.h"
#include "utils/cursor.h"

pgn_move_t __pgn_move_from_string(char *str, size_t *consumed)
{
    pgn_move_t move = {0};
    size_t cursor = 0;

    move.piece = pgn_piece_from_char(str[cursor++]);
    if (move.piece == PGN_PIECE_UNKNOWN) {
        cursor--;

        move.castles = PGN_CASTLING_NONE;
        if (str[cursor] == 'O') {
            assert(str[++cursor] == '-');
            assert(str[++cursor] == 'O');
            move.castles = PGN_CASTLING_KINGSIDE;
            cursor++;

            if (str[cursor] == '-') {
                assert(str[++cursor] == 'O');
                move.castles = PGN_CASTLING_QUEENSIDE;
                cursor++;
            }

            goto check;
        }

        move.piece = PGN_PIECE_PAWN;
    }

    if (str[cursor] == 'x' || str[cursor] == ':') {
        move.captures = true;
        cursor++;

        assert(islower(str[cursor]));
        move.dest.x = str[cursor++];
        assert(isdigit(str[cursor]));
        move.dest.y = str[cursor++] - '0';
    } else {
        if (islower(str[cursor])) move.from.x = str[cursor++];
        if (isdigit(str[cursor])) move.from.y = str[cursor++] - '0';

        if (str[cursor] == 'x' || str[cursor] == ':') {
            move.captures = true;
            cursor++;

            assert(islower(str[cursor]));
            move.dest.x = str[cursor++];
            assert(isdigit(str[cursor]));
            move.dest.y = str[cursor++] - '0';
        } else if (islower(str[cursor])) {
            assert(islower(str[cursor]));
            move.dest.x = str[cursor++];
            assert(isdigit(str[cursor]));
            move.dest.y = str[cursor++] - '0';
        } else {
            move.dest = move.from;
            move.from = (pgn_coordinate_t){0};
        }
    }

    move.promoted_to = pgn_piece_from_char(str[cursor]);
    if (move.promoted_to == PGN_PIECE_UNKNOWN) {
        switch (str[cursor]) {
        case '(':
            move.promoted_to = pgn_piece_from_char(str[++cursor]);
            assert(move.promoted_to != PGN_PIECE_UNKNOWN);
            assert(str[++cursor] == ')');
            cursor++;
            break;
        case '=':
        case '/':
            move.promoted_to = pgn_piece_from_char(str[++cursor]);
            assert(move.promoted_to != PGN_PIECE_UNKNOWN);
            cursor++;
            break;
        }

    }

check:
    move.check = __pgn_check_from_string(str + cursor, &cursor);
    move.annotation = __pgn_annotation_from_string(str + cursor, &cursor);

    pgn_cursor_skip_whitespace(str, &cursor);

    /* could be en passant */
    if (str[cursor] == 'e' && str[cursor + 1] == '.') {
        assert(str[cursor] == 'e');
        assert(str[++cursor] == '.');
        assert(str[++cursor] == 'p');
        assert(str[++cursor] == '.');
        cursor++;
    }

    /* Check for NAG annotation.
     */
    if (move.annotation == PGN_ANNOTATION_NULL)
        move.annotation = __pgn_annotation_from_string(str + cursor, &cursor);

    size_t notation_len = cursor;

    /* We slipped too much to the right because 
     * the possibility of having multiple NAG annotation.
     *
     * TODO: check for comments
     */
    if (isspace(str[notation_len - 1])) {
        notation_len--;

        while (isspace(str[notation_len])) {
            notation_len--;
        }

        notation_len++;
    }
    strncpy(move.notation, str, notation_len);

    *consumed += cursor;
    return move;
}

pgn_move_t pgn_move_from_string(char *str)
{
    size_t consumed = 0;
    return __pgn_move_from_string(str, &consumed);
}

pgn_moves_t *__pgn_moves_from_string_recurse(char *str, size_t *consumed, pgn_moves_t *moves)
{
    if (str[0] == ')' || str[0] == '\0')
        return moves;

    size_t cursor = 0;
    __pgn_moves_item_t move = { .alternatives = NULL };

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
    pgn_cursor_skip_whitespace(str, &cursor);

    assert(dots_count == 0 || dots_count == 1 || dots_count == 3);
    if (dots_count == 0 || dots_count == 1) {
        move.white = __pgn_move_from_string(str + cursor, &cursor);
    } else if (dots_count == 3) {
        move.black = __pgn_move_from_string(str + cursor, &cursor);
        /* TODO: remove pgn comments */
        pgn_moves_push(moves, move);
        __pgn_moves_from_string_recurse(str + cursor, &cursor, moves);
        *consumed += cursor;
        return moves;
    }

    pgn_cursor_skip_whitespace(str, &cursor);
    pgn_cursor_skip_comment(str, &cursor);
    pgn_cursor_skip_whitespace(str, &cursor);

    if (str[cursor] == '(') {
        cursor++;
        pgn_cursor_skip_whitespace(str, &cursor);
        move.alternatives = __pgn_moves_from_string_recurse(str + cursor, &cursor, pgn_moves_init());
        pgn_cursor_skip_whitespace(str, &cursor);
        assert(str[cursor++] == ')');

        pgn_cursor_skip_whitespace(str, &cursor);
    }

    /* TODO: maybe isolate into a function
     *
     * checking if it's the score.
     */
    if ((isdigit(str[cursor]) && (str[cursor + 1] == '-' || str[cursor + 1] == '/')) || str[cursor] == '*') {
        pgn_moves_push(moves, move);
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
    pgn_cursor_skip_whitespace(str, &cursor);

    move.black = __pgn_move_from_string(str + cursor, &cursor);

    pgn_cursor_skip_whitespace(str, &cursor);
    pgn_cursor_skip_comment(str, &cursor);
    pgn_cursor_skip_whitespace(str, &cursor);

    if (str[cursor] == '(') {
        cursor++;
        pgn_cursor_skip_whitespace(str, &cursor);
        move.alternatives = __pgn_moves_from_string_recurse(str + cursor, &cursor, pgn_moves_init());
        pgn_cursor_skip_whitespace(str, &cursor);
        assert(str[cursor++] == ')');

        pgn_cursor_skip_whitespace(str, &cursor);
    }

    pgn_moves_push(moves, move);
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

pgn_moves_t *pgn_moves_init(void)
{
    pgn_moves_t *moves = malloc(sizeof *moves);
    moves->values = malloc(sizeof *moves->values * PGN_MOVES_INITIAL_SIZE);
    moves->size = PGN_MOVES_INITIAL_SIZE;
    moves->length = 0;

    return moves;
}

void pgn_moves_push(pgn_moves_t *moves, __pgn_moves_item_t __moves)
{
    if (moves->length >= moves->size) {
        moves->size += PGN_MOVES_GROW_SIZE;
        moves->values = realloc(moves->values,  sizeof(*moves->values) * moves->size);
    }

    moves->values[moves->length++] = __moves;
}

void pgn_moves_cleanup(pgn_moves_t *moves)
{
    for (size_t i = 0; i < moves->length; i++) {
        if (moves->values[i].alternatives) {
            pgn_moves_cleanup(moves->values[i].alternatives);
        }
    }

    free(moves->values);
    free(moves);
}
