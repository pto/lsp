#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("usage: trumcate <filename> <length>\n");
		exit(EXIT_FAILURE);
	}

	off_t length = atol(argv[2]);

	int rc = truncate(argv[1], length);
	if (rc == -1) {
		perror("truncate");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
