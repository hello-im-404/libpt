#ifndef PTYPES_H
#define PTYPES_H

#include <stdbool.h>
#include <stdint.h>

typedef uint64_t u64;	
typedef uint32_t u32;	
typedef uint16_t u16;	
typedef uint8_t  u8;	

#define BUF256   256
#define BUF512   512
#define BUF1024  1024
#define BUF4096  4096

#define asize(x) (sizeof(x) / sizeof((x)[0]))

#endif
