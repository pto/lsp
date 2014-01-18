#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("usage: fputs <filename>\n");
		exit(EXIT_FAILURE);
	}

	FILE *stream = fopen(argv[1], "a");
	if (!stream) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	int rc = fputs("The ship is made of wood.\n", stream);
	if (rc == EOF) {
		perror("fputs");
		exit(EXIT_FAILURE);
	}
   	printf("rc = %d\n", rc);

	if (fclose(stream) == EOF) {
		perror("fclose");
		exit(EXIT_FAILURE);
	}

	exit(EXIT_SUCCESS);
}
