#ifndef __LIBPGN_TABLE_H
#define __LIBPGN_TABLE_H

#include "export.h"
#include "piece.h"
#include "string.h"

#include <stdlib.h>

#define PGN_TABLE_INITIAL_SIZE 7
#define PGN_TABLE_GROW_SIZE 7

typedef struct __pgn_table_item_t {
    pgn_string_t *key;
    pgn_string_t *value;
} __pgn_table_item_t;

typedef struct pgn_table_t {
    __pgn_table_item_t *items;
    size_t length, size;
} pgn_table_t;

PGN_EXPORT void __pgn_table_item_init(__pgn_table_item_t *item);
PGN_EXPORT void __pgn_table_item_cleanup(__pgn_table_item_t *item);

PGN_EXPORT pgn_table_t *pgn_table_init();
PGN_EXPORT pgn_table_t *__pgn_table_from_string(char *str, size_t *consumed);
PGN_EXPORT pgn_table_t *pgn_table_from_string(char *str);
PGN_EXPORT void pgn_table_printp(pgn_table_t *table);
PGN_EXPORT void pgn_table_insert(pgn_table_t *table, char *key, char *value);
PGN_EXPORT char *pgn_table_get(pgn_table_t *table, char *key);
PGN_EXPORT void pgn_table_delete(pgn_table_t *table, char *key);
PGN_EXPORT void pgn_table_cleanup(pgn_table_t *table);

#endif // __LIBPGN_TABLE_H
