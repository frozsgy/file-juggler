#ifndef FILE_JUGGLER_BLOCKS_H
#define FILE_JUGGLER_BLOCKS_H

typedef struct block_1kb {
	unsigned int position;
	unsigned char data[1020];
} block_1kb;

typedef struct block_2kb {
	unsigned int position;
	unsigned char data[2044];
} block_2kb;

typedef struct block_4kb {
	unsigned int position;
	unsigned char data[4092];
} block_4kb;

typedef struct block_8kb {
	unsigned int position;
	unsigned char data[8188];
} block_8kb;

typedef struct block_16kb {
	unsigned int position;
	unsigned char data[16380];
} block_16kb;

typedef struct block_32kb {
	unsigned int position;
	unsigned char data[32764];
} block_32kb;

typedef union block {
    block_1kb b_1;
    block_2kb b_2;
    block_4kb b_4;
    block_8kb b_8;
    block_16kb b_16;
} block;

#endif // FILE_JUGGLER_BLOCKS_H