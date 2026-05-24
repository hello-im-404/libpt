#ifndef PTPE_H
#define PTPE_H

#include "../types.h"

#define PEMZ  0x5A4D
#define PESIG 0x00004550

#pragma pack(push, 1)
typedef struct {
    u16 mgc;
    u16 cblp[28]; 
    u32 lfanew;
} ptpedos;

typedef struct {
    u16 mach;
    u16 secnum;
    u32 ts;
    u32 symptr;
    u32 symnum;
    u16 optsz;
    u16 charac;
} ptpefile;

typedef struct {
    u32 sig;
    ptpefile file;
} ptpehdr;

typedef struct {
    u8  name[8];
    u32 vsz;
    u32 vaddr;
    u32 rsz;
    u32 roff;
    u32 rptr;
    u32 lptr;
    u16 rnum;
    u16 lnum;
    u32 charac;
} ptpeshdr;
#pragma pack(pop)

int ptpeprs(u8 *buf, u32 bufs, ptpedos *dos, ptpehdr *hdr);
int ptpesec(u8 *buf, u32 bufs, ptpehdr *hdr, u16 idx, ptpeshdr *shdr);

#endif
