#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("usage: fgets <filename>\n");
		exit(EXIT_FAILURE);
	}

	FILE *stream = fopen(argv[1], "r");
	if (!stream) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	char buffer[LINE_MAX];
	if (!fgets(buffer, LINE_MAX, stream)) {
		perror("fgets");
		exit(EXIT_FAILURE);
	}

	printf("The line is: %s", buffer);
	
	if (fclose(stream) == EOF) {
		perror("fclose");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
