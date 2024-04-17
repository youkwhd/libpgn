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

int main(void)
{
    test_parsing_move();
    return 0;
}
