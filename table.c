#include "table.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>

void __pgn_table_from_metadata_string(pgn_table_t *table, char *str, size_t *consumed)
{
    /* Redundant check, but it works to not make unnecessary
     * memory allocations (key_buf, value_buf)
     */
    if (str[*consumed] != '[') return;

    pgn_string_t *key_buffer = pgn_string_init();
    pgn_string_t *value_buffer = pgn_string_init();

    for (;;) {
        if (str[*consumed] != '[') goto cleanup;
        (*consumed)++;

        while (str[*consumed] != ' ') pgn_string_append(key_buffer, str[(*consumed)++]);
        pgn_string_append_null_terminator(key_buffer);

        assert(str[++(*consumed)] == '"');
        (*consumed)++;

        while (str[*consumed] != '"') pgn_string_append(value_buffer, str[(*consumed)++]);
        pgn_string_append_null_terminator(value_buffer);

        pgn_table_insert(table, key_buffer->buf, value_buffer->buf);
        pgn_string_reset(key_buffer);
        pgn_string_reset(value_buffer);

        assert(str[++(*consumed)] == ']');
        /* TODO: maybe expect whitespaces than just newline
         */
        assert(str[++(*consumed)] == '\n');
        (*consumed)++;
    }

cleanup:
    pgn_string_cleanup(key_buffer);
    pgn_string_cleanup(value_buffer);
}

void pgn_table_from_metadata_string(pgn_table_t *table, char *str)
{
    size_t consumed = 0;
    __pgn_table_from_metadata_string(table, str, &consumed);
}

__pgn_table_item_t *__pgn_table_item_init()
{
    __pgn_table_item_t *item = malloc(sizeof *item);
    item->key = pgn_string_init();
    item->value = pgn_string_init();
    return item;
}

void __pgn_table_item_cleanup(__pgn_table_item_t *item)
{
    pgn_string_cleanup(item->key);
    pgn_string_cleanup(item->value);
    free(item);
}

pgn_table_t *pgn_table_init()
{
    pgn_table_t *table = malloc(sizeof *table);
    table->items = malloc((sizeof *table->items) * PGN_TABLE_INITIAL_SIZE);
    table->size = PGN_TABLE_INITIAL_SIZE;
    table->length = 0;
    return table;
}

void pgn_table_printp(pgn_table_t *table)
{
    for (size_t i = 0; i < table->length; i++) {
        printf("[%s \"%s\"]\n", table->items[i]->key->buf, table->items[i]->value->buf);
    }
}

void pgn_table_insert(pgn_table_t *table, char *key, char *value)
{
    if (table->length >= table->size) {
        table->size += PGN_TABLE_GROW_SIZE;
        table->items = realloc(table->items, table->size);
    }

    __pgn_table_item_t *item = __pgn_table_item_init();
    pgn_string_concat(item->key, key);
    pgn_string_concat(item->value, value);

    table->items[table->length++] = item;
}

char *pgn_table_get(pgn_table_t *table, char *key)
{
    for (size_t i = 0; i < table->length; i++) {
        if (pgn_string_equal(table->items[i]->key, key)) {
            return table->items[i]->value->buf;
        }
    }

    return NULL;
}

void pgn_table_delete(pgn_table_t *table, char *key)
{
    for (size_t i = 0; i < table->length; i++) {
        if (!pgn_string_equal(table->items[i]->key, key)) {
            continue;
        }

        __pgn_table_item_cleanup(table->items[i]);

        for (size_t j = i; j < table->length - 1; j++) {
            table->items[j] = table->items[j + 1];
        }

        table->length--;
        break;
    }
}

void pgn_table_cleanup(pgn_table_t *table)
{
    for (size_t i = 0; i < table->length; i++) {
        __pgn_table_item_cleanup(table->items[i]);
    }

    free(table->items);
    free(table);
}
