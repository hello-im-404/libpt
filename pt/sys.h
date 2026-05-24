#ifndef PTSYS_H
#define PTSYS_H

#include "types.h"

u32 ptsyspage(void);

u64 ptsysuptime(void);

u32 ptsyscpu(void);

void ptsyshost(char *buf, u32 bufs);

u32 ptsysuid(void);

u32 ptsysgid(void);

#endif
