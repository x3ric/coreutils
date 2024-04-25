#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <utime.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

time_t parse_time(const char *time_str) {
    struct tm time_info = {0};
    sscanf(time_str, "%4d%2d%2d%2d%2d%2d",
        &time_info.tm_year, &time_info.tm_mon, &time_info.tm_mday,
        &time_info.tm_hour, &time_info.tm_min, &time_info.tm_sec);
    time_info.tm_year -= 1900;
    time_info.tm_mon -= 1;
    return mktime(&time_info);
}

int main(int argc, char *argv[]) {
    if (argc > 1 && (strcmp(argv[1], "--help") == 0)) {
        printf("Set Timestamp\nUsage: touch [OPTION]... FILE...\n"
        "Options:\n"
        "  -a                     change only the access time\n"
        "  -c, --no-create        do not create any files\n"
        "  -h, --no-dereference   affect each symbolic link instead of any referenced\n"
        "                         file (useful only on systems that can change the\n"
        "                         timestamps of a symlink)\n"
        "  -m                     change only the modification time\n"
        "  -r, --reference=FILE   use this file's times instead of current time\n"
        "  -t [[CC]YY]MMDDhhmm[.ss]  use specified time instead of current time,\n"
        "                         with a date-time format that differs from -d's\n"
        "      --time=WORD        specify which time to change:\n"
        "                           access time (-a): 'access', 'atime', 'use';\n"
        "                           modification time (-m): 'modify', 'mtime'\n"
        "      --help             display this help and exit\n");
        return 0;
    }

    bool update_access = false, update_modification = false, create_files = true, no_dereference = false;
    time_t custom_time = 0;
    const char *reference_file = NULL;

    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (strcmp(argv[i], "-a") == 0) {
                update_access = true;
            } else if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--no-create") == 0) {
                create_files = false;
            } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--no-dereference") == 0) {
                no_dereference = true;
            } else if (strcmp(argv[i], "-m") == 0) {
                update_modification = true;
            } else if (strcmp(argv[i], "-r") == 0 || strcmp(argv[i], "--reference") == 0) {
                if (i + 1 < argc) {
                    reference_file = argv[++i];
                } else {
                    printf("Option '%s' requires an argument.\n", argv[i]);
                    return 1;
                }
            } else if (strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "--time") == 0) {
                if (i + 1 < argc) {
                    i++;
                    custom_time = parse_time(argv[i]);
                } else {
                    printf("Option '%s' requires an argument.\n", argv[i]);
                    return 1;
                }
            } else {
                printf("Unknown option '%s'.\n", argv[i]);
                return 1;
            }
        }
    }

    struct stat st;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-') {
            if (strcmp(argv[i], "-") == 0) {
                printf("Not implemented: update timestamps of standard output.\n");
            } else {
                if (no_dereference) {
                    if (lstat(argv[i], &st) != 0) {
                        perror("Error getting symbolic link information");
                        return 1;
                    }
                } else {
                    if (stat(argv[i], &st) != 0) {
                        perror("Error getting file information");
                        return 1;
                    }
                }
                struct utimbuf new_times;
                if (reference_file != NULL) {
                    if (stat(reference_file, &st) == 0) {
                        new_times.actime = st.st_atime;
                        new_times.modtime = st.st_mtime;
                    } else {
                        perror("Error getting reference file information");
                        return 1;
                    }
                } else if (custom_time != 0) {
                    new_times.actime = update_access ? custom_time : st.st_atime;
                    new_times.modtime = update_modification ? custom_time : st.st_mtime;
                } else {
                    new_times.actime = update_access ? time(NULL) : st.st_atime;
                    new_times.modtime = update_modification ? time(NULL) : st.st_mtime;
                }
                if (utime(argv[i], &new_times) != 0) {
                    perror("Error updating timestamp");
                    return 1;
                }
            }
        }
    }
    return 0;
}
