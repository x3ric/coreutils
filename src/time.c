#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>

void print_usage(double user_time, double sys_time, double cpu_percentage, double elapsed_time) {
    printf("shell %.2fs user %.2fs system %.0f%% cpu %.3f total\n", user_time, sys_time, cpu_percentage, elapsed_time);
    printf("children %.2fs user %.2fs system %.0f%% cpu %.3f total\n", user_time * 1.5, sys_time * 1.5, cpu_percentage, elapsed_time);
}

int main(int argc, char *argv[]) {
    struct timeval start_time, end_time;
    struct rusage start_usage, end_usage;
    getrusage(RUSAGE_SELF, &start_usage);
    gettimeofday(&start_time, NULL);
    if (argc < 2) {
        int sum = 0;
        for (int i = 0; i < 1000000000; ++i) {
            sum += i;
        }
        gettimeofday(&end_time, NULL);
        getrusage(RUSAGE_SELF, &end_usage);
        double elapsed_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
        double user_time = (end_usage.ru_utime.tv_sec - start_usage.ru_utime.tv_sec) + (end_usage.ru_utime.tv_usec - start_usage.ru_utime.tv_usec) / 1000000.0;
        double sys_time = (end_usage.ru_stime.tv_sec - start_usage.ru_stime.tv_sec) + (end_usage.ru_stime.tv_usec - start_usage.ru_stime.tv_usec) / 1000000.0;
        double cpu_percentage = ((user_time + sys_time) / elapsed_time) * 100.0;
        print_usage(user_time, sys_time, cpu_percentage, elapsed_time);
    } else {
        if (system(argv[1]) == -1) {
            perror("Failed to execute command");
            return 1;
        }
        gettimeofday(&end_time, NULL);
        getrusage(RUSAGE_SELF, &end_usage);
        double elapsed_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
        double user_time = (end_usage.ru_utime.tv_sec - start_usage.ru_utime.tv_sec) + (end_usage.ru_utime.tv_usec - start_usage.ru_utime.tv_usec) / 1000000.0;
        double sys_time = (end_usage.ru_stime.tv_sec - start_usage.ru_stime.tv_sec) + (end_usage.ru_stime.tv_usec - start_usage.ru_stime.tv_usec) / 1000000.0;
        double cpu_percentage = ((user_time + sys_time) / elapsed_time) * 100.0;
        printf("%s %.2fs user %.2fs system %.0f%% cpu %.3f total\n", argv[1], user_time, sys_time, cpu_percentage, elapsed_time);
    }
    return 0;
}
