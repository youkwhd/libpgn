#ifndef __LIBPGN_CURSOR_H
#define __LIBPGN_CURSOR_H

#include <stddef.h>

/* Tiny pgn cursor helper
 */

void pgn_cursor_skip_whitespace(char *str, size_t *cursor);
void pgn_cursor_skip_comment(char *str, size_t *cursor);
void pgn_cursor_skip_newline(char *str, size_t *cursor);

#endif // __LIBPGN_CURSOR_H
