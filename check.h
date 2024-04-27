#ifndef __LIBPGN_CHECK_H
#define __LIBPGN_CHECK_H

#include "export.h"
#include <stddef.h>

typedef enum pgn_check_t {
    PGN_CHECK_NONE = 0,
    PGN_CHECK_SINGLE,
    PGN_CHECK_DOUBLE,
} pgn_check_t;

PGN_EXPORT pgn_check_t __pgn_check_from_string(char *str, size_t *consumed);
PGN_EXPORT pgn_check_t pgn_check_from_string(char *str);

#endif // __LIBPGN_CHECK_H
