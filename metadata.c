#include "metadata.h"

#include <stdio.h>
#include <assert.h>

pgn_metadata_t *__pgn_metadata_from_string(char *str, size_t *consumed)
{
    size_t cursor = 0;

    /* Redundant check, but it works to not make unnecessary
     * memory allocations (key_buf, value_buf)
     */
    if (str[cursor] != '[') return NULL;

    pgn_metadata_t *metadata = pgn_metadata_init();
    pgn_string_t *key_buffer = pgn_string_init();
    pgn_string_t *value_buffer = pgn_string_init();

    for (;;) {
        if (str[cursor] != '[') break;
        cursor++;

        while (str[cursor] != ' ') pgn_string_append(key_buffer, str[cursor++]);
        pgn_string_append_null_terminator(key_buffer);

        assert(str[++cursor] == '"');
        cursor++;

        while (str[cursor] != '"') pgn_string_append(value_buffer, str[cursor++]);
        pgn_string_append_null_terminator(value_buffer);

        pgn_metadata_insert(metadata, key_buffer->buf, value_buffer->buf);
        pgn_string_reset(key_buffer);
        pgn_string_reset(value_buffer);

        assert(str[++cursor] == ']');
        /* TODO: maybe expect whitespaces than just newline
         */
        assert(str[++cursor] == '\n');
        cursor++;
    }

    *consumed += cursor;
    pgn_string_cleanup(key_buffer);
    pgn_string_cleanup(value_buffer);
    return metadata;
}

pgn_metadata_t *pgn_metadata_from_string(char *str)
{
    size_t consumed = 0;
    return __pgn_metadata_from_string(str, &consumed);
}

void __pgn_metadata_item_init(__pgn_metadata_item_t *item)
{
    item->key = pgn_string_init();
    item->value = pgn_string_init();
}

void __pgn_metadata_item_cleanup(__pgn_metadata_item_t *item)
{
    pgn_string_cleanup(item->key);
    pgn_string_cleanup(item->value);
}

pgn_metadata_t *pgn_metadata_init(void)
{
    pgn_metadata_t *metadata = malloc(sizeof *metadata);
    metadata->items = malloc((sizeof *metadata->items) * PGN_METADATA_INITIAL_SIZE);
    metadata->size = PGN_METADATA_INITIAL_SIZE;
    metadata->length = 0;
    return metadata;
}

void pgn_metadata_printp(pgn_metadata_t *metadata)
{
    for (size_t i = 0; i < metadata->length; i++) {
        printf("[%s \"%s\"]\n", metadata->items[i].key->buf, metadata->items[i].value->buf);
    }
}

void pgn_metadata_insert(pgn_metadata_t *metadata, char *key, char *value)
{
    if (metadata->length >= metadata->size) {
        metadata->size += PGN_METADATA_GROW_SIZE;
        metadata->items = realloc(metadata->items, (sizeof *metadata->items) * metadata->size);
    }

    __pgn_metadata_item_t item = {0};
    __pgn_metadata_item_init(&item);

    pgn_string_concat(item.key, key);
    pgn_string_concat(item.value, value);

    metadata->items[metadata->length++] = item;
}

char *pgn_metadata_get(pgn_metadata_t *metadata, char *key)
{
    for (size_t i = 0; i < metadata->length; i++) {
        if (pgn_string_equal(metadata->items[i].key, key)) {
            return metadata->items[i].value->buf;
        }
    }

    return NULL;
}

void pgn_metadata_delete(pgn_metadata_t *metadata, char *key)
{
    for (size_t i = 0; i < metadata->length; i++) {
        if (!pgn_string_equal(metadata->items[i].key, key)) {
            continue;
        }

        __pgn_metadata_item_cleanup(&metadata->items[i]);

        for (size_t j = i; j < metadata->length - 1; j++) {
            metadata->items[j] = metadata->items[j + 1];
        }

        metadata->length--;
        break;
    }
}

void pgn_metadata_cleanup(pgn_metadata_t *metadata)
{
    for (size_t i = 0; i < metadata->length; i++) {
        __pgn_metadata_item_cleanup(&metadata->items[i]);
    }

    free(metadata->items);
    free(metadata);
}
