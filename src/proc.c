#include "proc.h"
#include <stdio.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>

static int s2i(const char *s) {
    int res = 0;
    while (*s >= '0' && *s <= '9') {
        res = res * 10 + (*s - '0');
        s++;
    }
    return res;
}

int ptprocfind(const char *name) {
    DIR *d = opendir("/proc");
    struct dirent *e;
    int pid = -1;
    if (!d) return -1;
    while ((e = readdir(d))) {
        if (e->d_name[0] >= '0' && e->d_name[0] <= '9') {
            char path[256];
            char comm[256];
            snprintf(path, sizeof(path), "/proc/%s/comm", e->d_name);
            int fd = open(path, O_RDONLY);
            if (fd >= 0) {
                int n = read(fd, comm, sizeof(comm) - 1);
                close(fd);
                if (n > 0) {
                    if (comm[n-1] == '\n') comm[n-1] = '\0';
                    else comm[n] = '\0';
                    if (strcmp(comm, name) == 0) {
                        pid = s2i(e->d_name);
                        break;
                    }
                }
            }
        }
    }
    closedir(d);
    return pid;
}

u32 ptproclist(int *pids, u32 max) {
    DIR *d = opendir("/proc");
    struct dirent *e;
    u32 n = 0;
    if (!d) return 0;
    while ((e = readdir(d)) && n < max) {
        if (e->d_name[0] >= '0' && e->d_name[0] <= '9') {
            pids[n++] = s2i(e->d_name);
        }
    }
    closedir(d);
    return n;
}

int ptproccmd(int pid, char *buf, u32 bufs) {
    char path[64];
    snprintf(path, sizeof(path), "/proc/%d/cmdline", pid);
    int fd = open(path, O_RDONLY);
    if (fd < 0) return -1;
    int n = read(fd, buf, bufs - 1);
    close(fd);
    if (n > 0) buf[n] = '\0';
    return n;
}

int ptprocrun(const char *path, char *const argv[]) {
    int pid = fork();
    if (pid == 0) {
        execvp(path, argv);
        exit(1);
    }
    return pid;
}

int ptprockill(int pid) {
    return kill(pid, SIGKILL);
}

int ptprocself(void) {
    return getpid();
}
