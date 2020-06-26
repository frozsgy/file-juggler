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