#ifndef __LIBpgn_buffer_H
#define __LIBpgn_buffer_H

#include <stdlib.h>
#include <stdbool.h>

#define pgn_buffer_INITIAL_SIZE 16
#define pgn_buffer_GROW_SIZE 32

typedef struct pgn_buffer_t {
    char *buf;
    size_t length;
    size_t size;
} pgn_buffer_t;

pgn_buffer_t *pgn_buffer_init(void);
void pgn_buffer_grow(pgn_buffer_t *buf);
void pgn_buffer_reset(pgn_buffer_t *buf);
bool pgn_buffer_equal(pgn_buffer_t *buf, char *str);
void pgn_buffer_append(pgn_buffer_t *buf, char ch);
void pgn_buffer_append_null_terminator(pgn_buffer_t *buf);
void pgn_buffer_concat(pgn_buffer_t *buf, char *str);
void pgn_buffer_cleanup(pgn_buffer_t *buf);

#endif // __LIBpgn_buffer_H
