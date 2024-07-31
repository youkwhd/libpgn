#include <pgn.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

unsigned int __nth = 1;

void __print_success()
{
    printf("[%d] Assertion success\n", __nth++);
}

void test_parsing_piece()
{
    printf("calling %s()\n", __func__);
    __nth = 1;

    for (char ch = 'a'; ch <= 'z'; ch++) {
        assert(pgn_piece_from_char(ch) == PGN_PIECE_UNKNOWN);
    }

    assert(pgn_piece_from_char(0) == PGN_PIECE_UNKNOWN);
    assert(pgn_piece_from_char('P') == PGN_PIECE_PAWN);
    assert(pgn_piece_from_char('R') == PGN_PIECE_ROOK);
    assert(pgn_piece_from_char('N') == PGN_PIECE_KNIGHT);
    assert(pgn_piece_from_char('B') == PGN_PIECE_BISHOP);
    assert(pgn_piece_from_char('Q') == PGN_PIECE_QUEEN);
    assert(pgn_piece_from_char('K') == PGN_PIECE_KING);

    __print_success();
}

void test_convert_piece()
{
    printf("calling %s()\n", __func__);
    __nth = 2;

    assert(pgn_piece_to_string(PGN_PIECE_UNKNOWN) == NULL);
    assert(strcmp(pgn_piece_to_string(PGN_PIECE_PAWN), "Pawn") == 0);
    assert(strcmp(pgn_piece_to_string(PGN_PIECE_ROOK), "Rook") == 0);
    assert(strcmp(pgn_piece_to_string(PGN_PIECE_KNIGHT), "Knight") == 0);
    assert(strcmp(pgn_piece_to_string(PGN_PIECE_BISHOP), "Bishop") == 0);
    assert(strcmp(pgn_piece_to_string(PGN_PIECE_QUEEN), "Queen") == 0);
    assert(strcmp(pgn_piece_to_string(PGN_PIECE_KING), "King") == 0);

    __print_success();
}

int main(void)
{
    test_parsing_piece();
    test_convert_piece();
    putchar('\n');
    return 0;
}
