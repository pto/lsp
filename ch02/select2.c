#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("usage: select2 daly-in-seconds\n");
		exit(EXIT_FAILURE);
	}

	struct timeval tv;
	tv.tv_sec = atoi(argv[1]);
	tv.tv_usec = 0;

	fd_set readfds;
	FD_ZERO(&readfds);
	FD_SET(STDIN_FILENO, &readfds);

	int ret = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &tv);
	if (ret == -1) {
		perror("select");
		exit(EXIT_FAILURE);
	}
	if (!ret) {
		printf("%d seconds elapsed with no input\n", atoi(argv[1]));
		exit(EXIT_SUCCESS);
	}

	char buf[BUFSIZ + 1];
	int len = read(STDIN_FILENO, buf, BUFSIZ);
	if (len == -1) {
		perror("read");
		exit(EXIT_FAILURE);
	}
	if (len) {
		buf[len] = '\0';
		printf("read: %s", buf);
	}

	exit(EXIT_SUCCESS);
}
