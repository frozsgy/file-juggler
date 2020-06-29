#include "utils.h"

void PrintJuggleHelp()
{
    printf("usage: ./juggler block-size file-to-juggled new-name\n");
}

void PrintDejuggleHelp()
{
    printf("usage: ./dejuggler first-block-id file-to-dejuggled new-name\n");
}

int CheckBlockSize(int block_size)
{
    switch(block_size) {
        case 1:
        case 2:
        case 4:
        case 8:
        case 16:
        case 32:
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

int* GetBlockOrdering(int n)
{
    int* r = malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        r[i] = i;
    }

    srand(time(NULL));

    for (int i = n-1; i > 0; i--) {
        int j = rand() % (i + 1);
        int k = r[i];
        r[i] = r[j];
        r[j] = k;
    }

    return r;
}

void InvertData(int data_size, unsigned char* data)
{
    for (int i = 0; i < data_size; i++) {
        data[i] = ~data[i];
    }
}