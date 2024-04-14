#ifndef __LIBPGN_STRING_H
#define __LIBPGN_STRING_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define PGN_STRING_INITIAL_SIZE 64
#define PGN_STRING_GROW_SIZE 32

typedef struct pgn_string_t {
    char *buf;
    size_t length;
    size_t size;
} pgn_string_t;

pgn_string_t *pgn_string_init();
void pgn_string_reset(pgn_string_t *pstr);
bool pgn_string_equal(pgn_string_t *pstr, char *str);
void pgn_string_append(pgn_string_t *pstr, char ch);
void pgn_string_append_null_terminator(pgn_string_t *pstr);
void pgn_string_concat(pgn_string_t *pstr, char *str);
void pgn_string_cleanup(pgn_string_t *pstr);

#endif // __LIBPGN_STRING_H
