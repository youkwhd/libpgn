#include "pgn.h"

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

size_t pgn_parse_moves(pgn_t *pgn, char *str)
{
    PGN_UNUSED(pgn);
    PGN_UNUSED(str);
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

    size_t cursor = 0;
    pgn_table_from_metadata_string(pgn->metadata, str, &cursor);
}
