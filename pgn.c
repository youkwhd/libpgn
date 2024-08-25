#include "pgn.h"

#include <ctype.h>

pgn_t *pgn_init(void)
{
    pgn_t *pgn = malloc(sizeof *pgn);
    pgn->metadata = NULL;
    pgn->moves = NULL;
    return pgn;
}

void pgn_cleanup(pgn_t *pgn)
{
    if (pgn->metadata)
        pgn_metadata_cleanup(pgn->metadata);

    if (pgn->moves)
        pgn_moves_cleanup(pgn->moves);

    free(pgn);
}

pgn_metadata_t *pgn_parse_metadata(char *str)
{
    return pgn_metadata_from_string(str);
}

pgn_moves_t *pgn_parse_moves(char *str)
{
    return pgn_moves_from_string(str);
}

pgn_score_t pgn_parse_score(char *str)
{
    return pgn_score_from_string(str);
}

size_t pgn_parse(pgn_t *pgn, char *str)
{
    size_t cursor = 0;

    pgn->metadata = __pgn_metadata_from_string(str + cursor, &cursor);
    while (isspace(str[cursor])) cursor++;

    pgn->moves = __pgn_moves_from_string(str + cursor, &cursor);
    pgn->score = __pgn_score_from_string(str + cursor, &cursor);

    return cursor;
}
