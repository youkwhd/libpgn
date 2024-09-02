#include "extra/suite6.h"

#include <pgn.h>

void test_parsing_score()
{
    suite6_assert(pgn_parse_score("1/2-1/2") == PGN_SCORE_DRAW);
    suite6_assert(pgn_parse_score("1-0") == PGN_SCORE_WHITE_WON);
    suite6_assert(pgn_parse_score("0-1") == PGN_SCORE_BLACK_WON);
    suite6_assert(pgn_parse_score("0-0") == PGN_SCORE_FORFEIT);
    suite6_assert(pgn_parse_score("0-1/2") == PGN_SCORE_WHITE_FORFEIT);
    suite6_assert(pgn_parse_score("1/2-0") == PGN_SCORE_BLACK_FORFEIT);
}
int main(void)
{
    test_parsing_score();
    return 0;
}
