#include "coordinate.h"

char pgn_coordinate_as_char(int n)
{
    return n + 'a';
}

int pgn_coordinate_as_number(char n)
{
    return n - 'a';
}
