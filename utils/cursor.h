#ifndef __LIBPGN_CURSOR_H
#define __LIBPGN_CURSOR_H

#include <stddef.h>
#include <stdbool.h>

/* Tiny pgn cursor helper
 */

bool pgn_cursor_skip_whitespace(char *str, size_t *cursor);
bool pgn_cursor_revisit_whitespace(char *str, size_t *cursor);
bool pgn_cursor_skip_comment(char *str, size_t *cursor);
bool pgn_cursor_skip_newline(char *str, size_t *cursor);

#endif // __LIBPGN_CURSOR_H
