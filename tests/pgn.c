#include <pgn.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

unsigned int __nth = 1;

void __print_success()
{
    printf("[%d] Assertion success\n", __nth++);
}

void test_parsing_pgn()
{
    printf("calling %s()\n", __func__);
    __nth = 1;

    pgn_t *pgn = pgn_init();
    pgn_parse(pgn,
        "[Event \"Ch City (open)\"]\n"
        "[Site \"Frankfurt (Germany)\"]\n"
        "\n"
        "1.e4 e5\n"
        "2.Nc3 Nc6\n"
        "3. g3 0-1");

    assert(strcmp(pgn_metadata_get(pgn->metadata, "Event"), "Ch City (open)") == 0);
    assert(strcmp(pgn_metadata_get(pgn->metadata, "Site"), "Frankfurt (Germany)") == 0);

    assert(strcmp(pgn->moves->values[0].white.notation, "e4") == 0);
    assert(pgn->moves->values[0].white.piece == PGN_PIECE_PAWN);
    assert(pgn->moves->values[0].white.dest.x == 'e');
    assert(pgn->moves->values[0].white.dest.y == 4);
    assert(pgn->moves->values[0].white.captures == false);
    assert(pgn->moves->values[0].white.annotation == PGN_ANNOTATION_NONE);
    assert(strcmp(pgn->moves->values[0].black.notation, "e5") == 0);
    assert(pgn->moves->values[0].black.piece == PGN_PIECE_PAWN);
    assert(pgn->moves->values[0].black.dest.x == 'e');
    assert(pgn->moves->values[0].black.dest.y == 5);
    assert(pgn->moves->values[0].black.captures == false);
    assert(pgn->moves->values[0].black.annotation == PGN_ANNOTATION_NONE);
    assert(pgn->moves->values[0].alternatives == NULL);

    assert(strcmp(pgn->moves->values[1].white.notation, "Nc3") == 0);
    assert(pgn->moves->values[1].white.piece == PGN_PIECE_KNIGHT);
    assert(pgn->moves->values[1].white.dest.x == 'c');
    assert(pgn->moves->values[1].white.dest.y == 3);
    assert(pgn->moves->values[1].white.captures == false);
    assert(pgn->moves->values[1].white.annotation == PGN_ANNOTATION_NONE);
    assert(strcmp(pgn->moves->values[1].black.notation, "Nc6") == 0);
    assert(pgn->moves->values[1].black.piece == PGN_PIECE_KNIGHT);
    assert(pgn->moves->values[1].black.dest.x == 'c');
    assert(pgn->moves->values[1].black.dest.y == 6);
    assert(pgn->moves->values[1].black.captures == false);
    assert(pgn->moves->values[1].black.annotation == PGN_ANNOTATION_NONE);
    assert(pgn->moves->values[1].alternatives == NULL);

    assert(pgn->score.white == 0 && pgn->score.black == 1);

    pgn_cleanup(pgn);
    __print_success();
}

int main(void)
{
    test_parsing_pgn();
    putchar('\n');
    return 0;
}
