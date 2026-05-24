#include "pe.h"
#include <string.h>

int ptpeprs(u8 *buf, u32 bufs, ptpedos *dos, ptpehdr *hdr) {
    if (bufs < sizeof(ptpedos)) return -1;
    ptpedos *d = (ptpedos*)buf;
    if (d->mgc != PEMZ) return -1;
    if (dos) memcpy(dos, d, sizeof(ptpedos));
    if (d->lfanew + sizeof(ptpehdr) > bufs) return -1;
    ptpehdr *h = (ptpehdr*)(buf + d->lfanew);
    if (h->sig != PESIG) return -1;
    if (hdr) memcpy(hdr, h, sizeof(ptpehdr));
    return 0;
}

int ptpesec(u8 *buf, u32 bufs, ptpehdr *hdr, u16 idx, ptpeshdr *shdr) {
    if (idx >= hdr->file.secnum) return -1;
    ptpedos *d = (ptpedos*)buf;
    u64 off = d->lfanew + sizeof(ptpehdr) + hdr->file.optsz + (idx * sizeof(ptpeshdr));
    if (off + sizeof(ptpeshdr) > bufs) return -1;
    memcpy(shdr, buf + off, sizeof(ptpeshdr));
    return 0;
}
