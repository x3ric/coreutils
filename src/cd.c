#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc == 1) {
        chdir(getenv("HOME"));
    } else {
        chdir(argv[2]);
    }
    return 0;
}
