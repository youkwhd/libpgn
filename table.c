#include "table.h"

#include <stdio.h>
#include <string.h>

void pgn_table_init(pgn_table_t *table)
{
    table->items = malloc((sizeof *table->items) * PGN_TABLE_INITIAL_SIZE);
    table->size = PGN_TABLE_INITIAL_SIZE;
    table->length = 0;
}

void pgn_table_printp(pgn_table_t *table)
{
    for (size_t i = 0; i < table->length; i++) {
        printf("[%s \"%s\"]\n", table->items[i].key, table->items[i].value);
    }
}

void pgn_table_insert(pgn_table_t *table, char *key, char *value)
{
    if (table->length >= table->size) {
        table->size += PGN_TABLE_GROW_SIZE;
        table->items = realloc(table->items, table->size);
    }

    table->items[table->length++] = (__pgn_table_item_t){key, value};
}

char *pgn_table_get(pgn_table_t *table, char *key)
{
    for (size_t i = 0; i < table->length; i++) {
        if (strcmp(table->items[i].key, key) == 0) {
            return table->items[i].value;
        }
    }

    return NULL;
}

void pgn_table_cleanup(pgn_table_t *table)
{
    free(table->items);
}
