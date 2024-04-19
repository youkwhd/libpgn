#include <stdio.h>
#include "../pgn.h"
#include <assert.h>

unsigned int __nth = 1;

void __print_success()
{
    printf("[%d] Assertion success\n", __nth++);
}

void test_parsing_move()
{
    printf("calling %s()\n", __func__);
    __nth = 1;
    pgn_move_t move = {0};

    move = pgn_move_from_string("e4??");
    assert(move.piece == PGN_PIECE_PAWN);
    assert(move.captures == false);
    assert(move.from.x == PGN_COORDINATE_UNKNOWN);
    assert(move.from.y == PGN_COORDINATE_UNKNOWN);
    assert(move.dest.x == 'e');
    assert(move.dest.y == 4);
    assert(move.checks == false);
    assert(move.annotation == PGN_ANNOTATION_BLUNDER);
    __print_success();

    move = pgn_move_from_string("Qf1?!");
    assert(move.piece == PGN_PIECE_QUEEN);
    assert(move.captures == false);
    assert(move.from.x == PGN_COORDINATE_UNKNOWN);
    assert(move.from.y == PGN_COORDINATE_UNKNOWN);
    assert(move.dest.x == 'f');
    assert(move.dest.y == 1);
    assert(move.checks == false);
    assert(move.annotation == PGN_ANNOTATION_DUBIOUS_MOVE);
    __print_success();

    move = pgn_move_from_string("bxa8=Q??");
    assert(move.piece == PGN_PIECE_PAWN);
    assert(move.captures == true);
    assert(move.from.x == 'b');
    assert(move.from.y == PGN_COORDINATE_UNKNOWN);
    assert(move.dest.x == 'a');
    assert(move.dest.y == 8);
    assert(move.checks == false);
    assert(move.promoted_to == PGN_PIECE_QUEEN);
    assert(move.annotation == PGN_ANNOTATION_BLUNDER);
    __print_success();

    move = pgn_move_from_string("Bxg2");
    assert(move.piece == PGN_PIECE_BISHOP);
    assert(move.captures == true);
    assert(move.from.x == PGN_COORDINATE_UNKNOWN);
    assert(move.from.y == PGN_COORDINATE_UNKNOWN);
    assert(move.dest.x == 'g');
    assert(move.dest.y == 2);
    assert(move.checks == false);
    assert(move.promoted_to == PGN_PIECE_UNKNOWN);
    assert(move.annotation == PGN_ANNOTATION_NONE);
    __print_success();

    move = pgn_move_from_string("exf2+!");
    assert(move.piece == PGN_PIECE_PAWN);
    assert(move.captures == true);
    assert(move.from.x == 'e');
    assert(move.from.y == PGN_COORDINATE_UNKNOWN);
    assert(move.dest.x == 'f');
    assert(move.dest.y == 2);
    assert(move.checks == true);
    assert(move.promoted_to == PGN_PIECE_UNKNOWN);
    assert(move.annotation == PGN_ANNOTATION_GOOD_MOVE);
    __print_success();

    move = pgn_move_from_string("O-O+!!");
    assert(move.castles == PGN_CASTLING_KINGSIDE);
    assert(move.checks == true);
    assert(move.annotation == PGN_ANNOTATION_EXCELLENT_MOVE);
    __print_success();

    move = pgn_move_from_string("O-O-O");
    assert(move.castles == PGN_CASTLING_QUEENSIDE);
    assert(move.checks == false);
    assert(move.annotation == PGN_ANNOTATION_NONE);
    __print_success();
}

void test_parsing_bunch_of_moves()
{
    printf("calling %s()\n", __func__);
    __nth = 1;
    __pgn_moves_t *moves = NULL;

    moves = pgn_moves_from_string("1.e4 e5");
    assert(moves->white.piece == PGN_PIECE_PAWN);
    assert(moves->white.dest.x == 'e');
    assert(moves->white.dest.y == 4);
    assert(moves->white.captures == false);
    assert(moves->white.annotation == PGN_ANNOTATION_NONE);
    assert(moves->black.piece == PGN_PIECE_PAWN);
    assert(moves->black.dest.x == 'e');
    assert(moves->black.dest.y == 5);
    assert(moves->black.captures == false);
    assert(moves->black.annotation == PGN_ANNOTATION_NONE);
    assert(moves->alternatives.length == 0);
    __pgn_moves_cleanup(moves);

    __print_success();
}

int main(void)
{
    test_parsing_move();
    putchar('\n');
    test_parsing_bunch_of_moves();
    return 0;
}
