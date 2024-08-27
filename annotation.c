#include "annotation.h"
#include "cursor.h"

#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include <ctype.h>

pgn_annotation_t __pgn_annotation_from_string(char *str, size_t *consumed)
{
    /* TODO: maybe refactor using strcmp()?
     */
    pgn_annotation_t annotation = PGN_ANNOTATION_NULL;

    if (str[0] == '\0')
        return annotation;

    if (str[0] == '$') {
        size_t cursor = 0;

        /* INFO: NAG annotation tends to have $0 followed by another $<num>.
         * thus why the while loop, take the last.
         */
        while (str[cursor] == '$') {
            assert(isdigit(str[++cursor]));

            /* TODO: don't discard the rest.
             */
            char *endptr = NULL;
            long num = strtol(str + cursor, &endptr, 10);

            annotation = num;
            cursor += endptr - (str + cursor);

            pgn_cursor_skip_whitespace(str, &cursor);
        }

        *consumed += cursor;
        return annotation;
    }

    if (str[0] == '!') {
        (*consumed)++;
        annotation = PGN_ANNOTATION_GOOD_MOVE;
    }

    if (str[0] == '?') {
        (*consumed)++;
        annotation = PGN_ANNOTATION_MISTAKE;
    }

    if (str[1] == '\0')
        return annotation;

    if (str[0] == '!' && str[1] == '!') {
        (*consumed)++;
        annotation = PGN_ANNOTATION_BRILLIANT_MOVE;
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
