#ifndef __PGN_PGN_H
#define __PGN_PGN_H

#include <stdio.h>
#include <stdlib.h>

#undef PGN_UNUSED
#undef PGN_NOT_IMPLEMENTED

#define PGN_UNUSED(x) ((void)x)
#define PGN_NOT_IMPLEMENTED()                                                                                   \
    do {                                                                                                        \
        fprintf(stderr, "pgn: function `%s` is not implemented yet, at %s:%d\n", __func__, __FILE__, __LINE__); \
        exit(EXIT_FAILURE);                                                                                     \
    } while (0)

#endif // __PGN_PGN_H
