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

int ReadSignature(int fd)
{
    signature s;
    lseek(fd, 0, SEEK_SET);
    read(fd, &s, sizeof(signature));
    if (strcmp(s.name, APP_NAME) == 0) {
        return s.block_size;
    } else {
        return 0;
    }
}

int WriteSignature(int fd, const char* name, int block_size, double version)
{
    int r;
    signature* s_block = calloc(1, sizeof(signature));
    s_block->block_size = block_size;
    s_block->version = version;
    strcpy(s_block->name, name);
    r = write(fd, s_block, sizeof(signature));
    free(s_block);
    return r;
}

size_t ReadFileSignature(int fd)
{
    file f;
    lseek(fd, sizeof(signature), SEEK_SET);
    read(fd, &f, sizeof(file));
    return f.size;
}

int WriteFileSignature(int fd, const char* name, unsigned long long size)
{
    int r;
    file* f_block = calloc(1, sizeof(file));
    strcpy(f_block->name, name);
    f_block->size = size;
    lseek(fd, sizeof(signature), SEEK_SET);
    r = write(fd, f_block, sizeof(file));
    free(f_block);
    return r;
}

block ReadBlock(int fd, int block_size, int offset)
{
    block r;
    int file_offset = sizeof(signature) + sizeof(file) + (offset * block_size * 1024 * sizeof(char));
    lseek(fd, file_offset, SEEK_SET);
    read(fd, &r, block_size * 1024 * sizeof(char));
    return r;
}

int WriteBlock(int fd, int block_size, int offset, block data)
{
    int file_offset = sizeof(signature) + sizeof(file) + (offset * block_size * 1024 * sizeof(char));
    lseek(fd, file_offset, SEEK_SET);
    return write(fd, &data, block_size * 1024 * sizeof(char));
}

void ReadSource(int fd, int data_size, int offset, unsigned char* data)
{
    unsigned long long file_offset = offset * data_size;
    lseek(fd, file_offset, SEEK_SET);
    read(fd, data, data_size);
}