typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned char  uchar;
typedef uint pde_t;
typedef struct __lock_ {
    int ticket;
    int turn;
} lock_t;
