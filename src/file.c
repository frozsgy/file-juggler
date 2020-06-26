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
