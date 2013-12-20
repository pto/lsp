#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("usage: lseek <filename> <offset>\n");
		exit(EXIT_FAILURE);
	}

	int fd = open(argv[1], O_WRONLY);
	if (fd == -1) {
		perror("open");
		exit(EXIT_FAILURE);
	}

	int offset = atoi(argv[2]);

	off_t pos = lseek(fd, offset, SEEK_END);
	if (pos == -1) {
		perror("lseek");
		exit(EXIT_FAILURE);
	}

	ssize_t nr = write(fd, "?\n", 2);
	if (nr == -1) {
		perror("write");
		exit(EXIT_FAILURE);
	}
	if (nr != 2) {
		fprintf(stderr, "wrote %zu characters\n", nr);
		exit(EXIT_FAILURE);
	}

	if (close(fd) == -1) {
		perror("close");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
