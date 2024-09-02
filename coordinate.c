#include "coordinate.h"

#include <ctype.h>

int pgn_coordinate_file_as_index(char file)
{
    if (isupper(file))
        return file - 'A';

    return file - 'a';
}
