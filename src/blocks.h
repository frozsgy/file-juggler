#ifndef FILE_JUGGLER_BLOCKS_H
#define FILE_JUGGLER_BLOCKS_H

typedef struct block_1kb {
    int position;
    unsigned char data[1020];
} block_1kb;

typedef struct block_2kb {
    int position;
    unsigned char data[2044];
} block_2kb;

typedef struct block_4kb {
    int position;
    unsigned char data[4092];
} block_4kb;

typedef struct block_8kb {
    int position;
    unsigned char data[8188];
} block_8kb;

typedef struct block_16kb {
    int position;
    unsigned char data[16380];
} block_16kb;

typedef struct block_32kb {
    int position;
    unsigned char data[32764];
} block_32kb;

typedef union block {
    block_1kb b_1;
    block_2kb b_2;
    block_4kb b_4;
    block_8kb b_8;
    block_16kb b_16;
    block_32kb b_32;
} block;

/**
 * 32 byte block to add at the beginning of each juggled file
 */
typedef struct signature {
    char name[16];
    unsigned int block_size;
    double version;
} signature;

typedef struct file {
    char name[256];
    size_t size;
} file;

#endif // FILE_JUGGLER_BLOCKS_H