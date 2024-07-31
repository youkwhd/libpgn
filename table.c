#include "table.h"

#include <stdio.h>
#include <assert.h>

pgn_table_t *__pgn_table_from_string(char *str, size_t *consumed)
{
    size_t cursor = 0;

    /* Redundant check, but it works to not make unnecessary
     * memory allocations (key_buf, value_buf)
     */
    if (str[cursor] != '[') return NULL;

    pgn_table_t *table = pgn_table_init();
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

        pgn_table_insert(table, key_buffer->buf, value_buffer->buf);
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
    return table;
}

pgn_table_t *pgn_table_from_string(char *str)
{
    size_t consumed = 0;
    return __pgn_table_from_string(str, &consumed);
}

void __pgn_table_item_init(__pgn_table_item_t *item)
{
    item->key = pgn_string_init();
    item->value = pgn_string_init();
}

void __pgn_table_item_cleanup(__pgn_table_item_t *item)
{
    pgn_string_cleanup(item->key);
    pgn_string_cleanup(item->value);
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
        printf("[%s \"%s\"]\n", table->items[i].key->buf, table->items[i].value->buf);
    }
}

void pgn_table_insert(pgn_table_t *table, char *key, char *value)
{
    if (table->length >= table->size) {
        table->size += PGN_TABLE_GROW_SIZE;
        table->items = realloc(table->items, (sizeof *table->items) * table->size);
    }

    __pgn_table_item_t item = {0};
    __pgn_table_item_init(&item);

    pgn_string_concat(item.key, key);
    pgn_string_concat(item.value, value);

    table->items[table->length++] = item;
}

char *pgn_table_get(pgn_table_t *table, char *key)
{
    for (size_t i = 0; i < table->length; i++) {
        if (pgn_string_equal(table->items[i].key, key)) {
            return table->items[i].value->buf;
        }
    }

    return NULL;
}

void pgn_table_delete(pgn_table_t *table, char *key)
{
    for (size_t i = 0; i < table->length; i++) {
        if (!pgn_string_equal(table->items[i].key, key)) {
            continue;
        }

        __pgn_table_item_cleanup(&table->items[i]);

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
        __pgn_table_item_cleanup(&table->items[i]);
    }

    free(table->items);
    free(table);
}
