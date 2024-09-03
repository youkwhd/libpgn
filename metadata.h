#ifndef __LIBPGN_METADATA_H
#define __LIBPGN_METADATA_H

#include "piece.h"
#include "utils/export.h"
#include "utils/buffer.h"

#include <stddef.h>

#define PGN_METADATA_INITIAL_SIZE 8
#define PGN_METADATA_GROW_SIZE 8

typedef struct __pgn_metadata_item_t {
    pgn_buffer_t *key;
    pgn_buffer_t *value;
} __pgn_metadata_item_t;

typedef struct pgn_metadata_t {
    __pgn_metadata_item_t *items;
    size_t length, size;
} pgn_metadata_t;

void __pgn_metadata_item_init(__pgn_metadata_item_t *item);
void __pgn_metadata_item_cleanup(__pgn_metadata_item_t *item);

PGN_EXPORT pgn_metadata_t *pgn_metadata_init(void);
PGN_EXPORT pgn_metadata_t *__pgn_metadata_from_string(char *str, size_t *consumed);
PGN_EXPORT pgn_metadata_t *pgn_metadata_from_string(char *str);
PGN_EXPORT void pgn_metadata_printp(pgn_metadata_t *metadata);
PGN_EXPORT void pgn_metadata_insert(pgn_metadata_t *metadata, char *key, char *value);
PGN_EXPORT char *pgn_metadata_get(pgn_metadata_t *metadata, char *key);
PGN_EXPORT void pgn_metadata_delete(pgn_metadata_t *metadata, char *key);
PGN_EXPORT void pgn_metadata_cleanup(pgn_metadata_t *metadata);

#endif // __LIBPGN_METADATA_H
