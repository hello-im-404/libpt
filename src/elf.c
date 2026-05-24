#include "elf.h"
#include <string.h>

int ptelfprs(u8 *buf, u32 bufs, ptelfhdr *hdr) {
	if (bufs < sizeof(ptelfhdr)) return -1;
	if (memcmp(buf, ELF_MAG, 4) != 0) return -1;
	memcpy(hdr, buf, sizeof(ptelfhdr));
	return 0;
}

int ptelfsec(u8 *buf, u32 bufs, ptelfhdr *hdr, u16 idx, ptelfshdr *shdr) {
    if (idx >= hdr->shnum) return -1;
    u64 off = hdr->shoff + (idx * hdr->shentsz);
    if (off + sizeof(ptelfshdr) > bufs) return -1;
    memcpy(shdr, buf + off, sizeof(ptelfshdr));
    return 0;
}
