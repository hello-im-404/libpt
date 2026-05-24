#ifndef PTPROC_H
#define PTPROC_H

#include "types.h"

int ptprocfind(const char *name);

u32 ptproclist(int *pids, u32 max);

int ptproccmd(int pid, char *buf, u32 bufs);

int ptprocrun(const char *path, char *const argv[]);

int ptprockill(int pid);

int ptprocself(void);

#endif
