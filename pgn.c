#include "pgn.h"

#include <assert.h>

pgn_t *pgn_init()
{
    pgn_t *pgn = malloc(sizeof *pgn);
    pgn->metadata = pgn_table_init();

    return pgn;
}

void pgn_cleanup(pgn_t *pgn)
{
    pgn_table_cleanup(pgn->metadata);
    free(pgn);
}

size_t pgn_parse_metadata(pgn_t *pgn, char *str)
{
    unsigned int cursor = 0;

    for (;;) {
        if (str[cursor] != '[') return cursor;
        cursor++;

        pgn_string_t *key_buffer = pgn_string_init();
        pgn_string_t *value_buffer = pgn_string_init();

        while (str[cursor] != ' ') pgn_string_append(key_buffer, str[cursor++]);
        pgn_string_append_null_terminator(key_buffer);

        assert(str[++cursor] == '"');
        cursor++;

        while (str[cursor] != '"') pgn_string_append(value_buffer, str[cursor++]);
        pgn_string_append_null_terminator(value_buffer);

        pgn_table_insert(pgn->metadata, key_buffer->buf, value_buffer->buf);
        pgn_string_reset(key_buffer);
        pgn_string_reset(value_buffer);

        assert(str[++cursor] == ']');
        /* TODO: maybe expect whitespaces than just newline
         */
        assert(str[++cursor] == '\n');
        cursor++;

        pgn_string_cleanup(key_buffer);
        pgn_string_cleanup(value_buffer);
    }

    return cursor;
}

size_t pgn_parse_move(pgn_t *pgn, char *str)
{
    PGN_NOT_IMPLEMENTED();
    unsigned int cursor = 0;
    return cursor;
}

size_t pgn_parse_moves(pgn_t *pgn, char *str)
{
    PGN_NOT_IMPLEMENTED();
    unsigned int cursor = 0;
    return cursor;
}

void pgn_parse_from_file(pgn_t *pgn, FILE *file)
{
    PGN_UNUSED(pgn);
    PGN_UNUSED(file);
    PGN_NOT_IMPLEMENTED();
}

void pgn_parse_from_string(pgn_t *pgn, char *str)
{
    PGN_UNUSED(pgn);
    PGN_UNUSED(str);

    unsigned int cursor = 0;
    cursor += pgn_parse_metadata(pgn, str);
}
