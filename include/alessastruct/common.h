#ifndef ALESSASTRUCT_COMMON_H
#define ALESSASTRUCT_COMMON_H

#include "alessastruct/types.h"
#include "alessastruct/definitions.h"

#if defined(__GNUC__) || defined(__MWERKS__)
#define ATTRIBUTE(...) __attribute__((__VA_ARGS__))
#define ALIGNED(n) ATTRIBUTE(aligned(n))
#else
#define ATTRIBUTE(...)
#endif

typedef union Q {
    u_long128 u128;  // offset 0x0, size 0x10
    u_long u64[2];   // offset 0x0, size 0x8
    u_int u32[4];    // offset 0x0, size 0x10
    u_short u16[8];  // offset 0x0, size 0x10
    u_char u8[16];   // offset 0x0, size 0x10
    long s64[2];     // offset 0x0, size 0x8
    int s32[4];      // offset 0x0, size 0x10
    short s16[8];    // offset 0x0, size 0x10
    s_char s8[16];   // offset 0x0, size 0x10
    int q[4];        // offset 0x0, size 0x10
    float fv[4];     // offset 0x0, size 0x10
    int iv[4];       // offset 0x0, size 0x10
} Q;

#endif // ALESSASTRUCT_COMMON_H
