#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>

#include "def.h"
#include "blocks.h"
#include "utils.h"
#include "file.h"

int main(int argc, char** argv)
{
    if (argc != 4) {
        PrintJuggleHelp();
        exit(2);
    }

    int block_size;
    int data_size;
    int fd_source;
    int fd_destination;
    int block_count;
    int next_position;
    size_t file_size;
    int* block_list;
    int* block_map;
    char* source;
    char* destination;
    unsigned char* data;
    block data_block;

    block_size = atoi(argv[1]);
    source = argv[2];
    destination = argv[3];

    if (!CheckBlockSize(block_size)) {
        fprintf(stderr, "Block size can be one of the following: 1KB, 2KB, 4KB, 8KB, 16KB.\n");
        exit(3);
    }

    fd_source = OpenFile(source);

    if (fd_source < 0) {
        fprintf(stderr, "File %s cannot be read.\n", source);
        exit(4);
    }

    file_size = GetFileSize(fd_source);

    if (file_size <= 0) {
        fprintf(stderr, "The source file has an invalid size.\n");
        exit(5);
    }

    fd_destination = CreateFile(destination);

    if (fd_destination < 0) {
        fprintf(stderr, "Error creating file: %s\n", destination);
        exit(6);
    }

    if (WriteSignature(fd_destination, APP_NAME, block_size, VERSION) < sizeof(signature)) {
        fprintf(stderr, "Error writing to file: %s\n", destination);
        exit(7);
    }

    if (WriteFileSignature(fd_destination, source, file_size) < sizeof(file)) {
        fprintf(stderr, "Error writing to file: %s\n", destination);
        exit(8);
    }

    block_count = CalculateBlockCount(block_size, file_size);

    block_list = GetBlockOrdering(block_count);
    block_map = malloc(sizeof(int) * block_count);
    for (int i = 0; i < block_count; i++) {
        block_map[block_list[i]] = i;
    }

    data_size = block_size * 1024 * sizeof(char) - 4;
    data = malloc(data_size);

    for (int i = 0; i < block_count; i++) {
        ReadSource(fd_source, data_size, block_list[i], data);
        next_position = (block_list[i] + 1 == block_count) ? -1 : block_map[block_list[i] + 1];
        data_block.b_32.position = next_position;
        if (next_position != -1) {
            InvertData(data_size, data);
        } else {
            InvertData(file_size % data_size, data);
        }
        memcpy(data_block.b_32.data, data, block_size * 1024 * sizeof(char) - 4);
        WriteBlock(fd_destination, block_size, i, data_block);
    }

    CloseFile(fd_source);
    CloseFile(fd_destination);

    printf("Juggled file %s with block size %dKB from original file %s has been created succesfully.\n", destination, block_size, source);
    printf("--- SAVE THIS INFO --- \n");
    printf("Starting block number: %d\n", block_map[0]);

    free(block_list);
    free(block_map);
    free(data);

    return 0;
}