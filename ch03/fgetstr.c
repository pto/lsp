#include <stdio.h>
#include <stdlib.h>

char *fgetstr(char *str, int size, FILE *stream, int delimiter);

int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("usage: fgetstr <filename>\n");
		exit(EXIT_FAILURE);
	}

	FILE *stream = fopen(argv[1], "r");
	if (!stream) {
		perror("fopen");
		exit(EXIT_FAILURE);
	}

	char buf[BUFSIZ];
	char *ret = fgetstr(buf, BUFSIZ, stream, '\n');
	if (!ret) {
		perror("fgetstr");
		exit(EXIT_FAILURE);
	}

	printf("buf == ret is %d\n", buf == ret);
	printf("The string is: %s\n", buf);
	exit(EXIT_SUCCESS);
}

char *fgetstr(char *str, int size, FILE *stream, int delimiter)
{
	char *s = str;
	int c = 0;
	while (--size > 0 && (c = fgetc(stream)) != EOF && (*s++ = c) != delimiter)
		;
	if (c == delimiter)
		*--s = '\0';
	else
		*s = '\0';
	if (c == EOF && s == str)
		return NULL;
	else
		return str;
}
