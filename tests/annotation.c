#include "extra/suite6.h"

#include <pgn.h>
#include <string.h>

void test_parsing_moves_with_annotation()
{
    pgn_moves_t *moves;

    moves = pgn_moves_from_string("1. a4?? a5!");
    suite6_assert(moves->values[0].white.annotation == PGN_ANNOTATION_BLUNDER);
    suite6_assert(moves->values[0].black.annotation == PGN_ANNOTATION_GOOD_MOVE);
    pgn_moves_cleanup(moves);
}

void test_parsing_moves_with_NAG_annotation()
{
    pgn_moves_t *moves;

    moves = pgn_moves_from_string("1. a4 $4 a5 $1");
    suite6_assert(moves->values[0].white.annotation == PGN_ANNOTATION_BLUNDER);
    suite6_assert(moves->values[0].black.annotation == PGN_ANNOTATION_GOOD_MOVE);
    pgn_moves_cleanup(moves);

    moves = pgn_moves_from_string("1. a4 $69 a5 $420");
    suite6_assert(moves->values[0].white.annotation == 69);
    suite6_assert(moves->values[0].black.annotation == 420);
    pgn_moves_cleanup(moves);

    moves = pgn_moves_from_string("6. Nce2 $2 e5 $0 $19 {}");
    suite6_assert(moves->values[0].white.annotation == PGN_ANNOTATION_MISTAKE);
    suite6_assert(moves->values[0].black.annotation == 19);
    pgn_moves_cleanup(moves);
    
}

int main(void)
{
    test_parsing_moves_with_annotation();
    test_parsing_moves_with_NAG_annotation();
    return 0;
}
