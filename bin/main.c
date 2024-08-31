#include <pgn.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "fmt.h"

char *read_file(char *filename)
{
    FILE *fp = fopen(filename, "r");

    fseek(fp, 0, SEEK_END);
    int filesize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *buf = malloc(sizeof(*buf) * (filesize + 1));
    fread(buf, sizeof(*buf), filesize, fp);
    buf[filesize] = '\0';

    return buf;
}

int main(int argc, char **argv)
{
    if (argc <= 1) {
        fprintf(stderr, "%s: no subcommand provided.\n", *argv);
        exit(EXIT_FAILURE);
    }

    char *subcommand = argv[1];
    if (strcmp(subcommand, "fmt") == 0) {
        if (argc <= 2) {
            fprintf(stderr, "%s: no pgn file provided.\n", *argv);
            exit(EXIT_FAILURE);
        }

        char *filename = argv[2];
        char *pgn_file_contents = read_file(filename);
        char *saved_ptr = pgn_file_contents;

        while (*pgn_file_contents) {
            pgn_t *pgn = pgn_init();
            size_t consumed = pgn_parse(pgn, pgn_file_contents);

            pgn_file_contents += consumed;
            while (isspace(*pgn_file_contents))
                pgn_file_contents++;

            fmt_print(pgn);

            /* still have unparsed pgn */
            if (*pgn_file_contents)
                printf("\n");

            pgn_cleanup(pgn);
        }

        free(saved_ptr);
    } else {
        fprintf(stderr, "%s: unknown subcommand '%s'.\n", *argv, subcommand);
        exit(EXIT_FAILURE);
    }

    return 0;
}
