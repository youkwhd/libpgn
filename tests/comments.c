#include "extra/suite6.h"

#include <pgn.h>
#include <string.h>

void test_parsing_moves_with_comments_multiples(void)
{
    pgn_moves_t *moves;

    moves = pgn_moves_from_string("1.e4 {hello} {from} {libpgn} e5");
    suite6_assert(moves->values[0].white.comments->length == 3);
    suite6_assert(moves->values[0].white.comments->values[0].position == PGN_COMMENT_POSITION_AFTER_MOVE);
    suite6_assert(!strcmp(moves->values[0].white.comments->values[0].value->buf, "hello"));
    suite6_assert(moves->values[0].white.comments->values[1].position == PGN_COMMENT_POSITION_AFTER_MOVE);
    suite6_assert(!strcmp(moves->values[0].white.comments->values[1].value->buf, "from"));
    suite6_assert(moves->values[0].white.comments->values[2].position == PGN_COMMENT_POSITION_AFTER_MOVE);
    suite6_assert(!strcmp(moves->values[0].white.comments->values[2].value->buf, "libpgn"));
    pgn_moves_cleanup(moves);

    moves = pgn_moves_from_string("1.e4 {dump} e5 { spaces does not get trimmed } { trim it with pgn_comment_trim() } {this makes the pgn file original -> } ");
    suite6_assert(moves->values[0].white.comments->length == 1);
    suite6_assert(moves->values[0].white.comments->values[0].position == PGN_COMMENT_POSITION_AFTER_MOVE);
    suite6_assert(!strcmp(moves->values[0].white.comments->values[0].value->buf, "dump"));
    suite6_assert(moves->values[0].black.comments->length == 3);
    suite6_assert(moves->values[0].black.comments->values[0].position == PGN_COMMENT_POSITION_AFTER_MOVE);
    suite6_assert(!strcmp(moves->values[0].black.comments->values[0].value->buf, " spaces does not get trimmed "));
    suite6_assert(moves->values[0].black.comments->values[1].position == PGN_COMMENT_POSITION_AFTER_MOVE);
    suite6_assert(!strcmp(moves->values[0].black.comments->values[1].value->buf, " trim it with pgn_comment_trim() "));
    suite6_assert(moves->values[0].black.comments->values[2].position == PGN_COMMENT_POSITION_AFTER_MOVE);
    suite6_assert(!strcmp(moves->values[0].black.comments->values[2].value->buf, "this makes the pgn file original -> "));
    pgn_moves_cleanup(moves);
}

void test_parsing_moves_with_comments_nested(void)
{
    pgn_moves_t *moves;

    moves = pgn_moves_from_string("1.e4 { a comment {inside a comment} ? } e5");
    suite6_assert(moves->values[0].white.comments->length == 1);
    suite6_assert(moves->values[0].white.comments->values[0].position == PGN_COMMENT_POSITION_AFTER_MOVE);
    suite6_assert(!strcmp(moves->values[0].white.comments->values[0].value->buf, " a comment {inside a comment} ? "));
    pgn_moves_cleanup(moves);
}

int main(void)
{
    test_parsing_moves_with_comments_multiples();
    return 0;
}
