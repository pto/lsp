#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	struct pirate {
		char name[100];
		unsigned long booty;
		unsigned int beard_len;
	} p, blackbeard = { "Edward Teach", 950, 48 };

	FILE *out = fopen("data", "w");
	if (!out) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	int rc = fwrite(&blackbeard, sizeof(struct pirate), 1, out);
	if (!rc) {
		perror("fwrite");
		exit(EXIT_FAILURE);
	}
	printf("fwrite rc = %d\n", rc);

	if (fclose(out)) {
		perror("fclose");
		exit(EXIT_FAILURE);
	}

	FILE *in = fopen("data", "r");
	if (!in) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	rc = fread(&p, sizeof(struct pirate), 1, in);
	if (!rc) {
		perror("fread");
		exit(EXIT_FAILURE);
	}
	printf("fread rc = %d\n", rc);

	if (fclose(in)) {
		perror("fclose");
		exit(EXIT_FAILURE);
	}
	printf("name = \"%s\", booty = %lu, beard_len = %u\n",
			p.name, p.booty, p.beard_len);

	exit(EXIT_SUCCESS);
}
