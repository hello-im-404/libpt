#include "io.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>

int ptioread(const char *path, u8 *buf, u32 bufs) {
    int fd = open(path, O_RDONLY);
    if (fd < 0) return -1;
    int n = read(fd, buf, bufs);
    close(fd);
    return n;
}

int ptiowrite(const char *path, u8 *buf, u32 bufs) {
    int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) return -1;
    int n = write(fd, buf, bufs);
    close(fd);
    return n;
}

u64 ptiosize(const char *path) {
    struct stat st;
    if (stat(path, &st) < 0) return 0;
    return st.st_size;
}

bool ptioexists(const char *path) {
    return access(path, F_OK) == 0;
}

void* ptiomap(const char *path, u32 *sz) {
    int fd = open(path, O_RDONLY);
    if (fd < 0) return NULL;
    struct stat st;
    fstat(fd, &st);
    *sz = st.st_size;
    void *p = mmap(NULL, *sz, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);
    return (p == MAP_FAILED) ? NULL : p;
}

void ptiounmap(void *p, u32 sz) {
    if (p) munmap(p, sz);
}
