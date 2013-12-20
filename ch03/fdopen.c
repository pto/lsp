#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("usage: fdopen <filename>\n");
		exit(EXIT_FAILURE);
	}
	
	int fd = open(argv[1], O_RDONLY);
	if (fd == -1) {
		perror("open");
		exit(EXIT_FAILURE);
	}

	FILE *stream = fdopen(fd, "r");
	if (!stream) {
		perror("fdopen");
		exit(EXIT_FAILURE);
	}

	if (fclose(stream)) {
		perror("fclose");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
