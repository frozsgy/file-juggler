#include "utils.h"

void PrintHelp()
{
    printf("usage: ./juggle block-size file-to-juggled new-name\n");
}

int CheckBlockSize(int block_size)
{
    switch(block_size) {
        case 1:
        case 2:
        case 4:
        case 8:
        case 16:
            return 1;
            break;
        default:
            return 0;
            break;
    }
}

int CalculateBlockCount(int block_size, size_t file_size)
{
    int data_per_block = block_size * 1024 - 4;
    float block_count = ceil(file_size / (double) data_per_block);
    return (int) block_count;
}