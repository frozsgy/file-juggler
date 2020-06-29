#ifndef FILE_JUGGLER_FILE_H
#define FILE_JUGGLER_FILE_H

#include <unistd.h>
#include <fcntl.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

#include "blocks.h"

int OpenFile(const char* file_name);

int CreateFile(const char* file_name);

void CloseFile(int fd);

size_t GetFileSize(int fd);

int WriteSignature(int fd, const char* name, int block_size, double version);

int WriteName(int fd, const char* name);

block ReadBlock(int fd, int block_size, int offset);

int WriteBlock(int fd, int block_size, int offset, block data);

void ReadSource(int fd, int data_size, int offset, unsigned char* data);

#endif //FILE_JUGGLER_FILE_H
