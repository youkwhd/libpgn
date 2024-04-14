#include "annotation.h"

pgn_annotation_t pgn_annotation_from_string(char *str, size_t *consumed)
{
    if (str[0] == '\0') return PGN_ANNOTATION_NONE;

    if (str[0] == '!') {
        *consumed += 1;
        return PGN_ANNOTATION_GOOD_MOVE;
    }

    if (str[0] == '?') {
        *consumed += 1;
        return PGN_ANNOTATION_MISTAKE;
    }

    if (str[0] == '#') {
        *consumed += 1;
        return PGN_ANNOTATION_CHECKMATE;
    }

    if (str[1] == '\0') return PGN_ANNOTATION_NONE;

    if (str[0] == '!' && str[1] == '!') {
        *consumed += 2;
        return PGN_ANNOTATION_EXCELLENT_MOVE;
    }

    if (str[0] == '!' && str[1] == '?') {
        *consumed += 2;
        return PGN_ANNOTATION_INTRESTING_MOVE;
    }

    if (str[0] == '?' && str[1] == '!') {
        *consumed += 2;
        return PGN_ANNOTATION_DUBIOUS_MOVE;
    }

    if (str[0] == '?' && str[1] == '?') {
        *consumed += 2;
        return PGN_ANNOTATION_BLUNDER;
    }

    return PGN_ANNOTATION_NONE;
}
