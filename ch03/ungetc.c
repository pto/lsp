#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("usage: ungetc <filename>\n");
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

	printf("The character is %c\n", c);

	c = ungetc(c, stream);
	if (c == EOF) {
		perror("ungetc");
		exit(EXIT_FAILURE);
	}

	c = fgetc(stream);
	if (c == EOF) {
		perror("fgetc 2");
		exit(EXIT_FAILURE);
	}

	printf("The character is still %c\n", c);

	c = fgetc(stream);
	if (c == EOF) {
		perror("fgetc 3");
		exit(EXIT_FAILURE);
	}

	printf("The next character is %c\n", c);

	if (fclose(stream) == EOF) {
		perror("fclose");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
