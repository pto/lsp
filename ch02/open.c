#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
	int fd;
	fd = open("madagascar", O_WRONLY | O_CREAT | O_TRUNC,
		       	S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd == -1) {
		perror("open");
		exit(EXIT_FAILURE);
	}
	printf("fd is %d\n", fd);
	return EXIT_SUCCESS;
}
