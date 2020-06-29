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
        PrintDejuggleHelp();
        exit(2);
    }

    int block_size;
    int init_block;
    int data_size;
    int fd_source;
    int fd_destination;
    int write_size;
    int next_position;
    int rem_file_size;
    int dej_pos;
    size_t file_size;
    char* source;
    char* destination;
    unsigned char* data;
    block data_block;

    init_block = atoi(argv[1]);
    source = argv[2];
    destination = argv[3];

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

    block_size = ReadSignature(fd_source);

    if (!block_size) {
        fprintf(stderr, "The source file is not a valid File Juggler file.\n");
        exit(12);
    }

    
    file_size = ReadFileSignature(fd_source);

    if (file_size < 1) {
        fprintf(stderr, "The source file is not a valid File Juggler file.\n");
        exit(13);
    }
    
    fd_destination = CreateFile(destination);

    if (fd_destination < 0) {
        fprintf(stderr, "Error creating file: %s\n", destination);
        exit(6);
    }

    data_size = block_size * 1024 * sizeof(char) - 4;
    data = malloc(data_size);

    next_position = init_block;
    rem_file_size = file_size;
    dej_pos = 0;

    while (next_position != -1) {
        data_block = ReadBlock(fd_source, block_size, init_block);
        memcpy(data, data_block.b_32.data, block_size * 1024 * sizeof(char) - 4);
        next_position = data_block.b_32.position;
        if (next_position != -1) {
            InvertData(data_size, data);
        } else {
            InvertData(file_size % data_size, data);
        }

        lseek(fd_destination, dej_pos, SEEK_SET);
        write_size = (rem_file_size > data_size) ? data_size : rem_file_size;
        write(fd_destination, data, write_size);
        dej_pos += data_size;
        rem_file_size -= write_size;
        init_block = data_block.b_32.position;
    }

    CloseFile(fd_source);
    CloseFile(fd_destination);

    if (rem_file_size) {
        fprintf(stderr, "Dejuggle error.\n");
        exit(20);
    } else {
        printf("Dejuggled file %s from juggled file %s.\n", destination, source);    
    }

    free(data);

    return 0;
}