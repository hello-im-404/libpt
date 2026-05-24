#include "cry.h"
#include <fcntl.h>
#include <unistd.h>

void ptxore(u8 *buf, u32 bufs, u8 *key, u32 klen) {
    for (u32 i = 0; i < bufs; i++) buf[i] ^= key[i % klen];
}

u32 ptrotl32(u32 v, u8 n) {
    return (v << n) | (v >> (32 - n));
}

u32 ptrotr32(u32 v, u8 n) {
    return (v >> n) | (v << (32 - n));
}

u32 ptfnv1a(const u8 *buf, u32 bufs) {
    u32 h = 0x811c9dc5;
    for (u32 i = 0; i < bufs; i++) {
        h ^= buf[i];
        h *= 0x01000193;
    }
    return h;
}

u32 ptcrc32(const u8 *buf, u32 bufs) {
    u32 c = 0xFFFFFFFF;
    for (u32 i = 0; i < bufs; i++) {
        c ^= buf[i];
        for (int j = 0; j < 8; j++) {
            c = (c >> 1) ^ (0xEDB88320 & (-(c & 1)));
        }
    }
    return ~c;
}

u32 pthashxor(const u8 *buf, u32 bufs) {
    u32 h = 0;
    for (u32 i = 0; i < bufs; i++) h ^= (buf[i] << ((i % 4) * 8));
    return h;
}

double ptlog2(double x) {
    if (x <= 0.0) return 0.0;
    union { double d; u64 i; } u;
    u.d = x;
    int exp = (int)((u.i >> 52) & 0x7FF) - 1023;
    u.i = (u.i & 0x000FFFFFFFFFFFFFULL) | 0x3FF0000000000000ULL;
    double m = u.d;
    double y = (m - 1.0) / (m + 1.0);
    double y2 = y * y;
    return (double)exp + 2.885390081777927 * y * (1.0 + y2 * 0.333333333333333);
}

u8 ptentropy(const u8 *buf, u32 bufs) {
    u32 f[256] = {0};
    double e = 0;
    for (u32 i = 0; i < bufs; i++) f[buf[i]]++;
    for (int i = 0; i < 256; i++) {
        if (f[i] > 0) {
            double p = (double)f[i] / bufs;
            e -= p * ptlog2(p);
        }
    }
    return (u8)(e * 10); 
}

void ptmemxor(u8 *dst, const u8 *src, u32 bufs) {
    for (u32 i = 0; i < bufs; i++) dst[i] ^= src[i];
}

void ptkeyexp(u8 *key, u32 klen, u8 *out, u32 olen) {
    for (u32 i = 0; i < olen; i++) out[i] = key[i % klen] ^ (i & 0xFF);
}

static u32 r_state = 0xACE1u;
u32 ptrandom(void) {
    r_state ^= r_state << 13;
    r_state ^= r_state >> 17;
    r_state ^= r_state << 5;
    return r_state;
}
