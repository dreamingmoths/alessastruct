#ifndef ALESSASTRUCT_TYPES_H
#define ALESSASTRUCT_TYPES_H

typedef enum bool {
    false,
    true,
} bool;

#ifndef _SYS_TYPES_H
typedef unsigned char u_char;
typedef unsigned short u_short;
typedef unsigned int u_int;
typedef unsigned long u_long;
#endif

typedef signed char s_char;

typedef int long128 __attribute__((mode(TI)));
typedef unsigned int u_long128 __attribute__((mode(TI)));

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE (!FALSE)
#endif

#ifndef NULL
#define NULL 0
#endif

#endif // ALESSASTRUCT_TYPES_H
