#include "enc.h"

static u8 h2c(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return 0;
}

u32 pthexd(const char *hex, u8 *buf) {
    u32 i = 0, n = 0;
    while (hex[i] && hex[i+1]) {
        buf[n++] = (h2c(hex[i]) << 4) | h2c(hex[i+1]);
        i += 2;
    }
    return n;
}

u32 pthexe(u8 *buf, u32 bufs, char *hex) {
    const char *chars = "0123456789abcdef";
    for (u32 i = 0; i < bufs; i++) {
        hex[i * 2] = chars[(buf[i] >> 4) & 0x0F];
        hex[i * 2 + 1] = chars[buf[i] & 0x0F];
    }
    hex[bufs * 2] = '\0';
    return bufs * 2;
}

static const char b64t[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

u32 ptb64e(const u8 *in, u32 len, char *out) {
    u32 i, j;
    for (i = 0, j = 0; i < len; i += 3, j += 4) {
        u32 v = in[i] << 16;
        if (i + 1 < len) v |= in[i + 1] << 8;
        if (i + 2 < len) v |= in[i + 2];
        out[j] = b64t[(v >> 18) & 0x3F];
        out[j + 1] = b64t[(v >> 12) & 0x3F];
        out[j + 2] = (i + 1 < len) ? b64t[(v >> 6) & 0x3F] : '=';
        out[j + 3] = (i + 2 < len) ? b64t[v & 0x3F] : '=';
    }
    out[j] = '\0';
    return j;
}

u32 ptb64d(const char *in, u8 *out) {
    u32 len = 0;
    while(in[len]) len++;
    u32 i, j;
    u8 d[256] = {0};
    for (i = 0; i < 64; i++) d[(u8)b64t[i]] = i;
    for (i = 0, j = 0; i < len; i += 4, j += 3) {
        u32 v = d[(u8)in[i]] << 18 | d[(u8)in[i+1]] << 12 | d[(u8)in[i+2]] << 6 | d[(u8)in[i+3]];
        out[j] = (v >> 16) & 0xFF;
        if (in[i+2] != '=') out[j+1] = (v >> 8) & 0xFF;
        if (in[i+3] != '=') out[j+2] = v & 0xFF;
    }
    return j;
}

u32 pturle(const char *in, char *out) {
    const char *hex = "0123456789ABCDEF";
    u32 j = 0;
    for (u32 i = 0; in[i]; i++) {
        u8 c = in[i];
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
            out[j++] = c;
        } else {
            out[j++] = '%';
            out[j++] = hex[c >> 4];
            out[j++] = hex[c & 15];
        }
    }
    out[j] = '\0';
    return j;
}

u32 pturld(const char *in, char *out) {
    u32 j = 0;
    for (u32 i = 0; in[i]; i++) {
        if (in[i] == '%' && in[i+1] && in[i+2]) {
            out[j++] = (h2c(in[i+1]) << 4) | h2c(in[i+2]);
            i += 2;
        } else if (in[i] == '+') {
            out[j++] = ' ';
        } else {
            out[j++] = in[i];
        }
    }
    out[j] = '\0';
    return j;
}

void ptprintfilt(char *s) {
    for (u32 i = 0; s[i]; i++) {
        if (s[i] < 32 || s[i] > 126) s[i] = '.';
    }
}

u32 ptbitrev32(u32 v) {
    v = ((v >> 1) & 0x55555555) | ((v & 0x55555555) << 1);
    v = ((v >> 2) & 0x33333333) | ((v & 0x33333333) << 2);
    v = ((v >> 4) & 0x0F0F0F0F) | ((v & 0x0F0F0F0F) << 4);
    v = ((v >> 8) & 0x00FF00FF) | ((v & 0x00FF00FF) << 8);
    v = (v >> 16) | (v << 16);
    return v;
}
