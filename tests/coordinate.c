#include "extra/suite6.h"

#include <pgn.h>

void test_convert_coordinate()
{
    suite6_assert(pgn_coordinate_file_as_index('a') == 0);
    suite6_assert(pgn_coordinate_file_as_index('b') == 1);
    suite6_assert(pgn_coordinate_file_as_index('c') == 2);
    suite6_assert(pgn_coordinate_file_as_index('d') == 3);
    suite6_assert(pgn_coordinate_file_as_index('e') == 4);
}

int main(void)
{
    test_convert_coordinate();
    return 0;
}
