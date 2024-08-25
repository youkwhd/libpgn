#include "suite6.h"

#include <pgn.h>
#include <string.h>

void test_parsing_pgn()
{
    pgn_t *pgn = pgn_init();
    pgn_parse(pgn,
        "[Event \"Ch City (open)\"]\n"
        "[Site \"Frankfurt (Germany)\"]\n"
        "\n"
        "1.e4 e5\n"
        "2.Nc3 Nc6\n"
        "3. g3 0-1");

    suite6_assert(strcmp(pgn_metadata_get(pgn->metadata, "Event"), "Ch City (open)") == 0);
    suite6_assert(strcmp(pgn_metadata_get(pgn->metadata, "Site"), "Frankfurt (Germany)") == 0);

    suite6_assert(strcmp(pgn->moves->values[0].white.notation, "e4") == 0);
    suite6_assert(pgn->moves->values[0].white.piece == PGN_PIECE_PAWN);
    suite6_assert(pgn->moves->values[0].white.dest.x == 'e');
    suite6_assert(pgn->moves->values[0].white.dest.y == 4);
    suite6_assert(pgn->moves->values[0].white.captures == false);
    suite6_assert(pgn->moves->values[0].white.annotation == PGN_ANNOTATION_NONE);
    suite6_assert(strcmp(pgn->moves->values[0].black.notation, "e5") == 0);
    suite6_assert(pgn->moves->values[0].black.piece == PGN_PIECE_PAWN);
    suite6_assert(pgn->moves->values[0].black.dest.x == 'e');
    suite6_assert(pgn->moves->values[0].black.dest.y == 5);
    suite6_assert(pgn->moves->values[0].black.captures == false);
    suite6_assert(pgn->moves->values[0].black.annotation == PGN_ANNOTATION_NONE);
    suite6_assert(pgn->moves->values[0].alternatives == NULL);

    suite6_assert(strcmp(pgn->moves->values[1].white.notation, "Nc3") == 0);
    suite6_assert(pgn->moves->values[1].white.piece == PGN_PIECE_KNIGHT);
    suite6_assert(pgn->moves->values[1].white.dest.x == 'c');
    suite6_assert(pgn->moves->values[1].white.dest.y == 3);
    suite6_assert(pgn->moves->values[1].white.captures == false);
    suite6_assert(pgn->moves->values[1].white.annotation == PGN_ANNOTATION_NONE);
    suite6_assert(strcmp(pgn->moves->values[1].black.notation, "Nc6") == 0);
    suite6_assert(pgn->moves->values[1].black.piece == PGN_PIECE_KNIGHT);
    suite6_assert(pgn->moves->values[1].black.dest.x == 'c');
    suite6_assert(pgn->moves->values[1].black.dest.y == 6);
    suite6_assert(pgn->moves->values[1].black.captures == false);
    suite6_assert(pgn->moves->values[1].black.annotation == PGN_ANNOTATION_NONE);
    suite6_assert(pgn->moves->values[1].alternatives == NULL);

    suite6_assert(pgn->score.white == 0 && pgn->score.black == 1);

    pgn_cleanup(pgn);
}

int main(void)
{
    test_parsing_pgn();
    return 0;
}
