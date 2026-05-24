#ifndef PTIO_H
#define PTIO_H

#include "types.h"

int   ptioread(const char *path, u8 *buf, u32 bufs);
int   ptiowrite(const char *path, u8 *buf, u32 bufs);
u64   ptiosize(const char *path);
bool  ptioexists(const char *path);
void* ptiomap(const char *path, u32 *sz);
void  ptiounmap(void *p, u32 sz);

#endif
