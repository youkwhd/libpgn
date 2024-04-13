#include "table.h"

#include <stdio.h>
#include <string.h>

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
        if (strcmp(table->items[i]->key->buf, key) == 0) {
            return table->items[i]->value->buf;
        }
    }

    return NULL;
}

void pgn_table_cleanup(pgn_table_t *table)
{
    for (size_t i = 0; i < table->length; i++) {
        __pgn_table_item_cleanup(table->items[i]);
    }

    free(table->items);
    free(table);
}
