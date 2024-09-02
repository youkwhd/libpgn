#ifndef __LIBPGN_COORDINATE_H
#define __LIBPGN_COORDINATE_H

#define PGN_COORDINATE_UNKNOWN 0

typedef struct pgn_coordinate_t {
    char file;
    int rank;
} pgn_coordinate_t;

int pgn_coordinate_file_as_index(char file);

#endif // __LIBPGN_COORDINATE_H
