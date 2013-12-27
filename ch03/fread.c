#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if (argc != 3) {
		printf("usage: fread <filename> <count>\n");
		exit(EXIT_FAILURE);
	}

	FILE *stream = fopen(argv[1], "r");
	if (!stream) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	int count = atoi(argv[2]);
	if (count <= 0) {
		fprintf(stderr, "fread: invalid count %s\n", argv[2]);
		exit(EXIT_FAILURE);
	}

	int buf[count];
	size_t nr = fread(buf, sizeof(int), count, stream);

	printf("Number of integers read: %lu\n", (long)nr);
	for (unsigned int i = 0; i < nr; i++)
		printf("   %d\n", buf[i]);

	exit(EXIT_SUCCESS);
}
