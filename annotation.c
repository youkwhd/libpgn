#include "annotation.h"

pgn_annotation_t __pgn_annotation_from_string(char *str, size_t *consumed)
{
    /* TODO: maybe refactor using strcmp()?
     */
    pgn_annotation_t annotation = PGN_ANNOTATION_NONE;

    if (str[0] == '\0')
        return annotation;

    if (str[0] == '!') {
        (*consumed)++;
        annotation = PGN_ANNOTATION_GOOD_MOVE;
    }

    if (str[0] == '?') {
        (*consumed)++;
        annotation = PGN_ANNOTATION_MISTAKE;
    }

    if (str[0] == '#') {
        (*consumed)++;
        annotation = PGN_ANNOTATION_CHECKMATE;
    }

    if (str[1] == '\0')
        return annotation;

    if (str[0] == '!' && str[1] == '!') {
        (*consumed)++;
        annotation = PGN_ANNOTATION_EXCELLENT_MOVE;
    }

    if (str[0] == '!' && str[1] == '?') {
        (*consumed)++;
        annotation = PGN_ANNOTATION_INTRESTING_MOVE;
    }

    if (str[0] == '?' && str[1] == '!') {
        (*consumed)++;
        annotation = PGN_ANNOTATION_DUBIOUS_MOVE;
    }

    if (str[0] == '?' && str[1] == '?') {
        (*consumed)++;
        annotation = PGN_ANNOTATION_BLUNDER;
    }

    return annotation;
}

pgn_annotation_t pgn_annotation_from_string(char *str)
{
    size_t consumed = 0;
    return __pgn_annotation_from_string(str, &consumed);
}
