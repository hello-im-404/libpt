#ifndef PTELF_H
#define PTELF_H

#include "../types.h"

#define ELF_MAG "\x7f\x45\x4c\x46"

#pragma pack(push, 1)
typedef struct {
	u8  ident[16];
	u16 type;
	u16 mach;
	u32 ver;
	u64 ent;
	u64 phoff;
	u64 shoff;
	u32 flg;
	u16 ehsz;
	u16 phentsz;
	u16 phnum;
	u16 shentsz;
	u16 shnum;
	u16 shstridx;
} ptelfhdr;

typedef struct {
    u32 name;
    u32 type;
    u64 flg;
    u64 addr;
    u64 off;
    u64 sz;
    u32 link;
    u32 info;
    u64 align;
    u64 entsz;
} ptelfshdr;
#pragma pack(pop)

int ptelfprs(u8 *buf, u32 bufs, ptelfhdr *hdr);
int ptelfsec(u8 *buf, u32 bufs, ptelfhdr *hdr, u16 idx, ptelfshdr *shdr);

#endif
