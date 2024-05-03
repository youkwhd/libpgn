#include <pgn.h>
#include <stdio.h>
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
    assert(move.check == PGN_CHECK_NONE);
    assert(move.annotation == PGN_ANNOTATION_BLUNDER);
    __print_success();

    move = pgn_move_from_string("Qf1?!");
    assert(move.piece == PGN_PIECE_QUEEN);
    assert(move.captures == false);
    assert(move.from.x == PGN_COORDINATE_UNKNOWN);
    assert(move.from.y == PGN_COORDINATE_UNKNOWN);
    assert(move.dest.x == 'f');
    assert(move.dest.y == 1);
    assert(move.check == PGN_CHECK_NONE);
    assert(move.annotation == PGN_ANNOTATION_DUBIOUS_MOVE);
    __print_success();

    move = pgn_move_from_string("bxa8=Q??");
    assert(move.piece == PGN_PIECE_PAWN);
    assert(move.captures == true);
    assert(move.from.x == 'b');
    assert(move.from.y == PGN_COORDINATE_UNKNOWN);
    assert(move.dest.x == 'a');
    assert(move.dest.y == 8);
    assert(move.check == PGN_CHECK_NONE);
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
    assert(move.check == PGN_CHECK_NONE);
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
    assert(move.check == PGN_CHECK_SINGLE);
    assert(move.promoted_to == PGN_PIECE_UNKNOWN);
    assert(move.annotation == PGN_ANNOTATION_GOOD_MOVE);
    __print_success();

    move = pgn_move_from_string("O-O+!!");
    assert(move.castles == PGN_CASTLING_KINGSIDE);
    assert(move.check == PGN_CHECK_SINGLE);
    assert(move.annotation == PGN_ANNOTATION_EXCELLENT_MOVE);
    __print_success();

    move = pgn_move_from_string("O-O-O");
    assert(move.castles == PGN_CASTLING_QUEENSIDE);
    assert(move.check == PGN_CHECK_NONE);
    assert(move.annotation == PGN_ANNOTATION_NONE);
    __print_success();
}

void test_parsing_bunch_of_moves()
{
    printf("calling %s()\n", __func__);
    __nth = 1;
    pgn_moves_t *moves = NULL;

    moves = pgn_moves_from_string("1.e4 e5");
    assert(moves->values[0]->white.piece == PGN_PIECE_PAWN);
    assert(moves->values[0]->white.dest.x == 'e');
    assert(moves->values[0]->white.dest.y == 4);
    assert(moves->values[0]->white.captures == false);
    assert(moves->values[0]->white.annotation == PGN_ANNOTATION_NONE);
    assert(moves->values[0]->black.piece == PGN_PIECE_PAWN);
    assert(moves->values[0]->black.dest.x == 'e');
    assert(moves->values[0]->black.dest.y == 5);
    assert(moves->values[0]->black.captures == false);
    assert(moves->values[0]->black.annotation == PGN_ANNOTATION_NONE);
    assert(moves->values[0]->alternatives == NULL);
    pgn_moves_cleanup(moves);
    __print_success();

    moves = pgn_moves_from_string("1.e4 $2 e5 $1");
    assert(moves->values[0]->white.piece == PGN_PIECE_PAWN);
    assert(moves->values[0]->white.dest.x == 'e');
    assert(moves->values[0]->white.dest.y == 4);
    assert(moves->values[0]->white.captures == false);
    assert(moves->values[0]->white.annotation == PGN_ANNOTATION_NONE);
    assert(moves->values[0]->white.nth_best == 2);
    assert(moves->values[0]->black.piece == PGN_PIECE_PAWN);
    assert(moves->values[0]->black.dest.x == 'e');
    assert(moves->values[0]->black.dest.y == 5);
    assert(moves->values[0]->black.captures == false);
    assert(moves->values[0]->black.annotation == PGN_ANNOTATION_NONE);
    assert(moves->values[0]->black.nth_best == 1);
    assert(moves->values[0]->alternatives == NULL);
    pgn_moves_cleanup(moves);
    __print_success();

    moves = pgn_moves_from_string("69.Be4 69... Rxe5?!");
    assert(moves->values[0]->white.piece == PGN_PIECE_BISHOP);
    assert(moves->values[0]->white.dest.x == 'e');
    assert(moves->values[0]->white.dest.y == 4);
    assert(moves->values[0]->white.captures == false);
    assert(moves->values[0]->white.annotation == PGN_ANNOTATION_NONE);
    assert(moves->values[0]->black.piece == PGN_PIECE_ROOK);
    assert(moves->values[0]->black.dest.x == 'e');
    assert(moves->values[0]->black.dest.y == 5);
    assert(moves->values[0]->black.captures == true);
    assert(moves->values[0]->black.annotation == PGN_ANNOTATION_DUBIOUS_MOVE);
    assert(moves->values[0]->alternatives == NULL);
    pgn_moves_cleanup(moves);
    __print_success();

    moves = pgn_moves_from_string("9.e4 { This is a comment :O } e5 10. Nc3 Nc6");
    assert(moves->values[0]->white.piece == PGN_PIECE_PAWN);
    assert(moves->values[0]->white.dest.x == 'e');
    assert(moves->values[0]->white.dest.y == 4);
    assert(moves->values[0]->white.captures == false);
    assert(moves->values[0]->white.annotation == PGN_ANNOTATION_NONE);
    assert(moves->values[0]->black.piece == PGN_PIECE_PAWN);
    assert(moves->values[0]->black.dest.x == 'e');
    assert(moves->values[0]->black.dest.y == 5);
    assert(moves->values[0]->black.captures == false);
    assert(moves->values[0]->black.annotation == PGN_ANNOTATION_NONE);
    assert(moves->values[0]->alternatives == NULL);

    assert(moves->values[1]->white.piece == PGN_PIECE_KNIGHT);
    assert(moves->values[1]->white.dest.x == 'c');
    assert(moves->values[1]->white.dest.y == 3);
    assert(moves->values[1]->white.captures == false);
    assert(moves->values[1]->white.annotation == PGN_ANNOTATION_NONE);
    assert(moves->values[1]->black.piece == PGN_PIECE_KNIGHT);
    assert(moves->values[1]->black.dest.x == 'c');
    assert(moves->values[1]->black.dest.y == 6);
    assert(moves->values[1]->black.captures == false);
    assert(moves->values[1]->black.annotation == PGN_ANNOTATION_NONE);
    assert(moves->values[0]->alternatives == NULL);
    pgn_moves_cleanup(moves);
    __print_success();

    moves = pgn_moves_from_string("69.Be4 ( 69. Be2 69... e4 ) 69... Rxe5?!");
    assert(moves->values[0]->white.piece == PGN_PIECE_BISHOP);
    assert(moves->values[0]->white.dest.x == 'e');
    assert(moves->values[0]->white.dest.y == 4);
    assert(moves->values[0]->white.captures == false);
    assert(moves->values[0]->white.annotation == PGN_ANNOTATION_NONE);
    assert(moves->values[0]->black.piece == PGN_PIECE_ROOK);
    assert(moves->values[0]->black.dest.x == 'e');
    assert(moves->values[0]->black.dest.y == 5);
    assert(moves->values[0]->black.captures == true);
    assert(moves->values[0]->black.annotation == PGN_ANNOTATION_DUBIOUS_MOVE);
    assert(moves->values[0]->alternatives);

    assert(moves->values[0]->alternatives->values[0]->white.piece == PGN_PIECE_BISHOP);
    assert(moves->values[0]->alternatives->values[0]->white.dest.x == 'e');
    assert(moves->values[0]->alternatives->values[0]->white.dest.y == 2);
    assert(moves->values[0]->alternatives->values[0]->white.captures == false);
    assert(moves->values[0]->alternatives->values[0]->white.annotation == PGN_ANNOTATION_NONE);
    assert(moves->values[0]->alternatives->values[0]->black.piece == PGN_PIECE_PAWN);
    assert(moves->values[0]->alternatives->values[0]->black.dest.x == 'e');
    assert(moves->values[0]->alternatives->values[0]->black.dest.y == 4);
    assert(moves->values[0]->alternatives->values[0]->black.captures == false);
    assert(moves->values[0]->alternatives->values[0]->black.annotation == PGN_ANNOTATION_NONE);
    assert(moves->values[0]->alternatives->values[0]->alternatives == NULL);
    pgn_moves_cleanup(moves);
    __print_success();

    moves = pgn_moves_from_string("69.Be4 69... Rxe5?! ( 69. e5 69... e4 )");
    assert(moves->values[0]->white.piece == PGN_PIECE_BISHOP);
    assert(moves->values[0]->white.dest.x == 'e');
    assert(moves->values[0]->white.dest.y == 4);
    assert(moves->values[0]->white.captures == false);
    assert(moves->values[0]->white.annotation == PGN_ANNOTATION_NONE);
    assert(moves->values[0]->black.piece == PGN_PIECE_ROOK);
    assert(moves->values[0]->black.dest.x == 'e');
    assert(moves->values[0]->black.dest.y == 5);
    assert(moves->values[0]->black.captures == true);
    assert(moves->values[0]->black.annotation == PGN_ANNOTATION_DUBIOUS_MOVE);
    assert(moves->values[0]->alternatives);

    assert(moves->values[0]->alternatives->values[0]->white.piece == PGN_PIECE_PAWN);
    assert(moves->values[0]->alternatives->values[0]->white.dest.x == 'e');
    assert(moves->values[0]->alternatives->values[0]->white.dest.y == 5);
    assert(moves->values[0]->alternatives->values[0]->white.captures == false);
    assert(moves->values[0]->alternatives->values[0]->white.annotation == PGN_ANNOTATION_NONE);
    assert(moves->values[0]->alternatives->values[0]->alternatives == NULL);

    assert(moves->values[0]->alternatives->values[0]->black.piece == PGN_PIECE_PAWN);
    assert(moves->values[0]->alternatives->values[0]->black.dest.x == 'e');
    assert(moves->values[0]->alternatives->values[0]->black.dest.y == 4);
    assert(moves->values[0]->alternatives->values[0]->black.captures == false);
    assert(moves->values[0]->alternatives->values[0]->black.annotation == PGN_ANNOTATION_NONE);
    assert(moves->values[0]->alternatives->values[0]->alternatives == NULL);
    pgn_moves_cleanup(moves);
    __print_success();
}

void test_parsing_real_games()
{
    printf("calling %s()\n", __func__);
    __nth = 1;
    pgn_moves_t *moves = NULL;

    moves = pgn_moves_from_string("1.c4 ( 1.e4  ) c5 2.Nc3 Nc6");
    assert(moves->values[0]->white.piece == PGN_PIECE_PAWN);
    assert(moves->values[0]->white.dest.x == 'c');
    assert(moves->values[0]->white.dest.y == 4);
    assert(moves->values[0]->white.captures == false);
    assert(moves->values[0]->white.annotation == PGN_ANNOTATION_NONE);
    assert(moves->values[0]->black.piece == PGN_PIECE_PAWN);
    assert(moves->values[0]->black.dest.x == 'c');
    assert(moves->values[0]->black.dest.y == 5);
    assert(moves->values[0]->black.captures == false);
    assert(moves->values[0]->black.annotation == PGN_ANNOTATION_NONE);

    assert(moves->values[0]->alternatives->values[0]->white.piece == PGN_PIECE_PAWN);
    assert(moves->values[0]->alternatives->values[0]->white.dest.x == 'e');
    assert(moves->values[0]->alternatives->values[0]->white.dest.y == 4);
    assert(moves->values[0]->alternatives->values[0]->white.captures == false);
    assert(moves->values[0]->alternatives->values[0]->white.annotation == PGN_ANNOTATION_NONE);
    assert(moves->values[0]->alternatives->values[0]->alternatives == NULL);

    assert(moves->values[1]->white.piece == PGN_PIECE_KNIGHT);
    assert(moves->values[1]->white.dest.x == 'c');
    assert(moves->values[1]->white.dest.y == 3);
    assert(moves->values[1]->white.captures == false);
    assert(moves->values[1]->white.annotation == PGN_ANNOTATION_NONE);
    assert(moves->values[1]->alternatives == NULL);

    assert(moves->values[1]->black.piece == PGN_PIECE_KNIGHT);
    assert(moves->values[1]->black.dest.x == 'c');
    assert(moves->values[1]->black.dest.y == 6);
    assert(moves->values[1]->black.captures == false);
    assert(moves->values[1]->black.annotation == PGN_ANNOTATION_NONE);
    assert(moves->values[1]->alternatives == NULL);
    pgn_moves_cleanup(moves);
    __print_success();

    moves = pgn_moves_from_string("1.c4 ( 1.e4  ) c5 2.Nc3 Nc6 1/2-1/2");
    assert(moves->values[0]->white.piece == PGN_PIECE_PAWN);
    assert(moves->values[0]->white.dest.x == 'c');
    assert(moves->values[0]->white.dest.y == 4);
    assert(moves->values[0]->white.captures == false);
    assert(moves->values[0]->white.annotation == PGN_ANNOTATION_NONE);
    assert(moves->values[0]->black.piece == PGN_PIECE_PAWN);
    assert(moves->values[0]->black.dest.x == 'c');
    assert(moves->values[0]->black.dest.y == 5);
    assert(moves->values[0]->black.captures == false);
    assert(moves->values[0]->black.annotation == PGN_ANNOTATION_NONE);

    assert(moves->values[0]->alternatives->values[0]->white.piece == PGN_PIECE_PAWN);
    assert(moves->values[0]->alternatives->values[0]->white.dest.x == 'e');
    assert(moves->values[0]->alternatives->values[0]->white.dest.y == 4);
    assert(moves->values[0]->alternatives->values[0]->white.captures == false);
    assert(moves->values[0]->alternatives->values[0]->white.annotation == PGN_ANNOTATION_NONE);
    assert(moves->values[0]->alternatives->values[0]->alternatives == NULL);

    assert(moves->values[1]->white.piece == PGN_PIECE_KNIGHT);
    assert(moves->values[1]->white.dest.x == 'c');
    assert(moves->values[1]->white.dest.y == 3);
    assert(moves->values[1]->white.captures == false);
    assert(moves->values[1]->white.annotation == PGN_ANNOTATION_NONE);
    assert(moves->values[1]->alternatives == NULL);

    assert(moves->values[1]->black.piece == PGN_PIECE_KNIGHT);
    assert(moves->values[1]->black.dest.x == 'c');
    assert(moves->values[1]->black.dest.y == 6);
    assert(moves->values[1]->black.captures == false);
    assert(moves->values[1]->black.annotation == PGN_ANNOTATION_NONE);
    assert(moves->values[1]->alternatives == NULL);
    pgn_moves_cleanup(moves);
    __print_success();
}

void test_parsing_en_passant()
{
    printf("calling %s()\n", __func__);
    __nth = 1;

    pgn_move_t move = pgn_move_from_string("exd6 e.p.");
    assert(move.piece == PGN_PIECE_PAWN);
    assert(move.from.x == 'e');
    assert(move.dest.x == 'd');
    assert(move.dest.y == 6);
    assert(move.captures);
    __print_success();

    pgn_moves_t *moves = pgn_moves_from_string("1. d4 exd3 e.p. 2.  Nc4 Nc6 3. cxb3 e.p. 3... Be4");
    assert(moves->values[0]->white.piece == PGN_PIECE_PAWN);
    assert(moves->values[0]->white.dest.x == 'd');
    assert(moves->values[0]->white.dest.y == 4);
    assert(moves->values[0]->black.piece == PGN_PIECE_PAWN);
    assert(moves->values[0]->black.from.x == 'e');
    assert(moves->values[0]->black.dest.x == 'd');
    assert(moves->values[0]->black.dest.y == 3);

    assert(moves->values[1]->white.piece == PGN_PIECE_KNIGHT);
    assert(moves->values[1]->white.dest.x == 'c');
    assert(moves->values[1]->white.dest.y == 4);
    assert(moves->values[1]->black.piece == PGN_PIECE_KNIGHT);
    assert(moves->values[1]->black.dest.x == 'c');
    assert(moves->values[1]->black.dest.y == 6);

    assert(moves->values[2]->white.piece == PGN_PIECE_PAWN);
    assert(moves->values[2]->white.from.x == 'c');
    assert(moves->values[2]->white.dest.x == 'b');
    assert(moves->values[2]->white.dest.y == 3);
    assert(moves->values[2]->black.piece == PGN_PIECE_BISHOP);
    assert(moves->values[2]->black.dest.x == 'e');
    assert(moves->values[2]->black.dest.y == 4);
    pgn_moves_cleanup(moves);
    __print_success();
}

int main(void)
{
    test_parsing_move();
    putchar('\n');
    test_parsing_bunch_of_moves();
    putchar('\n');
    test_parsing_real_games();
    putchar('\n');
    test_parsing_en_passant();
    putchar('\n');
    return 0;
}
