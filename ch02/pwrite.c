#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("usage: pwrite <filename>\n");
		exit(EXIT_FAILURE);
	}

	int fd = open(argv[1], O_WRONLY);
	if (fd == -1) {
		perror("open");
		exit(EXIT_FAILURE);
	}

	ssize_t count = pwrite(fd, "t", 1, 6);
	if (count == -1) {
		perror("pwrite");
		exit(EXIT_FAILURE);
	}
	if (count != 1) {
		printf("pwrite: warning: wrote %ld characters\n", count);
		exit(EXIT_FAILURE);
	}

	if (close(fd) != 0) {
		perror("close");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
