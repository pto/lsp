#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
	int fd = creat("bermuda", S_IRUSR | S_IWUSR);
	if (fd == -1) {
		perror("creat");
		exit(EXIT_FAILURE);
	}
	printf("fd is %d\n", fd);

	exit(EXIT_SUCCESS);
}
