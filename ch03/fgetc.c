#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("usage: fgetc <filename>\n");
		exit(EXIT_FAILURE);
	}

	FILE *stream = fopen(argv[1], "r");
	if (!stream) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	int c = fgetc(stream);
	if (c == EOF) {
		perror("fgetc");
		exit(EXIT_FAILURE);
	}

	printf("c is %c\n", (char)c);

	exit(EXIT_SUCCESS);
}
