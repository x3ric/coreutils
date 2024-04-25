#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

int main(int argc, char *argv[]) {
    int opt;
    int ignore = 0;
    int nproc = 0;
    
    struct option long_options[] = {
        {"all", no_argument, NULL, 'a'},
        {"ignore", required_argument, NULL, 'i'},
        {"help", no_argument, NULL, 'h'},
        {NULL, 0, NULL, 0}
    };
    
    while ((opt = getopt_long(argc, argv, "", long_options, NULL)) != -1) {
        switch (opt) {
            case 'a':
                goto exitnproc;
                break;
            case 'i':
                ignore = atoi(optarg);
                break;
            case 'h':
                printf("Usage: nproc [OPTION]...\n"
                       "Print the number of processing units available to the current process,\n"
                       "which may be less than the number of online processors\n\n"
                       "      --all      print the number of installed processors\n"
                       "      --ignore=N  if possible, exclude N processing units\n"
                       "      --help        display this help and exit\n");
                exit(EXIT_SUCCESS);
            default:
                fprintf(stderr, "Usage: %s [--all] [--ignore=N] [--help]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }
    
    if (ignore > 0) {
        nproc = sysconf(_SC_NPROCESSORS_CONF) - ignore;
        if(nproc<=0){nproc=1;}
        printf("%ld\n", nproc);
    } else {
        exitnproc:
        nproc = sysconf(_SC_NPROCESSORS_ONLN);
        printf("%ld\n", nproc);
    }
    
    return 0;
}
