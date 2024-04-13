#ifndef __LIBPGN_TABLE_H
#define __LIBPGN_TABLE_H

#include "piece.h"
#include <stdlib.h>

#define PGN_TABLE_INITIAL_SIZE 7
#define PGN_TABLE_GROW_SIZE 7

typedef struct __pgn_table_item_t {
    char *key;
    char *value;
} __pgn_table_item_t;

typedef struct pgn_table_t {
    __pgn_table_item_t *items;
    size_t length, size;
} pgn_table_t;

void pgn_table_init(pgn_table_t *table);
void pgn_table_printp(pgn_table_t *table);
void pgn_table_insert(pgn_table_t *table, char *key, char *value);
char *pgn_table_get(pgn_table_t *table, char *key);
void pgn_table_cleanup(pgn_table_t *table);

#endif // __LIBPGN_TABLE_H
