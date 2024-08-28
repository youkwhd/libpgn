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
    suite6_assert(move.annotation == PGN_ANNOTATION_NULL);

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
    suite6_assert(move.annotation == PGN_ANNOTATION_NULL);

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
    suite6_assert(move.annotation == PGN_ANNOTATION_BRILLIANT_MOVE);

    move = pgn_parse_move("O-O-O");
    suite6_assert(move.castles == PGN_CASTLING_QUEENSIDE);
    suite6_assert(move.check == PGN_CHECK_NONE);
    suite6_assert(!strcmp(move.notation, "O-O-O"));
    suite6_assert(move.annotation == PGN_ANNOTATION_NULL);
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
    suite6_assert(moves->values[0].white.annotation == PGN_ANNOTATION_NULL);
    suite6_assert(strcmp(moves->values[0].black.notation, "e5") == 0);
    suite6_assert(moves->values[0].black.piece == PGN_PIECE_PAWN);
    suite6_assert(moves->values[0].black.dest.x == 'e');
    suite6_assert(moves->values[0].black.dest.y == 5);
    suite6_assert(moves->values[0].black.captures == false);
    suite6_assert(moves->values[0].black.annotation == PGN_ANNOTATION_NULL);
    pgn_moves_cleanup(moves);

    moves = pgn_parse_moves("1.e4 $2 e5 $1");
    suite6_assert(moves->values[0].white.piece == PGN_PIECE_PAWN);
    suite6_assert(moves->values[0].white.dest.x == 'e');
    suite6_assert(moves->values[0].white.dest.y == 4);
    suite6_assert(moves->values[0].white.captures == false);
    suite6_assert(moves->values[0].white.annotation == 2);
    suite6_assert(moves->values[0].black.piece == PGN_PIECE_PAWN);
    suite6_assert(moves->values[0].black.dest.x == 'e');
    suite6_assert(moves->values[0].black.dest.y == 5);
    suite6_assert(moves->values[0].black.captures == false);
    suite6_assert(moves->values[0].black.annotation == 1);
    pgn_moves_cleanup(moves);

    moves = pgn_parse_moves("69.Be4 69... Rxe5?!");
    suite6_assert(moves->values[0].white.piece == PGN_PIECE_BISHOP);
    suite6_assert(moves->values[0].white.dest.x == 'e');
    suite6_assert(moves->values[0].white.dest.y == 4);
    suite6_assert(moves->values[0].white.captures == false);
    suite6_assert(moves->values[0].white.annotation == PGN_ANNOTATION_NULL);
    suite6_assert(moves->values[0].black.piece == PGN_PIECE_ROOK);
    suite6_assert(moves->values[0].black.dest.x == 'e');
    suite6_assert(moves->values[0].black.dest.y == 5);
    suite6_assert(moves->values[0].black.captures == true);
    suite6_assert(moves->values[0].black.annotation == PGN_ANNOTATION_DUBIOUS_MOVE);
    pgn_moves_cleanup(moves);

    moves = pgn_parse_moves("9.e4 { This is a comment :O } e5 10. Nc3 Nc6");
    suite6_assert(moves->values[0].white.comments->length == 1);
    suite6_assert(!strcmp(moves->values[0].white.comments->values[0].value->buf, " This is a comment :O "));
    suite6_assert(moves->values[0].white.comments->values[0].position == PGN_COMMENT_POSITION_AFTER_MOVE);
    suite6_assert(moves->values[0].white.piece == PGN_PIECE_PAWN);
    suite6_assert(moves->values[0].white.dest.x == 'e');
    suite6_assert(moves->values[0].white.dest.y == 4);
    suite6_assert(moves->values[0].white.captures == false);
    suite6_assert(moves->values[0].white.annotation == PGN_ANNOTATION_NULL);
    suite6_assert(moves->values[0].black.piece == PGN_PIECE_PAWN);
    suite6_assert(moves->values[0].black.dest.x == 'e');
    suite6_assert(moves->values[0].black.dest.y == 5);
    suite6_assert(moves->values[0].black.captures == false);
    suite6_assert(moves->values[0].black.annotation == PGN_ANNOTATION_NULL);

    suite6_assert(moves->values[1].white.piece == PGN_PIECE_KNIGHT);
    suite6_assert(moves->values[1].white.dest.x == 'c');
    suite6_assert(moves->values[1].white.dest.y == 3);
    suite6_assert(moves->values[1].white.captures == false);
    suite6_assert(moves->values[1].white.annotation == PGN_ANNOTATION_NULL);
    suite6_assert(moves->values[1].black.piece == PGN_PIECE_KNIGHT);
    suite6_assert(moves->values[1].black.dest.x == 'c');
    suite6_assert(moves->values[1].black.dest.y == 6);
    suite6_assert(moves->values[1].black.captures == false);
    suite6_assert(moves->values[1].black.annotation == PGN_ANNOTATION_NULL);
    pgn_moves_cleanup(moves);

    moves = pgn_parse_moves("69.Be4 ( 69. Be2 69... e4 ) 69... Rxe5?!");
    suite6_assert(moves->values[0].white.piece == PGN_PIECE_BISHOP);
    suite6_assert(moves->values[0].white.dest.x == 'e');
    suite6_assert(moves->values[0].white.dest.y == 4);
    suite6_assert(moves->values[0].white.captures == false);
    suite6_assert(moves->values[0].white.annotation == PGN_ANNOTATION_NULL);
    suite6_assert(moves->values[0].black.piece == PGN_PIECE_ROOK);
    suite6_assert(moves->values[0].black.dest.x == 'e');
    suite6_assert(moves->values[0].black.dest.y == 5);
    suite6_assert(moves->values[0].black.captures == true);
    suite6_assert(moves->values[0].black.annotation == PGN_ANNOTATION_DUBIOUS_MOVE);
    suite6_assert(moves->values[0].white.alternatives);

    suite6_assert(moves->values[0].white.alternatives->values[0]->values[0].white.piece == PGN_PIECE_BISHOP);
    suite6_assert(moves->values[0].white.alternatives->values[0]->values[0].white.dest.x == 'e');
    suite6_assert(moves->values[0].white.alternatives->values[0]->values[0].white.dest.y == 2);
    suite6_assert(moves->values[0].white.alternatives->values[0]->values[0].white.captures == false);
    suite6_assert(moves->values[0].white.alternatives->values[0]->values[0].white.annotation == PGN_ANNOTATION_NULL);
    suite6_assert(moves->values[0].white.alternatives->values[0]->values[0].black.piece == PGN_PIECE_PAWN);
    suite6_assert(moves->values[0].white.alternatives->values[0]->values[0].black.dest.x == 'e');
    suite6_assert(moves->values[0].white.alternatives->values[0]->values[0].black.dest.y == 4);
    suite6_assert(moves->values[0].white.alternatives->values[0]->values[0].black.captures == false);
    suite6_assert(moves->values[0].white.alternatives->values[0]->values[0].black.annotation == PGN_ANNOTATION_NULL);
    pgn_moves_cleanup(moves);

    moves = pgn_parse_moves("69.Be4 69... Rxe5?! ( 69. e5 69... e4 )");
    suite6_assert(moves->values[0].white.piece == PGN_PIECE_BISHOP);
    suite6_assert(moves->values[0].white.dest.x == 'e');
    suite6_assert(moves->values[0].white.dest.y == 4);
    suite6_assert(moves->values[0].white.captures == false);
    suite6_assert(moves->values[0].white.annotation == PGN_ANNOTATION_NULL);
    suite6_assert(moves->values[0].black.piece == PGN_PIECE_ROOK);
    suite6_assert(moves->values[0].black.dest.x == 'e');
    suite6_assert(moves->values[0].black.dest.y == 5);
    suite6_assert(moves->values[0].black.captures == true);
    suite6_assert(moves->values[0].black.annotation == PGN_ANNOTATION_DUBIOUS_MOVE);
    suite6_assert(moves->values[0].black.alternatives);

    suite6_assert(moves->values[0].black.alternatives->values[0]->values[0].white.piece == PGN_PIECE_PAWN);
    suite6_assert(moves->values[0].black.alternatives->values[0]->values[0].white.dest.x == 'e');
    suite6_assert(moves->values[0].black.alternatives->values[0]->values[0].white.dest.y == 5);
    suite6_assert(moves->values[0].black.alternatives->values[0]->values[0].white.captures == false);
    suite6_assert(moves->values[0].black.alternatives->values[0]->values[0].white.annotation == PGN_ANNOTATION_NULL);

    suite6_assert(moves->values[0].black.alternatives->values[0]->values[0].black.piece == PGN_PIECE_PAWN);
    suite6_assert(moves->values[0].black.alternatives->values[0]->values[0].black.dest.x == 'e');
    suite6_assert(moves->values[0].black.alternatives->values[0]->values[0].black.dest.y == 4);
    suite6_assert(moves->values[0].black.alternatives->values[0]->values[0].black.captures == false);
    suite6_assert(moves->values[0].black.alternatives->values[0]->values[0].black.annotation == PGN_ANNOTATION_NULL);
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
    suite6_assert(moves->values[0].white.annotation == PGN_ANNOTATION_NULL);
    suite6_assert(moves->values[0].black.piece == PGN_PIECE_PAWN);
    suite6_assert(moves->values[0].black.dest.x == 'c');
    suite6_assert(moves->values[0].black.dest.y == 5);
    suite6_assert(moves->values[0].black.captures == false);
    suite6_assert(moves->values[0].black.annotation == PGN_ANNOTATION_NULL);

    suite6_assert(moves->values[0].white.alternatives->values[0]->values[0].white.piece == PGN_PIECE_PAWN);
    suite6_assert(moves->values[0].white.alternatives->values[0]->values[0].white.dest.x == 'e');
    suite6_assert(moves->values[0].white.alternatives->values[0]->values[0].white.dest.y == 4);
    suite6_assert(moves->values[0].white.alternatives->values[0]->values[0].white.captures == false);
    suite6_assert(moves->values[0].white.alternatives->values[0]->values[0].white.annotation == PGN_ANNOTATION_NULL);

    suite6_assert(moves->values[1].white.piece == PGN_PIECE_KNIGHT);
    suite6_assert(moves->values[1].white.dest.x == 'c');
    suite6_assert(moves->values[1].white.dest.y == 3);
    suite6_assert(moves->values[1].white.captures == false);
    suite6_assert(moves->values[1].white.annotation == PGN_ANNOTATION_NULL);

    suite6_assert(moves->values[1].black.piece == PGN_PIECE_KNIGHT);
    suite6_assert(moves->values[1].black.dest.x == 'c');
    suite6_assert(moves->values[1].black.dest.y == 6);
    suite6_assert(moves->values[1].black.captures == false);
    suite6_assert(moves->values[1].black.annotation == PGN_ANNOTATION_NULL);
    pgn_moves_cleanup(moves);

    moves = pgn_parse_moves("1.c4 ( 1.e4  ) c5 2.Nc3 Nc6 1/2-1/2");
    suite6_assert(moves->values[0].white.piece == PGN_PIECE_PAWN);
    suite6_assert(moves->values[0].white.dest.x == 'c');
    suite6_assert(moves->values[0].white.dest.y == 4);
    suite6_assert(moves->values[0].white.captures == false);
    suite6_assert(moves->values[0].white.annotation == PGN_ANNOTATION_NULL);
    suite6_assert(moves->values[0].black.piece == PGN_PIECE_PAWN);
    suite6_assert(moves->values[0].black.dest.x == 'c');
    suite6_assert(moves->values[0].black.dest.y == 5);
    suite6_assert(moves->values[0].black.captures == false);
    suite6_assert(moves->values[0].black.annotation == PGN_ANNOTATION_NULL);

    suite6_assert(moves->values[0].white.alternatives->values[0]->values[0].white.piece == PGN_PIECE_PAWN);
    suite6_assert(moves->values[0].white.alternatives->values[0]->values[0].white.dest.x == 'e');
    suite6_assert(moves->values[0].white.alternatives->values[0]->values[0].white.dest.y == 4);
    suite6_assert(moves->values[0].white.alternatives->values[0]->values[0].white.captures == false);
    suite6_assert(moves->values[0].white.alternatives->values[0]->values[0].white.annotation == PGN_ANNOTATION_NULL);

    suite6_assert(moves->values[1].white.piece == PGN_PIECE_KNIGHT);
    suite6_assert(moves->values[1].white.dest.x == 'c');
    suite6_assert(moves->values[1].white.dest.y == 3);
    suite6_assert(moves->values[1].white.captures == false);
    suite6_assert(moves->values[1].white.annotation == PGN_ANNOTATION_NULL);

    suite6_assert(moves->values[1].black.piece == PGN_PIECE_KNIGHT);
    suite6_assert(moves->values[1].black.dest.x == 'c');
    suite6_assert(moves->values[1].black.dest.y == 6);
    suite6_assert(moves->values[1].black.captures == false);
    suite6_assert(moves->values[1].black.annotation == PGN_ANNOTATION_NULL);
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

void test_parsing_moves_with_alternatives()
{
    pgn_moves_t *moves = NULL;

    moves = pgn_moves_from_string("1. e4 e5 (1. f4? e5! 2. g4?? Qh4#)");
    suite6_assert(moves->length == 1);
    suite6_assert(moves->values[0].black.alternatives->length == 1);
    suite6_assert(!strcmp(moves->values[0].black.alternatives->values[0]->values[0].white.notation, "f4?"));
    suite6_assert(!strcmp(moves->values[0].black.alternatives->values[0]->values[0].black.notation, "e5!"));
    suite6_assert(!strcmp(moves->values[0].black.alternatives->values[0]->values[1].white.notation, "g4??"));
    suite6_assert(!strcmp(moves->values[0].black.alternatives->values[0]->values[1].black.notation, "Qh4#"));
    pgn_moves_cleanup(moves);

    moves = pgn_moves_from_string("1. e4 e5 (1. f4? e5! 2. g4?? Qh4#) (1. e4 f6? 2. d4 g5?? 3. Qh5#)");
    suite6_assert(moves->length == 1);
    suite6_assert(moves->values[0].black.alternatives->length == 2);
    suite6_assert(!strcmp(moves->values[0].black.alternatives->values[0]->values[0].white.notation, "f4?"));
    suite6_assert(!strcmp(moves->values[0].black.alternatives->values[0]->values[0].black.notation, "e5!"));
    suite6_assert(!strcmp(moves->values[0].black.alternatives->values[0]->values[1].white.notation, "g4??"));
    suite6_assert(!strcmp(moves->values[0].black.alternatives->values[0]->values[1].black.notation, "Qh4#"));
    suite6_assert(!strcmp(moves->values[0].black.alternatives->values[1]->values[0].white.notation, "e4"));
    suite6_assert(!strcmp(moves->values[0].black.alternatives->values[1]->values[0].black.notation, "f6?"));
    suite6_assert(!strcmp(moves->values[0].black.alternatives->values[1]->values[1].white.notation, "d4"));
    suite6_assert(!strcmp(moves->values[0].black.alternatives->values[1]->values[1].black.notation, "g5??"));
    suite6_assert(!strcmp(moves->values[0].black.alternatives->values[1]->values[2].white.notation, "Qh5#"));
    pgn_moves_cleanup(moves);

    moves = pgn_moves_from_string("1. e4 e5 (1. f4? e5! 2. g4?? Qh4#) 2. Nc6 Nf4");
    suite6_assert(moves->length == 2);
    suite6_assert(moves->values[0].black.alternatives->length == 1);
    suite6_assert(!strcmp(moves->values[0].black.alternatives->values[0]->values[0].white.notation, "f4?"));
    suite6_assert(!strcmp(moves->values[0].black.alternatives->values[0]->values[0].black.notation, "e5!"));
    suite6_assert(!strcmp(moves->values[0].black.alternatives->values[0]->values[1].white.notation, "g4??"));
    suite6_assert(!strcmp(moves->values[0].black.alternatives->values[0]->values[1].black.notation, "Qh4#"));
    suite6_assert(!strcmp(moves->values[1].white.notation, "Nc6"));
    suite6_assert(!strcmp(moves->values[1].black.notation, "Nf4"));
    pgn_moves_cleanup(moves);
}

int main(void)
{
    test_parsing_single_move();
    test_parsing_bunch_of_moves();
    test_parsing_moves_with_score();
    test_parsing_en_passant();
    test_parsing_moves_with_alternatives();
    return 0;
}
