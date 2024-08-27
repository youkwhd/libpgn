#include "cursor.h"

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

    while (str[(*cursor)++] != '}');
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
