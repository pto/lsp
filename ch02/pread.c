#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const off_t START = 11;
const ssize_t COUNT = 5;

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("usage: pread <filename>\n");
		exit(EXIT_FAILURE);
	}

	int fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		perror("open");
		exit(EXIT_FAILURE);
	}

	char buf[COUNT + 1];
	ssize_t count = pread(fd, buf, COUNT, START);
	if (count == -1) {
		perror("pread");
		exit(EXIT_FAILURE);
	}
	if (count != COUNT) {
		printf("pread: warning: only read %ld characters\n", (long)count);
	}
	buf[count] = '\0';

	printf("result: %s\n", buf);

	count = read(fd, buf, COUNT);
	if (count == -1) {
		perror("read");
		exit(EXIT_FAILURE);
	}
	if (count != COUNT) {
		printf("pread: warning: only read %ld characters\n", (long)count);
	}
	buf[count] = '\0';

	printf("file position is zero: %s\n", buf);

	exit(EXIT_SUCCESS);
}
