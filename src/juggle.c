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
#define YEAR GetYear()

int main(int argc, char** argv)
{
	if (argc != 4) {
		PrintHelp();
		exit(2);
	}

	int block_size;
	int fd_source;
	int fd_destination;
	size_t file_size;
	char* source;
	char* destination;

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

	if (WriteSignature(fd_destination, APP_NAME, YEAR, VERSION) < sizeof(signature)) {
		fprintf(stderr, "Error writing to file: %s\n", destination);
        exit(7);
	}

	printf("i will use %d many blocks. the file size was %lu\n", CalculateBlockCount(block_size, file_size), file_size);


	return 0;
}