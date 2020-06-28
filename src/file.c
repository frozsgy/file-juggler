#include "file.h"


int OpenFile(const char* file_name)
{
    int fd;
    fd = open(file_name, O_RDONLY);
    return fd;
}

int CreateFile(const char* file_name)
{
    int fd;
    fd = creat(file_name, S_IRWXU);
    return fd;
}

void CloseFile(int fd)
{
    close(fd);
}

size_t GetFileSize(int fd)
{
    size_t size = lseek(fd, 0, SEEK_END);
    return size;
}

int WriteSignature(int fd, const char* name, int year, double version)
{
    signature s_block = {"", year, version};
    strcpy(s_block.name, name);
    return write(fd, &s_block, sizeof(signature));
}

block ReadBlock(int fd, int block_size, int offset)
{
    block r;
    int file_offset = sizeof(signature) + (offset * block_size * 1024 * sizeof(char));
    lseek(fd, file_offset, SEEK_SET);
    read(fd, &r, block_size * 1024 * sizeof(char));
    return r;
}

int WriteBlock(int fd, int block_size, int offset, block data)
{
    int file_offset = sizeof(signature) + (offset * block_size * 1024 * sizeof(char));
    lseek(fd, file_offset, SEEK_SET);
    return write(fd, &data, block_size * 1024 * sizeof(char));
}