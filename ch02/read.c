#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const size_t CHARACTERS = 5;

int main(int argc, char *argv[]) {
	if (argc != 1 && argc != 2) {
		printf("usage: read [filename]\n");
		exit(EXIT_FAILURE);
	}

	int fd;
	if (argc == 1) {
		fd = STDIN_FILENO;
	} else {
		fd = open(argv[1], O_RDONLY | O_NONBLOCK);
		if (fd == -1) {
			perror("open");
			exit(EXIT_FAILURE);
		}
	}

	char buf[CHARACTERS + 1];
	char *pbuf = buf;
	size_t len = CHARACTERS;
	ssize_t ret;

	while (len != 0 && (ret = read(fd, pbuf, len)) != 0) {
		if (ret == -1) {
			if (errno == EINTR)
				continue;
			if (errno == EAGAIN) {
				printf("waiting...\n");
				sleep(2);
				continue;
			}
			perror("read");
			break;
		}
		len -= ret;
		pbuf += ret;
	}
	if (len == 0) {
		buf[CHARACTERS] = '\0';
		printf("First %zu characters: %s\n", CHARACTERS, buf);
		exit(EXIT_SUCCESS);
	} else {
		buf[CHARACTERS - len] = '\0';
		printf("Got %zu characters: %s\n", CHARACTERS - len, buf);
		exit(EXIT_FAILURE);
	}
}
