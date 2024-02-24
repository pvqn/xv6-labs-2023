#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"

int main() {
    int uptime_ticks = uptime();
    printf("Uptime: %d ticks\n", uptime_ticks);
    exit(0);
}
