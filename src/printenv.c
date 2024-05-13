#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

void print_help(char *program_name) {
    printf("Usage: %s [-0 | --null] [VARIABLE]\n", program_name);
    printf("Print the values of specified environment variable or all environment variables.\n\n");
    printf("Options:\n");
    printf("  -0, --null   End each output line with NUL, not newline.\n");
}

int main(int argc, char *argv[]) {
    int use_null_terminator = 0;
    if (argc > 1 && (strcmp(argv[1], "-0") == 0 || strcmp(argv[1], "--null") == 0)) {
        use_null_terminator = 1;
        argc--;
        argv++;
    }
    if (argc > 2 || (argc == 2 && (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0))) {
        print_help(argv[0]);
        return 0;
    }
    if (argc == 2) {
        char *value = getenv(argv[1]);
        if (value == NULL) {
            fprintf(stderr, "%s: %s: No such environment variable\n", argv[0], argv[1]);
            return 1;
        }
        printf("%s", value);
        if (use_null_terminator) {
            putchar('\0');
        } else {
            putchar('\n');
        }
    } else {
        char **env = environ;
        while (*env != NULL) {
            printf("%s", *env);
            if (use_null_terminator) {
                putchar('\0');
            } else {
                putchar('\n');
            }
            env++;
        }
    }

    return 0;
}
