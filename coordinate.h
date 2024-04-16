#ifndef __LIBPGN_COORDINATE_H
#define __LIBPGN_COORDINATE_H

typedef struct pgn_coordinate_t {
    char x;
    int y;
} pgn_coordinate_t;

char pgn_coordinate_as_char(int n);
int pgn_coordinate_as_int(char n);

#endif // __LIBPGN_COORDINATE_H
