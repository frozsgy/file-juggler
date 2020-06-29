#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>

#include "blocks.h"
#include "utils.h"
#include "file.h"

#define APP_NAME "file_juggler"
#define VERSION 0.1

int main(int argc, char** argv)
{
    if (argc != 4) {
        PrintHelp();
        exit(2);
    }

    int block_size;
    int data_size;
    int fd_source;
    int fd_destination;
    int block_count;
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

    if (WriteName(fd_destination, source) < sizeof(file_name)) {
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
        int next_position = (block_list[i] + 1 == block_count) ? -1 : block_map[block_list[i] + 1];
        data_block.b_32.position = next_position;
        memcpy(data_block.b_32.data, data, block_size * 1024 * sizeof(char) - 4);
        WriteBlock(fd_destination, block_size, i, data_block);
    }

    /* TESTING READ */ 

    CloseFile(fd_destination);

    fd_destination = OpenFile(destination);
    int fd_new = CreateFile("test-unjuggle");
    int fd_new_offset = 0;
    int bytes = 0;
    int start_pos = block_map[0];
    int rem_file_size = file_size;

    while (start_pos != -1) {
        block tr = ReadBlock(fd_destination, block_size, start_pos);
        for (int j = 0; j < data_size; j++) {
            bytes++;
            //printf("%c", tr.b_32.data[j]);    
            if (bytes == file_size) break;
        }        


        lseek(fd_new, fd_new_offset, SEEK_SET);
        int write_size = (rem_file_size > data_size) ? data_size : rem_file_size;
        printf("file size: %d\nwrite size: %d\n\n", rem_file_size, write_size);
        write(fd_new, tr.b_32.data, write_size);
        fd_new_offset += data_size;
        rem_file_size -= write_size;

        
        start_pos = tr.b_32.position;
    }

    /* READ WRITE TEST ENDED */

    free(block_list);
    free(block_map);
    free(data);

    return 0;
}