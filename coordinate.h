#ifndef __LIBPGN_COORDINATE_H
#define __LIBPGN_COORDINATE_H

typedef struct pgn_coordinate_t {
    int x, y;
} pgn_coordinate_t;

char pgn_coordinate_as_alphabet(int n);
int pgn_coordinate_as_number(char n);

#endif // __LIBPGN_COORDINATE_H
