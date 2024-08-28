#ifndef __LIBPGN_COMMENTS_H
#define __LIBPGN_COMMENTS_H

#include <stdlib.h>

#include "utils/buffer.h"

typedef enum pgn_comment_position_t {
    PGN_COMMENT_POSITION_UNKNOWN = 0,

    /* {} 1. e4
     * ^ comment is here
     *
     * {} 1... e5
     * ^ comment is here
     */
    PGN_COMMENT_POSITION_BEFORE_MOVE,

    /* 1. {} e4
     *    ^ comment is here
     *
     * 1... {} e5
     *      ^ comment is here
     */
    PGN_COMMENT_POSITION_BETWEEN_MOVE,

    /* 1. e4 {}
     *       ^ comment is here
     *
     * 1... e5 {}
     *         ^ comment is here
     */
    PGN_COMMENT_POSITION_AFTER_MOVE,
} pgn_comment_position_t;

#define PGN_COMMENTS_INITIAL_SIZE 1
#define PGN_COMMENTS_GROW_SIZE 1

typedef struct pgn_comment_t {
    /* relative to a move */
    pgn_comment_position_t position;
    pgn_buffer_t *value;
} pgn_comment_t;

typedef struct pgn_comments_t {
    pgn_comment_t *values;
    size_t length;
    size_t size;
} pgn_comments_t;

void pgn_comment_init(pgn_comment_t *comment);
/* @abstraction
 *
 * it's the same as
 *
 * ```
 *   char *value = comment->value->buf;
 * ```
 */
char *pgn_comment_value(pgn_comment_t *comment);
pgn_comment_t __pgn_comment_from_string(char *str, size_t *consumed);
void pgn_comment_cleanup(pgn_comment_t *comment);

pgn_comments_t *pgn_comments_init();
void pgn_comments_push(pgn_comments_t *comments, pgn_comment_t comment);
void pgn_comments_cleanup(pgn_comments_t *comments);

#endif // __LIBPGN_COMMENTS_H
