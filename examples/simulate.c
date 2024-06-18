#include <signal.h>
#include <ctype.h>
#include <pgn.h>
#include <stdbool.h>
#include <stdio.h>

/* TODOs & Missing features:
 *  - No way of knowing if a piece is pinned
 *      this is useful when the pgn file states a piece PIECE move,
 *      and there's ambigous 2 pieces that could move to the destination (one is pinned one isn't).
 *
 *  - No logic for:
 *      - Queen moves
 *      - King moves
 */

#define PGN_FILEPATH "examples/record.pgn"

#define CHESS_BOARD_WIDTH 8
#define CHESS_BOARD_HEIGHT 8

#define BUFFER_SIZE 1024
#define ARRAY_SIZE(arr) (sizeof((arr)) / sizeof((arr)[0]))

#define COOR_INSIDE_BOARD(x, y) ((x) >= 0 && (x) < CHESS_BOARD_WIDTH) && ((y) >= 0 && (y) < CHESS_BOARD_HEIGHT)

typedef enum player {
    WHITE = 0,
    BLACK,
} player;

typedef pgn_coordinate_t coordinate;

bool is_piece_player_eq(player pl, char piece)
{
    return (pl == WHITE && isupper(piece)) || (pl == BLACK && islower(piece));
}

bool is_move_possible(char board[CHESS_BOARD_HEIGHT][CHESS_BOARD_WIDTH], player pl, int x, int y, pgn_move_t move)
{
    int dest_x = move.dest.x - 'a', dest_y = -(move.dest.y - CHESS_BOARD_HEIGHT);

    switch (move.piece) {
    case PGN_PIECE_UNKNOWN: return false;
    case PGN_PIECE_PAWN:
        if (pl == WHITE) {
            if (COOR_INSIDE_BOARD(x, y - 1) && x == dest_x && y - 1 == dest_y) return true;
            if (COOR_INSIDE_BOARD(x, y - 2) && x == dest_x && y - 2 == dest_y) return true;

            if (move.captures && !is_piece_player_eq(pl, board[y - 1][x - 1]) && COOR_INSIDE_BOARD(x - 1, y - 1) && x - 1 == dest_x && y - 1 == dest_y) return true;
            if (move.captures && !is_piece_player_eq(pl, board[y - 1][x + 1]) && COOR_INSIDE_BOARD(x + 1, y - 1) && x + 1 == dest_x && y - 1 == dest_y) return true;

            // e.p.
            if (move.en_passant && COOR_INSIDE_BOARD(x - 1, y - 1) && x - 1 == dest_x && y - 1 == dest_y) return true;
            if (move.en_passant && COOR_INSIDE_BOARD(x + 1, y - 1) && x + 1 == dest_x && y - 1 == dest_y) return true;
        }

        if (pl == BLACK) {
            if (COOR_INSIDE_BOARD(x, y + 1) && x == dest_x && y + 1 == dest_y) return true;
            if (COOR_INSIDE_BOARD(x, y + 2) && x == dest_x && y + 2 == dest_y) return true;

            if (move.captures && !is_piece_player_eq(pl, board[y + 1][x - 1]) && COOR_INSIDE_BOARD(x - 1, y + 1) && x - 1 == dest_x && y + 1 == dest_y) return true;
            if (move.captures && !is_piece_player_eq(pl, board[y + 1][x + 1]) && COOR_INSIDE_BOARD(x + 1, y + 1) && x + 1 == dest_x && y + 1 == dest_y) return true;

            // e.p.
            if (move.en_passant && COOR_INSIDE_BOARD(x - 1, y + 1) && x - 1 == dest_x && y + 1 == dest_y) return true;
            if (move.en_passant && COOR_INSIDE_BOARD(x + 1, y + 1) && x + 1 == dest_x && y + 1 == dest_y) return true;
        }

        break;
    case PGN_PIECE_ROOK:
        for (int i = 0; i < CHESS_BOARD_HEIGHT; i++) {
            if (i == y) continue;
            if (board[i][x] != ' ' && is_piece_player_eq(pl, board[i][x])) break;
            if (COOR_INSIDE_BOARD(x, i) && x == dest_x && i == dest_y) return true;
        }

        for (int i = 0; i < CHESS_BOARD_WIDTH; i++) {
            if (i == x) continue;
            if (board[i][x] != ' ' && is_piece_player_eq(pl, board[i][x])) break;
            if (COOR_INSIDE_BOARD(i, y) && i == dest_x && y == dest_y) return true;
        }

        break;
    case PGN_PIECE_KNIGHT:
        if (!is_piece_player_eq(pl, board[y + 2][x - 1]) && x - 1 == dest_x && y + 2 == dest_y) return true;
        if (!is_piece_player_eq(pl, board[y + 2][x + 1]) && x + 1 == dest_x && y + 2 == dest_y) return true;

        if (!is_piece_player_eq(pl, board[y + 1][x - 2]) && x - 2 == dest_x && y + 1 == dest_y) return true;
        if (!is_piece_player_eq(pl, board[y + 1][x + 2]) && x + 2 == dest_x && y + 1 == dest_y) return true;

        if (!is_piece_player_eq(pl, board[y - 2][x - 1]) && x - 1 == dest_x && y - 2 == dest_y) return true;
        if (!is_piece_player_eq(pl, board[y - 2][x + 1]) && x + 1 == dest_x && y - 2 == dest_y) return true;

        if (!is_piece_player_eq(pl, board[y - 1][x - 2]) && x - 2 == dest_x && y - 1 == dest_y) return true;
        if (!is_piece_player_eq(pl, board[y - 1][x + 2]) && x + 2 == dest_x && y - 1 == dest_y) return true;

        break;
    case PGN_PIECE_BISHOP:
        for (int i = 1; i < CHESS_BOARD_HEIGHT; i++) {
            if (COOR_INSIDE_BOARD(x + i, y + i) && x + i == dest_x && y + i == dest_y) return true;
            if (COOR_INSIDE_BOARD(x + i, y - i) && x + i == dest_x && y - i == dest_y) return true;
            if (COOR_INSIDE_BOARD(x - i, y - i) && x - i == dest_x && y - i == dest_y) return true;
            if (COOR_INSIDE_BOARD(x - i, y + i) && x - i == dest_x && y + i == dest_y) return true;
        }

        break;
    case PGN_PIECE_QUEEN:
        fprintf(stderr, "Queen move is not implemented yet.\n");
        exit(1);
        break;
    case PGN_PIECE_KING:
        fprintf(stderr, "King move is not implemented yet.\n");
        exit(1);
        break;
    }

    return false;
}

void move(char board[CHESS_BOARD_HEIGHT][CHESS_BOARD_WIDTH], player pl, pgn_move_t move)
{
    if (move.castles) {
        switch (move.castles) {
        case PGN_CASTLING_KINGSIDE:
            switch (pl) {
            case WHITE:
                board[7][4] = ' ';
                board[7][5] = pgn_piece_to_char(PGN_PIECE_ROOK);
                board[7][6] = pgn_piece_to_char(PGN_PIECE_KING);
                board[7][7] = ' ';
                break;
            case BLACK:
                board[0][4] = ' ';
                board[0][5] = tolower(pgn_piece_to_char(PGN_PIECE_ROOK));
                board[0][6] = tolower(pgn_piece_to_char(PGN_PIECE_KING));
                board[0][7] = ' ';
                break;
            }
            break;
        case PGN_CASTLING_QUEENSIDE:
            switch (pl) {
            case WHITE:
                board[7][0] = ' ';
                board[7][2] = pgn_piece_to_char(PGN_PIECE_KING);
                board[7][3] = pgn_piece_to_char(PGN_PIECE_ROOK);
                board[7][5] = ' ';
                break;
            case BLACK:
                board[0][0] = ' ';
                board[0][2] = tolower(pgn_piece_to_char(PGN_PIECE_KING));
                board[0][3] = tolower(pgn_piece_to_char(PGN_PIECE_ROOK));
                board[0][5] = ' ';
                break;
            }
            break;
        }

        return;
    }

    for (int i = 0; i < CHESS_BOARD_HEIGHT; i++) {
        for (int j = 0; j < CHESS_BOARD_WIDTH; j++) {
            if (toupper(board[i][j]) != pgn_piece_to_char(move.piece))
                continue;

            if (!is_piece_player_eq(pl, board[i][j]))
                continue;

            int x = j, y = -(i - CHESS_BOARD_HEIGHT) - 1;
            if (move.from.y != PGN_COORDINATE_UNKNOWN && y != move.from.y - 1 ||
                move.from.x != PGN_COORDINATE_UNKNOWN && x != move.from.x - 'a')
                continue;

            if (!is_move_possible(board, pl, j, i, move))
                continue;

            board[-(move.dest.y - CHESS_BOARD_HEIGHT)][move.dest.x - 'a'] = board[i][j];
            board[i][j] = ' ';

            if (move.en_passant) {
                board[-(move.dest.y - CHESS_BOARD_HEIGHT) + (pl == WHITE ? 1 : -1)][move.dest.x - 'a'] = ' ';
            }

            return;
        }
    }
}

void print_board(char board[CHESS_BOARD_HEIGHT][CHESS_BOARD_WIDTH])
{
    for (int i = 0; i < CHESS_BOARD_HEIGHT; i++) {
        printf("%d ", -(i - CHESS_BOARD_HEIGHT));

        for (int j = 0; j < CHESS_BOARD_WIDTH; j++) {
            printf("%c ", board[i][j]);
        }

        printf("\n");
    }

    printf("  ");
    for (int i = 0 ; i < CHESS_BOARD_WIDTH; i++) {
        printf("%c ", 'a' + i);
    }
}

/* Needed to be global for signal handling
 */
pgn_t *pgn = NULL;

void __on_interrupted(int sig)
{
    (void)sig;
    pgn_cleanup(pgn);
    exit(0);
}

int main(void)
{
    char buffer[BUFFER_SIZE] = {0};
    char board[CHESS_BOARD_HEIGHT][CHESS_BOARD_WIDTH] = {
        { 'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r' },
        { 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p' },
        { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
        { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
        { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
        { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },
        { 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P' },
        { 'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R' },
    };

    FILE *fp = fopen(PGN_FILEPATH, "r");
    fread(buffer, sizeof(*buffer), BUFFER_SIZE, fp);
    fclose(fp);

    pgn = pgn_init();
    pgn_parse(pgn, buffer);
    /* pgn_parse(pgn, "1. e4 e5 2. Nf3 Nc6 3. Bb5 {This opening is called the Ruy Lopez.} 3... a6 4. Ba4 Nf6 5. O-O Be7 6. Re1 b5 7. Bb3 d6 8. c3 O-O 9. h3 Nb8 10. d4 Nbd7 11. c4 c6 12. cxb5 axb5 13. Nc3 Bb7 14. Bg5 b4 15. Nb1 h6 16. Bh4 c5 17. dxe5 Nxe4"); */

    signal(SIGINT, __on_interrupted);

    for (int i = 0; i < (int)pgn->moves->length; i++) {
        move(board, WHITE, pgn->moves->values[i].white);
        printf("\n");
        print_board(board);
        getchar();

        move(board, BLACK, pgn->moves->values[i].black);
        printf("\n");
        print_board(board);
        getchar();
    }

    printf("\n%d %d\n", pgn->score.white, pgn->score.black);
    pgn_cleanup(pgn);
    return 0;
}
