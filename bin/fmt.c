#include <pgn.h>
#include <pgn/metadata.h>
#include <pgn/moves.h>
#include <stdbool.h>

#include "fmt.h"

bool fmt_print_moves(pgn_moves_t *moves, int depth, size_t last_index);

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
        printf("(");
        fmt_print_moves(alt->values[i], depth, last_index);
        printf(") ");
    }

    return printed;
}

/* TODO: do actual formatting, we're just re-printing without comments
 */
bool fmt_print_moves(pgn_moves_t *moves, int depth, size_t last_index)
{
    bool printed = false;

    for (size_t i = 0; i < moves->length; i++) {
        pgn_move_t white = moves->values[i].white;
        pgn_move_t black = moves->values[i].black;

        if (white.notation[0]) {
            printf("%zu. %s", i + last_index, white.notation);

            if (white.alternatives) {
                printf(" ");
                fmt_print_alternative_moves(white.alternatives, 0, i + last_index);
            }
        }

        if (black.notation[0]) {
            if (white.alternatives)
                printf(" %zu...", i + last_index);

            if (!white.notation[0]) {
                printf("%zu...", i + last_index);
            }

            printf(" %s", black.notation);

            if (black.alternatives) {
                printf(" ");
                fmt_print_alternative_moves(black.alternatives, 0, i + last_index);
            }
        }


        printf(" ");
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

    fmt_print_moves(pgn->moves, 0, 1);
    fmt_print_score(pgn);
}
