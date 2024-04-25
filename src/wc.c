#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE_LENGTH 1024

int main(int argc, char *argv[]) {
    if (argc > 1 && (strcmp(argv[1], "--help") == 0)) {
        printf("Usage: wc [OPTION]... [FILE]...\n"
               "  or:  w [OPTION]... --files0-from=F\n"
               "Print newline, word, and byte counts for each FILE, and a total line if\n"
               "more than one FILE is specified.  A word is a nonempty sequence of non white\n"
               "space delimited by white space characters or by start or end of input.\n\n"
               "With no FILE, or when FILE is -, read standard input.\n\n"
               "Options:\n"
               "  -c, --bytes           print the byte counts\n"
               "  -m, --chars           print the character counts\n"
               "  -l, --lines           print the newline counts\n"
               "      --files0-from=F  read input from the files specified by\n"
               "                        NUL-terminated names in file F;\n"
               "                        If F is - then read names from standard input\n"
               "  -L, --max-line-length print the maximum display width\n"
               "  -w, --words           print the word counts\n"
               "      --total=WHEN      when to print a line with total counts;\n"
               "                        WHEN can be: auto, always, only, never\n");
        return 0;
    } else {
        int print_lines = 0, print_words = 0, print_chars = 0, print_bytes = 0, print_max_line_length = 0;
        int print_total = 0;
        char *file_name = NULL;
        int opt;
        while ((opt = getopt(argc, argv, "clmLw")) != -1) {
            switch (opt) {
                case 'c': print_bytes = 1; break;
                case 'm': print_chars = 1; break;
                case 'l': print_lines = 1; break;
                case 'w': print_words = 1; break;
                case 'L': print_max_line_length = 1; break;
                default:
                    fprintf(stderr, "Usage: %s [OPTION]... [FILE]...\n", argv[0]);
                    fprintf(stderr, "Try '%s --help' for more information.\n", argv[0]);
                    return 1;
            }
        }
        if (optind < argc) {
            file_name = argv[optind];
        } else {
            fprintf(stderr, "Usage: %s [OPTION]... [FILE]...\n", argv[0]);
            return 1;
        }
        FILE *file;
        if (file_name != NULL && strcmp(file_name, "-") != 0) {
            file = fopen(file_name, "r");
            if (file == NULL) {
                fprintf(stderr, "Error: Unable to open file %s\n", file_name);
                return 1;
            }
        } else {
            file = stdin;
        }
        int total_lines = 0, total_words = 0, total_chars = 0, total_bytes = 0, max_line_length = 0;
        char line[MAX_LINE_LENGTH];
        while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
            int line_length = strlen(line);
            total_lines++;
            total_chars += line_length;
            total_bytes += line_length;
            if (print_max_line_length && line_length > max_line_length) {
                max_line_length = line_length;
            }
            char *token = strtok(line, " \t\n\r\v\f");
            while (token != NULL) {
                total_words++;
                token = strtok(NULL, " \t\n\r\v\f");
            }
        }
        if (file != stdin) {
            fclose(file);
        }
        if (print_total) {
            printf("%d %d %d %s\n", total_lines, total_words, total_chars, file_name);
        } else {
            if (print_lines == 0 && print_words == 0 && print_chars == 0 && print_bytes == 0 && print_max_line_length == 0) {
                print_lines = print_words = print_chars = 1;
            }
            if (print_lines) printf("%d ", total_lines - 1);
            if (print_words) printf("%d ", total_words);
            if (print_chars) printf("%d ", total_chars);
            if (print_bytes) printf("%d ", total_bytes);
            if (print_max_line_length) printf("%d ", max_line_length - 1);
            printf("%s\n", file_name);
        }
    }
    return 0;
}
