#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc == 1) {
        return 0;
    }
    if (argc > 1 && (strcmp(argv[1], "--help") == 0)) {
        printf("Concatenate Files In Reverse\nUsage: tac [FILE]...\n");
        return 0;
    } else {
        FILE *file;
        for (int i = 1; i < argc; i++) {
            file = fopen(argv[i], "r");
            if (file == NULL) {
                perror(argv[i]);
                continue;
            }
            int c, linec = 0;
            while ((c = fgetc(file)) != EOF) if (c == '\n') linec++;
            fseek(file, 0, SEEK_SET);
            char **lines = malloc(linec * sizeof(char *));
            for (int i = 0; i < linec; i++) {
                char *line = NULL;
                size_t len = 0;
                getline(&line, &len, file);
                lines[i] = line;
            }
            for (int i = linec - 1; i >= 0; i--) {
                printf("%s", lines[i]);
                free(lines[i]);
            }
            free(lines);
            putchar('\n');
            fclose(file);
        }
    }
    return 0;
}
