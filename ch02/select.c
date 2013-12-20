#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/time.h>

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("usage: select filename ...\n");
		exit(EXIT_FAILURE);
	}

	int fd[argc - 1];
	int fd_max = 0;

	for (int i = 1; i < argc; i++) {
		fd[i - 1] = open(argv[i], O_RDONLY);
		if (fd[i - 1] == -1) {
			fprintf(stderr, "%s: cannot open\n", argv[i]);
			perror("open");
			exit(EXIT_FAILURE);
		}
		if (fd[i - 1] > fd_max)
			fd_max = fd[i - 1];
	}

	fd_set readfds;
	FD_ZERO(&readfds);
	for (int i = 0; i < argc - 1; i++) {
		FD_SET(fd[i], &readfds);
	}
	struct timeval tv = {0, 0};

	int rc = select(fd_max + 1, &readfds, NULL, NULL, &tv);
	if (rc == -1) {
		perror("select");
		exit(EXIT_FAILURE);
	}
	printf("%d file(s) ready\n", rc);

	for (int i = 0; i < argc - 1; i++) {
		printf("%s (fd %d) is ", argv[i + 1], fd[i]);
		if (FD_ISSET(fd[i], &readfds))
			printf("ready\n");
		else
			printf("not ready\n");
	}

	for (int i = 0; i < argc - 1; i++) {
		if (close(fd[i]) == -1) {
			fprintf(stderr, "%s: cannot close\n", argv[i + 1]);
			perror("close");
		}
	}

	exit(EXIT_SUCCESS);
}
