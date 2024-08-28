#include <pgn.h>
#include <pgn/metadata.h>
#include <pgn/moves.h>
#include <stdbool.h>

#include "fmt.h"

bool fmt_print_moves(pgn_moves_t *moves, int depth, size_t last_index, bool newline);

void fmt_print_tab(int depth, int width)
{
    for (int i = 0; i < depth; i++) {
        for (int j = 0; j < width; j++) {
            printf(" ");
        }
    }
}

bool fmt_print_metadata(pgn_metadata_t *mt)
{
    bool printed = false;

    for (size_t i = 0; i < mt->length; i++) {
        printf("[%s \"%s\"]\n", mt->items[i].key->buf, mt->items[i].value->buf);
        printed = true;
    }

    return printed;
}

bool fmt_print_alternative_moves(pgn_alternative_moves_t *alt, int depth, size_t last_index)
{
    bool printed = false;

    for (size_t i = 0; i < alt->length; i++) {
        fmt_print_tab(depth, 2);

        printf("(");
        fmt_print_moves(alt->values[i], 0, last_index, false);
        printf(")\n");
    }

    return printed;
}

bool fmt_print_moves(pgn_moves_t *moves, int depth, size_t last_index, bool newline)
{
    bool printed = false;

    for (size_t i = 0; i < moves->length; i++) {
        pgn_move_t white = moves->values[i].white;
        pgn_move_t black = moves->values[i].black;

        fmt_print_tab(depth, 2);
        printf("%zu. %s %s", i + last_index, white.notation, black.notation);
        if (newline) putchar('\n');

        if (moves->values[i].alternatives)
            fmt_print_alternative_moves(moves->values[i].alternatives, ++depth, i + last_index);

        printed = true;
    }

    return printed;
}

/* TODO: this is incorrect, try getting
 * the score from the actual end of moves
 */
bool fmt_print_score(pgn_t *pgn)
{
    char *score = pgn_metadata_get(pgn->metadata, "Result");
    if (!score) return false;

    printf("%s\n", score);
    return true;
}

void fmt_print(pgn_t *pgn)
{
    if (fmt_print_metadata(pgn->metadata))
        printf("\n");

    fmt_print_moves(pgn->moves, 0, 1, true);
    fmt_print_score(pgn);
}
