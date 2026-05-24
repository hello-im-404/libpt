#ifndef PTCRY_H
#define PTCRY_H

#include "types.h"

void ptxore(u8 *buf, u32 bufs, u8 *key, u32 klen);
u32  ptrotl32(u32 v, u8 n);
u32  ptrotr32(u32 v, u8 n);
u32  ptfnv1a(const u8 *buf, u32 bufs);
u32  ptcrc32(const u8 *buf, u32 bufs);
u32  pthashxor(const u8 *buf, u32 bufs);
u8   ptentropy(const u8 *buf, u32 bufs);
double ptlog2(double x);
void ptmemxor(u8 *dst, const u8 *src, u32 bufs);
void ptkeyexp(u8 *key, u32 klen, u8 *out, u32 olen);
u32  ptrandom(void);

#endif
