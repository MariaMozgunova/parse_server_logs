#define __STDC_FORMAT_MACROS 1
#include "utils.c"

int main(int argc, char* argv[]) {
    uint64_t count_5xx;
    uint64_t max_logs;

    solve(argc, argv, &count_5xx, &max_logs);

    return 0;
}