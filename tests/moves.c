#include "extra/suite6.h"

#include <pgn.h>
#include <string.h>

void test_parsing_single_move()
{
    pgn_move_t move = {0};

    move = pgn_parse_move("e4??");
    suite6_assert(move.piece == PGN_PIECE_PAWN);
    suite6_assert(move.captures == false);
    suite6_assert(move.from.x == PGN_COORDINATE_UNKNOWN);
    suite6_assert(move.from.y == PGN_COORDINATE_UNKNOWN);
    suite6_assert(move.dest.x == 'e');
    suite6_assert(move.dest.y == 4);
    suite6_assert(move.check == PGN_CHECK_NONE);
    suite6_assert(!strcmp(move.notation, "e4??"));
    suite6_assert(move.annotation == PGN_ANNOTATION_BLUNDER);

    move = pgn_parse_move("Nb6d5+");
    suite6_assert(move.piece == PGN_PIECE_KNIGHT);
    suite6_assert(move.captures == false);
    suite6_assert(move.from.x == 'b');
    suite6_assert(move.from.y == 6);
    suite6_assert(move.dest.x == 'd');
    suite6_assert(move.dest.y == 5);
    suite6_assert(move.check == PGN_CHECK_SINGLE);
    suite6_assert(!strcmp(move.notation, "Nb6d5+"));
    suite6_assert(move.annotation == PGN_ANNOTATION_NONE);

    move = pgn_parse_move("Qf1?!");
    suite6_assert(move.piece == PGN_PIECE_QUEEN);
    suite6_assert(move.captures == false);
    suite6_assert(move.from.x == PGN_COORDINATE_UNKNOWN);
    suite6_assert(move.from.y == PGN_COORDINATE_UNKNOWN);
    suite6_assert(move.dest.x == 'f');
    suite6_assert(move.dest.y == 1);
    suite6_assert(move.check == PGN_CHECK_NONE);
    suite6_assert(!strcmp(move.notation, "Qf1?!"));
    suite6_assert(move.annotation == PGN_ANNOTATION_DUBIOUS_MOVE);

    move = pgn_parse_move("bxa8=Q??");
    suite6_assert(move.piece == PGN_PIECE_PAWN);
    suite6_assert(move.captures == true);
    suite6_assert(move.from.x == 'b');
    suite6_assert(move.from.y == PGN_COORDINATE_UNKNOWN);
    suite6_assert(move.dest.x == 'a');
    suite6_assert(move.dest.y == 8);
    suite6_assert(move.check == PGN_CHECK_NONE);
    suite6_assert(move.promoted_to == PGN_PIECE_QUEEN);
    suite6_assert(!strcmp(move.notation, "bxa8=Q??"));
    suite6_assert(move.annotation == PGN_ANNOTATION_BLUNDER);

    move = pgn_parse_move("Bxg2");
    suite6_assert(move.piece == PGN_PIECE_BISHOP);
    suite6_assert(move.captures == true);
    suite6_assert(move.from.x == PGN_COORDINATE_UNKNOWN);
    suite6_assert(move.from.y == PGN_COORDINATE_UNKNOWN);
    suite6_assert(move.dest.x == 'g');
    suite6_assert(move.dest.y == 2);
    suite6_assert(move.check == PGN_CHECK_NONE);
    suite6_assert(move.promoted_to == PGN_PIECE_UNKNOWN);
    suite6_assert(!strcmp(move.notation, "Bxg2"));
    suite6_assert(move.annotation == PGN_ANNOTATION_NONE);

    move = pgn_parse_move("exf2+!");
    suite6_assert(move.piece == PGN_PIECE_PAWN);
    suite6_assert(move.captures == true);
    suite6_assert(move.from.x == 'e');
    suite6_assert(move.from.y == PGN_COORDINATE_UNKNOWN);
    suite6_assert(move.dest.x == 'f');
    suite6_assert(move.dest.y == 2);
    suite6_assert(move.check == PGN_CHECK_SINGLE);
    suite6_assert(move.promoted_to == PGN_PIECE_UNKNOWN);
    suite6_assert(!strcmp(move.notation, "exf2+!"));
    suite6_assert(move.annotation == PGN_ANNOTATION_GOOD_MOVE);

    move = pgn_parse_move("O-O+!!");
    suite6_assert(move.castles == PGN_CASTLING_KINGSIDE);
    suite6_assert(move.check == PGN_CHECK_SINGLE);
    suite6_assert(!strcmp(move.notation, "O-O+!!"));
    suite6_assert(move.annotation == PGN_ANNOTATION_EXCELLENT_MOVE);

    move = pgn_parse_move("O-O-O");
    suite6_assert(move.castles == PGN_CASTLING_QUEENSIDE);
    suite6_assert(move.check == PGN_CHECK_NONE);
    suite6_assert(!strcmp(move.notation, "O-O-O"));
    suite6_assert(move.annotation == PGN_ANNOTATION_NONE);
}

void test_parsing_bunch_of_moves()
{
    pgn_moves_t *moves = NULL;

    moves = pgn_parse_moves("1.e4 e5");
    suite6_assert(strcmp(moves->values[0].white.notation, "e4") == 0);
    suite6_assert(moves->values[0].white.piece == PGN_PIECE_PAWN);
    suite6_assert(moves->values[0].white.dest.x == 'e');
    suite6_assert(moves->values[0].white.dest.y == 4);
    suite6_assert(moves->values[0].white.captures == false);
    suite6_assert(moves->values[0].white.annotation == PGN_ANNOTATION_NONE);
    suite6_assert(strcmp(moves->values[0].black.notation, "e5") == 0);
    suite6_assert(moves->values[0].black.piece == PGN_PIECE_PAWN);
    suite6_assert(moves->values[0].black.dest.x == 'e');
    suite6_assert(moves->values[0].black.dest.y == 5);
    suite6_assert(moves->values[0].black.captures == false);
    suite6_assert(moves->values[0].black.annotation == PGN_ANNOTATION_NONE);
    suite6_assert(moves->values[0].alternatives == NULL);
    pgn_moves_cleanup(moves);

    moves = pgn_parse_moves("1.e4 $2 e5 $1");
    suite6_assert(moves->values[0].white.piece == PGN_PIECE_PAWN);
    suite6_assert(moves->values[0].white.dest.x == 'e');
    suite6_assert(moves->values[0].white.dest.y == 4);
    suite6_assert(moves->values[0].white.captures == false);
    suite6_assert(moves->values[0].white.annotation == PGN_ANNOTATION_NONE);
    suite6_assert(moves->values[0].white.nth_best == 2);
    suite6_assert(moves->values[0].black.piece == PGN_PIECE_PAWN);
    suite6_assert(moves->values[0].black.dest.x == 'e');
    suite6_assert(moves->values[0].black.dest.y == 5);
    suite6_assert(moves->values[0].black.captures == false);
    suite6_assert(moves->values[0].black.annotation == PGN_ANNOTATION_NONE);
    suite6_assert(moves->values[0].black.nth_best == 1);
    suite6_assert(moves->values[0].alternatives == NULL);
    pgn_moves_cleanup(moves);

    moves = pgn_parse_moves("69.Be4 69... Rxe5?!");
    suite6_assert(moves->values[0].white.piece == PGN_PIECE_BISHOP);
    suite6_assert(moves->values[0].white.dest.x == 'e');
    suite6_assert(moves->values[0].white.dest.y == 4);
    suite6_assert(moves->values[0].white.captures == false);
    suite6_assert(moves->values[0].white.annotation == PGN_ANNOTATION_NONE);
    suite6_assert(moves->values[0].black.piece == PGN_PIECE_ROOK);
    suite6_assert(moves->values[0].black.dest.x == 'e');
    suite6_assert(moves->values[0].black.dest.y == 5);
    suite6_assert(moves->values[0].black.captures == true);
    suite6_assert(moves->values[0].black.annotation == PGN_ANNOTATION_DUBIOUS_MOVE);
    suite6_assert(moves->values[0].alternatives == NULL);
    pgn_moves_cleanup(moves);

    moves = pgn_parse_moves("9.e4 { This is a comment :O } e5 10. Nc3 Nc6");
    suite6_assert(moves->values[0].white.piece == PGN_PIECE_PAWN);
    suite6_assert(moves->values[0].white.dest.x == 'e');
    suite6_assert(moves->values[0].white.dest.y == 4);
    suite6_assert(moves->values[0].white.captures == false);
    suite6_assert(moves->values[0].white.annotation == PGN_ANNOTATION_NONE);
    suite6_assert(moves->values[0].black.piece == PGN_PIECE_PAWN);
    suite6_assert(moves->values[0].black.dest.x == 'e');
    suite6_assert(moves->values[0].black.dest.y == 5);
    suite6_assert(moves->values[0].black.captures == false);
    suite6_assert(moves->values[0].black.annotation == PGN_ANNOTATION_NONE);
    suite6_assert(moves->values[0].alternatives == NULL);

    suite6_assert(moves->values[1].white.piece == PGN_PIECE_KNIGHT);
    suite6_assert(moves->values[1].white.dest.x == 'c');
    suite6_assert(moves->values[1].white.dest.y == 3);
    suite6_assert(moves->values[1].white.captures == false);
    suite6_assert(moves->values[1].white.annotation == PGN_ANNOTATION_NONE);
    suite6_assert(moves->values[1].black.piece == PGN_PIECE_KNIGHT);
    suite6_assert(moves->values[1].black.dest.x == 'c');
    suite6_assert(moves->values[1].black.dest.y == 6);
    suite6_assert(moves->values[1].black.captures == false);
    suite6_assert(moves->values[1].black.annotation == PGN_ANNOTATION_NONE);
    suite6_assert(moves->values[0].alternatives == NULL);
    pgn_moves_cleanup(moves);

    moves = pgn_parse_moves("69.Be4 ( 69. Be2 69... e4 ) 69... Rxe5?!");
    suite6_assert(moves->values[0].white.piece == PGN_PIECE_BISHOP);
    suite6_assert(moves->values[0].white.dest.x == 'e');
    suite6_assert(moves->values[0].white.dest.y == 4);
    suite6_assert(moves->values[0].white.captures == false);
    suite6_assert(moves->values[0].white.annotation == PGN_ANNOTATION_NONE);
    suite6_assert(moves->values[0].black.piece == PGN_PIECE_ROOK);
    suite6_assert(moves->values[0].black.dest.x == 'e');
    suite6_assert(moves->values[0].black.dest.y == 5);
    suite6_assert(moves->values[0].black.captures == true);
    suite6_assert(moves->values[0].black.annotation == PGN_ANNOTATION_DUBIOUS_MOVE);
    suite6_assert(moves->values[0].alternatives);

    suite6_assert(moves->values[0].alternatives->values[0].white.piece == PGN_PIECE_BISHOP);
    suite6_assert(moves->values[0].alternatives->values[0].white.dest.x == 'e');
    suite6_assert(moves->values[0].alternatives->values[0].white.dest.y == 2);
    suite6_assert(moves->values[0].alternatives->values[0].white.captures == false);
    suite6_assert(moves->values[0].alternatives->values[0].white.annotation == PGN_ANNOTATION_NONE);
    suite6_assert(moves->values[0].alternatives->values[0].black.piece == PGN_PIECE_PAWN);
    suite6_assert(moves->values[0].alternatives->values[0].black.dest.x == 'e');
    suite6_assert(moves->values[0].alternatives->values[0].black.dest.y == 4);
    suite6_assert(moves->values[0].alternatives->values[0].black.captures == false);
    suite6_assert(moves->values[0].alternatives->values[0].black.annotation == PGN_ANNOTATION_NONE);
    suite6_assert(moves->values[0].alternatives->values[0].alternatives == NULL);
    pgn_moves_cleanup(moves);

    moves = pgn_parse_moves("69.Be4 69... Rxe5?! ( 69. e5 69... e4 )");
    suite6_assert(moves->values[0].white.piece == PGN_PIECE_BISHOP);
    suite6_assert(moves->values[0].white.dest.x == 'e');
    suite6_assert(moves->values[0].white.dest.y == 4);
    suite6_assert(moves->values[0].white.captures == false);
    suite6_assert(moves->values[0].white.annotation == PGN_ANNOTATION_NONE);
    suite6_assert(moves->values[0].black.piece == PGN_PIECE_ROOK);
    suite6_assert(moves->values[0].black.dest.x == 'e');
    suite6_assert(moves->values[0].black.dest.y == 5);
    suite6_assert(moves->values[0].black.captures == true);
    suite6_assert(moves->values[0].black.annotation == PGN_ANNOTATION_DUBIOUS_MOVE);
    suite6_assert(moves->values[0].alternatives);

    suite6_assert(moves->values[0].alternatives->values[0].white.piece == PGN_PIECE_PAWN);
    suite6_assert(moves->values[0].alternatives->values[0].white.dest.x == 'e');
    suite6_assert(moves->values[0].alternatives->values[0].white.dest.y == 5);
    suite6_assert(moves->values[0].alternatives->values[0].white.captures == false);
    suite6_assert(moves->values[0].alternatives->values[0].white.annotation == PGN_ANNOTATION_NONE);
    suite6_assert(moves->values[0].alternatives->values[0].alternatives == NULL);

    suite6_assert(moves->values[0].alternatives->values[0].black.piece == PGN_PIECE_PAWN);
    suite6_assert(moves->values[0].alternatives->values[0].black.dest.x == 'e');
    suite6_assert(moves->values[0].alternatives->values[0].black.dest.y == 4);
    suite6_assert(moves->values[0].alternatives->values[0].black.captures == false);
    suite6_assert(moves->values[0].alternatives->values[0].black.annotation == PGN_ANNOTATION_NONE);
    suite6_assert(moves->values[0].alternatives->values[0].alternatives == NULL);
    pgn_moves_cleanup(moves);
}

void test_parsing_moves_with_score()
{
    pgn_moves_t *moves = NULL;

    moves = pgn_parse_moves("1.c4 ( 1.e4  ) c5 2.Nc3 Nc6");
    suite6_assert(moves->values[0].white.piece == PGN_PIECE_PAWN);
    suite6_assert(moves->values[0].white.dest.x == 'c');
    suite6_assert(moves->values[0].white.dest.y == 4);
    suite6_assert(moves->values[0].white.captures == false);
    suite6_assert(moves->values[0].white.annotation == PGN_ANNOTATION_NONE);
    suite6_assert(moves->values[0].black.piece == PGN_PIECE_PAWN);
    suite6_assert(moves->values[0].black.dest.x == 'c');
    suite6_assert(moves->values[0].black.dest.y == 5);
    suite6_assert(moves->values[0].black.captures == false);
    suite6_assert(moves->values[0].black.annotation == PGN_ANNOTATION_NONE);

    suite6_assert(moves->values[0].alternatives->values[0].white.piece == PGN_PIECE_PAWN);
    suite6_assert(moves->values[0].alternatives->values[0].white.dest.x == 'e');
    suite6_assert(moves->values[0].alternatives->values[0].white.dest.y == 4);
    suite6_assert(moves->values[0].alternatives->values[0].white.captures == false);
    suite6_assert(moves->values[0].alternatives->values[0].white.annotation == PGN_ANNOTATION_NONE);
    suite6_assert(moves->values[0].alternatives->values[0].alternatives == NULL);

    suite6_assert(moves->values[1].white.piece == PGN_PIECE_KNIGHT);
    suite6_assert(moves->values[1].white.dest.x == 'c');
    suite6_assert(moves->values[1].white.dest.y == 3);
    suite6_assert(moves->values[1].white.captures == false);
    suite6_assert(moves->values[1].white.annotation == PGN_ANNOTATION_NONE);
    suite6_assert(moves->values[1].alternatives == NULL);

    suite6_assert(moves->values[1].black.piece == PGN_PIECE_KNIGHT);
    suite6_assert(moves->values[1].black.dest.x == 'c');
    suite6_assert(moves->values[1].black.dest.y == 6);
    suite6_assert(moves->values[1].black.captures == false);
    suite6_assert(moves->values[1].black.annotation == PGN_ANNOTATION_NONE);
    suite6_assert(moves->values[1].alternatives == NULL);
    pgn_moves_cleanup(moves);

    moves = pgn_parse_moves("1.c4 ( 1.e4  ) c5 2.Nc3 Nc6 1/2-1/2");
    suite6_assert(moves->values[0].white.piece == PGN_PIECE_PAWN);
    suite6_assert(moves->values[0].white.dest.x == 'c');
    suite6_assert(moves->values[0].white.dest.y == 4);
    suite6_assert(moves->values[0].white.captures == false);
    suite6_assert(moves->values[0].white.annotation == PGN_ANNOTATION_NONE);
    suite6_assert(moves->values[0].black.piece == PGN_PIECE_PAWN);
    suite6_assert(moves->values[0].black.dest.x == 'c');
    suite6_assert(moves->values[0].black.dest.y == 5);
    suite6_assert(moves->values[0].black.captures == false);
    suite6_assert(moves->values[0].black.annotation == PGN_ANNOTATION_NONE);

    suite6_assert(moves->values[0].alternatives->values[0].white.piece == PGN_PIECE_PAWN);
    suite6_assert(moves->values[0].alternatives->values[0].white.dest.x == 'e');
    suite6_assert(moves->values[0].alternatives->values[0].white.dest.y == 4);
    suite6_assert(moves->values[0].alternatives->values[0].white.captures == false);
    suite6_assert(moves->values[0].alternatives->values[0].white.annotation == PGN_ANNOTATION_NONE);
    suite6_assert(moves->values[0].alternatives->values[0].alternatives == NULL);

    suite6_assert(moves->values[1].white.piece == PGN_PIECE_KNIGHT);
    suite6_assert(moves->values[1].white.dest.x == 'c');
    suite6_assert(moves->values[1].white.dest.y == 3);
    suite6_assert(moves->values[1].white.captures == false);
    suite6_assert(moves->values[1].white.annotation == PGN_ANNOTATION_NONE);
    suite6_assert(moves->values[1].alternatives == NULL);

    suite6_assert(moves->values[1].black.piece == PGN_PIECE_KNIGHT);
    suite6_assert(moves->values[1].black.dest.x == 'c');
    suite6_assert(moves->values[1].black.dest.y == 6);
    suite6_assert(moves->values[1].black.captures == false);
    suite6_assert(moves->values[1].black.annotation == PGN_ANNOTATION_NONE);
    suite6_assert(moves->values[1].alternatives == NULL);
    pgn_moves_cleanup(moves);
}

void test_parsing_en_passant()
{
    pgn_move_t move = pgn_parse_move("exd6 e.p.");
    suite6_assert(move.piece == PGN_PIECE_PAWN);
    suite6_assert(move.from.x == 'e');
    suite6_assert(move.dest.x == 'd');
    suite6_assert(move.dest.y == 6);
    suite6_assert(move.captures);

    pgn_moves_t *moves = pgn_parse_moves("1. d4 exd3 e.p. 2.  Nc4 Nc6 3. cxb3 e.p. 3... Be4");
    suite6_assert(moves->values[0].white.piece == PGN_PIECE_PAWN);
    suite6_assert(moves->values[0].white.dest.x == 'd');
    suite6_assert(moves->values[0].white.dest.y == 4);
    suite6_assert(moves->values[0].black.piece == PGN_PIECE_PAWN);
    suite6_assert(moves->values[0].black.from.x == 'e');
    suite6_assert(moves->values[0].black.dest.x == 'd');
    suite6_assert(moves->values[0].black.dest.y == 3);

    suite6_assert(moves->values[1].white.piece == PGN_PIECE_KNIGHT);
    suite6_assert(moves->values[1].white.dest.x == 'c');
    suite6_assert(moves->values[1].white.dest.y == 4);
    suite6_assert(moves->values[1].black.piece == PGN_PIECE_KNIGHT);
    suite6_assert(moves->values[1].black.dest.x == 'c');
    suite6_assert(moves->values[1].black.dest.y == 6);

    suite6_assert(moves->values[2].white.piece == PGN_PIECE_PAWN);
    suite6_assert(moves->values[2].white.from.x == 'c');
    suite6_assert(moves->values[2].white.dest.x == 'b');
    suite6_assert(moves->values[2].white.dest.y == 3);
    suite6_assert(moves->values[2].black.piece == PGN_PIECE_BISHOP);
    suite6_assert(moves->values[2].black.dest.x == 'e');
    suite6_assert(moves->values[2].black.dest.y == 4);
    pgn_moves_cleanup(moves);
}

int main(void)
{
    test_parsing_single_move();
    test_parsing_bunch_of_moves();
    test_parsing_moves_with_score();
    test_parsing_en_passant();
    return 0;
}
