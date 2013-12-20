#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("usage: pselect delay-in-seconds\n");
		exit(EXIT_FAILURE);
	}

	struct timespec ts;
	ts.tv_sec = atoi(argv[1]);
	ts.tv_nsec = 0;

	fd_set readfds;
	FD_ZERO(&readfds);
	FD_SET(STDIN_FILENO, &readfds);

	int ret = pselect(STDIN_FILENO + 1, &readfds, NULL, NULL, &ts, NULL);
	if (ret == -1) {
		perror("pselect");
		exit(EXIT_FAILURE);
	}
	if (!ret) {
		printf("%ld seconds elapsed with no input\n", ts.tv_nsec);
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
