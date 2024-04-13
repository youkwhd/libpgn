#include "string.h"

pgn_string_t *pgn_string_init()
{
    pgn_string_t *pstr = malloc(sizeof *pstr);
    pstr->buf = malloc((sizeof *pstr->buf) * PGN_STRING_INITIAL_SIZE);
    pstr->size = PGN_STRING_INITIAL_SIZE;

    pgn_string_reset(pstr);
    return pstr;
}

void pgn_string_reset(pgn_string_t *pstr)
{
    pstr->length = 0;
    pgn_string_append_null_terminator(pstr);
}

void pgn_string_append(pgn_string_t *pstr, char ch)
{
    if (pstr->length >= pstr->size) {
        pstr->size += PGN_STRING_GROW_SIZE;
        pstr->buf = realloc(pstr->buf, pstr->size);
    }

    pstr->buf[pstr->length++] = ch;
}

void pgn_string_append_null_terminator(pgn_string_t *pstr)
{
    if (pstr->length >= pstr->size) {
        pstr->size += PGN_STRING_GROW_SIZE;
        pstr->buf = realloc(pstr->buf, pstr->size);
    }

    pstr->buf[pstr->length] = '\0';
}

void pgn_string_concat(pgn_string_t *pstr, char *str)
{
    for (; *str != '\0'; str++) {
        pgn_string_append(pstr, *str);
    }

    pgn_string_append_null_terminator(pstr);
}

void pgn_string_cleanup(pgn_string_t *pstr)
{
    free(pstr->buf);
    free(pstr);
}

