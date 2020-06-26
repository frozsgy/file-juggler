#ifndef FILE_JUGGLER_FILE_H
#define FILE_JUGGLER_FILE_H

#include <unistd.h>
#include <fcntl.h>
#include <stddef.h>

#include "blocks.h"

int OpenFile(const char* file_name);

int CreateFile(const char* file_name);

void CloseFile(int fd);

size_t GetFileSize(int fd);

#endif //FILE_JUGGLER_FILE_H
