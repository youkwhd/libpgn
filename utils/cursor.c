#include "cursor.h"

#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

void pgn_cursor_skip_whitespace(char *str, size_t *cursor)
{
    while (isspace(str[*cursor])) (*cursor)++;
}

void pgn_cursor_skip_comment(char *str, size_t *cursor)
{
    if (str[*cursor] != '{')
        return;

    (*cursor)++;

    unsigned int left_brace_count = 1, right_brace_count = 0; 
    while (right_brace_count != left_brace_count) {
        /* TODO: how to error idk???
         * maybe return corrupted err file idk wtf
         */
        if (str[*cursor] == '\0')
            abort();

        left_brace_count += str[*cursor] == '{';
        right_brace_count += str[*cursor] == '}';
        (*cursor)++;
    }
}

void pgn_cursor_skip_newline(char *str, size_t *cursor)
{
    if (str[*cursor] == '\r') {
        assert(str[(*cursor)++] == '\r');
        assert(str[(*cursor)++] == '\n');
        return;
    }

    assert(str[(*cursor)++] == '\n');
}
