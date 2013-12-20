#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("usage: fopen <filename>\n");
		exit(EXIT_FAILURE);
	}

	FILE *stream = fopen(argv[1], "r");
	if (!stream) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	printf("file is open\n");

	if (fclose(stream)) {
		perror("fclose");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
