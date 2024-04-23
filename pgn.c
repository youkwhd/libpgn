#include "pgn.h"

#include <ctype.h>

pgn_t *pgn_init()
{
    pgn_t *pgn = malloc(sizeof *pgn);
    pgn->metadata = NULL;
    pgn->moves = NULL;
    return pgn;
}

void pgn_cleanup(pgn_t *pgn)
{
    if (pgn->metadata)
        pgn_table_cleanup(pgn->metadata);

    if (pgn->moves)
        pgn_moves_cleanup(pgn->moves);

    free(pgn);
}

void pgn_parse(pgn_t *pgn, char *str)
{
    size_t cursor = 0;

    pgn->metadata = __pgn_table_from_string(str + cursor, &cursor);
    while (isspace(str[cursor])) cursor++;

    pgn->moves = __pgn_moves_from_string(str + cursor, &cursor);
    pgn->score = __pgn_score_from_string(str + cursor, &cursor);
}
