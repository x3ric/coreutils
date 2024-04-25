#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc == 1) {
        return 0;
    }
    if (argc > 1 && (strcmp(argv[1], "--help") == 0)) {
        printf("Concatenate Files\nUsage: cat [FILE]...\n");
        return 0;
    } else {
        for (int i = 1; i < argc; i++) {
            FILE *file = fopen(argv[i], "r");
            if (file == NULL) {
                perror(argv[i]);
                continue;
            }
            int c;
            while ((c = fgetc(file)) != EOF) {
                putchar(c);
            }
            putchar('\n');
            fclose(file);
        }
    }
    return 0;
}
