#include <pgn.h>
#include <stdbool.h>

#include "fmt.h"

void fmt_print_tab(int depth, int width)
{
    for (int i = 0; i < depth; i++) {
        for (int j = 0; j < width; j++) {
            printf(" ");
        }
    }
}

bool fmt_print_metadata(pgn_t *pgn)
{
    bool printed = false;

    for (size_t i = 0; i < pgn->metadata->length; i++) {
        printf("[%s \"%s\"]\n", pgn->metadata->items[i].key->buf, pgn->metadata->items[i].value->buf);
        printed = true;
    }

    return printed;
}

bool fmt_print_moves(pgn_t *pgn, int depth)
{
    bool printed = false;

    /* TODO: recursively print alternatives
     */
    for (size_t i = 0; i < pgn->moves->length; i++) {
        pgn_move_t white = pgn->moves->values[i].white;
        pgn_move_t black = pgn->moves->values[i].black;

        fmt_print_tab(depth, 2);
        printf("%zu. %s %s\n", i + 1, white.notation, black.notation);
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
    if (fmt_print_metadata(pgn))
        printf("\n");

    fmt_print_moves(pgn, 0);
    fmt_print_score(pgn);
}
