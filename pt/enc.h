#ifndef PTENC_H
#define PTENC_H

#include "types.h"

u32 pthexe(u8 *buf, u32 bufs, char *hex);
u32 pthexd(const char *hex, u8 *buf);
u32 ptb64e(const u8 *in, u32 len, char *out);
u32 ptb64d(const char *in, u8 *out);
u32 pturle(const char *in, char *out);
u32 pturld(const char *in, char *out);
void ptprintfilt(char *s);
u32 ptbitrev32(u32 v);

#endif
