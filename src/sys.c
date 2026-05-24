#include "sys.h"
#include <unistd.h>
#include <sys/sysinfo.h>
#include <stdio.h>

u32 ptsyspage(void) {
    return sysconf(_SC_PAGESIZE);
}

u64 ptsysuptime(void) {
    struct sysinfo info;
    if (sysinfo(&info) < 0) return 0;
    return info.uptime;
}

u32 ptsyscpu(void) {
    return sysconf(_SC_NPROCESSORS_ONLN);
}

void ptsyshost(char *buf, u32 bufs) {
    gethostname(buf, bufs);
}

u32 ptsysuid(void) {
    return getuid();
}

u32 ptsysgid(void) {
    return getgid();
}
