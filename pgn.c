#include "pgn.h"

void pgn_init(pgn_t *pgn)
{
    pgn_table_init(pgn->metadata);
}

void pgn_cleanup(pgn_t *pgn)
{
    pgn_table_cleanup(pgn->metadata);
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
    PGN_NOT_IMPLEMENTED();
}
