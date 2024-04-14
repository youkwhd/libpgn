#include "coordinate.h"

char pgn_coordinate_as_alphabet(int n)
{
    return n + 'A';
}

int pgn_coordinate_as_number(char n)
{
    return n - 'A';
}
