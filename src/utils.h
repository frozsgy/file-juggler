#ifndef _JUGGLER_UTILS_H_
#define _JUGGLER_UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>
#include <time.h>

#include "blocks.h"


void PrintHelp();

int CheckBlockSize(int block_size);

int CalculateBlockCount(int block_size, size_t file_size);

int* GetBlockOrdering(int n);

#endif // _JUGGLER_UTILS_H_