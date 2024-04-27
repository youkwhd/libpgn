#include <pgn.h>
#include <stdio.h>
#include <assert.h>

unsigned int __nth = 1;

void __print_success()
{
    printf("[%d] Assertion success\n", __nth++);
}

void test_parsing_metadata()
{
    printf("calling %s()\n", __func__);
    __nth = 1;

    pgn_table_t *metadata = pgn_metadata_from_string("[Event \"F/S Return Match\"]\n[Site \"Belgrade, Serbia JUG\"]\n[Date \"1992.11.04\"]\n[Round \"29\"]\n[White \"Fischer, Robert J.\"]\n[Black \"Spassky, Boris V.\"]\n[Result \"1/2-1/2\"]\n");
    assert(strcmp(pgn_table_get(metadata, "Event"), "F/S Return Match") == 0);
    assert(strcmp(pgn_table_get(metadata, "Site"), "Belgrade, Serbia JUG") == 0);
    assert(strcmp(pgn_table_get(metadata, "Date"), "1992.11.04") == 0);
    assert(strcmp(pgn_table_get(metadata, "Round"), "29") == 0);
    assert(strcmp(pgn_table_get(metadata, "White"), "Fischer, Robert J.") == 0);
    assert(strcmp(pgn_table_get(metadata, "Black"), "Spassky, Boris V.") == 0);
    assert(strcmp(pgn_table_get(metadata, "Result"), "1/2-1/2") == 0);

    pgn_score_t score = pgn_score_from_string(pgn_table_get(metadata, "Result"));
    assert(score.white == 0 && score.black == 0);

    pgn_table_cleanup(metadata);
    __print_success();
}

int main(void)
{
    test_parsing_metadata();
    return 0;
}
