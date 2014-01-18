#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("usage: fputs <filename>\n");
		exit(1);
	}

	FILE *stream = fopen(argv[1], "a");
	if (!stream) {
		perror("fopen");
		exit(1);
	}

	int rc = fputs("The ship is made of wood.\n", stream);
	if (rc == EOF) {
		perror("fputs");
		exit(1);
	}
   	printf("rc = %d\n", rc);

	if (fclose(stream) == EOF) {
		perror("fclose");
		exit(1);
	}
}
