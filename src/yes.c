#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if(argc >= 2 && (strcmp(argv[1], "--help") == 0)) {
        printf("Usage: yes [STRING]\n");
        return 0;
    } else {
        while (1) {
            if (argc < 2) {
                printf("y\n");
            } else {
                printf("%s\n", argv[1]);
            }
        }
    }
    return 0;
}
