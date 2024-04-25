#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
    if (argc > 1 && (strcmp(argv[1], "--help") == 0)) {
        printf("Output First Part Of Files\nUsage: head [OPTIONS] [FILE]...\n"
                "Options:\n"
                "  -h, --help               Display this help and exit\n"
                "  -n, --lines NUM          Output the first NUM lines\n"
                "  -c, --bytes NUM          Output the first NUM bytes\n"
                "  -q, --quiet, --silent    Never print headers giving file names\n"
                "  -v, --verbose            Always print headers giving file names\n"
                "  -z, --zero-terminated    Line delimiter is NUL, not newline\n");
        return 0;
    } else {
        FILE *file;

        int nfiles = argc;
        int nbytes = 0;
        int mlines = 10;
        int mbytes = 0;
        bool skip = false;
        bool bytes = false;
        bool quiet = false;
        bool verbose = false;
        bool zterminated = false;

        for (int i = 1; i < argc; i++) {
            if (i == 1) {
                nbytes = 0;
            }

            if (skip) {
                nfiles--;
                skip = false;
                if (bytes) {
                    mbytes = atoi(argv[i]);
                } else {
                    mlines = atoi(argv[i]);
                }
                continue;
            }
            
            if (strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "--lines") == 0) {
                nfiles--;
                skip = true;
                bytes = false;
                continue;
            }

            if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--bytes") == 0) {
                nfiles--;
                skip = true;
                bytes = true;
                continue;
            }

            if (strcmp(argv[i], "-z") == 0 || strcmp(argv[i], "--zero-terminated") == 0) {
                zterminated = true;
                continue;
            }

            if (strcmp(argv[i], "-q") == 0 || strcmp(argv[i], "--quiet") == 0 || strcmp(argv[i], "--silent") == 0) {
                quiet = true;
                continue;
            }

            if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0) {
                verbose = true;
                continue;
            }

            file = fopen(argv[i], "r");
            if (file == NULL) {
                perror(argv[i]);
                continue;
            }

            if ( ((!quiet || verbose) && (nfiles > 2)) ) {
                if ( zterminated ) {
                    printf("==> %s <==\0", argv[i]);
                } else {
                    printf("==> %s <==\n", argv[i]);
                }   
            }

            int c;
            int cline = 0;
            while (cline < mlines && (c = fgetc(file)) != EOF) {
                if (nbytes == mbytes && mbytes != 0) {
                    if ( zterminated ) {
                        putchar('\0');
                    } else {
                        putchar('\n');
                    }
                    break;
                }
                nbytes++;
                if (c == '\n' || c == '\r' || (zterminated && c == '\0')) cline++;
                putchar(c);
            }
            
            fclose(file);
        }
    }
    return 0;
}
