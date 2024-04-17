#include <pgn.h>
#include <assert.h>

void test_parsing_move()
{
    pgn_move_t move = {0};

    move = pgn_move_from_string("e4??");
    assert(move.piece == PGN_PIECE_PAWN);
    assert(move.captures == false);
    assert(move.to.x == 'e');
    assert(move.to.y == 4);
    assert(move.annotation == PGN_ANNOTATION_BLUNDER);

    move = pgn_move_from_string("Qf1?!");
    assert(move.piece == PGN_PIECE_QUEEN);
    assert(move.captures == false);
    assert(move.to.x == 'f');
    assert(move.to.y == 1);
    assert(move.annotation == PGN_ANNOTATION_DUBIOUS_MOVE);
}

int main(void)
{
    test_parsing_move();
    return 0;
}
