#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

const char MESSAGE[] = "My ship is solid!\n";

void start_duration(struct timespec *start_time) {
	clock_gettime(CLOCK_MONOTONIC, start_time);
}

void end_duration(const struct timespec *start_time, const char *name) {
	struct timespec stop_time;
	clock_gettime(CLOCK_MONOTONIC, &stop_time);
	long long duration = (stop_time.tv_sec - (*start_time).tv_sec) *
	       1e9 + stop_time.tv_nsec - (*start_time).tv_nsec;
	fprintf(stderr, "%s duration: %12.9f sec\n", name, duration/1e9);
}	

int main(int argc, char *argv[]) {
	if (argc != 1 && argc != 2) {
		printf("usage: write [filename]\n");
		exit(EXIT_FAILURE);
	}

	int fd = STDOUT_FILENO;
	if (argc == 2) {
		fd = open(argv[1], O_WRONLY | O_CREAT | O_EXCL,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		if (fd == -1) {
			perror("creat");
			exit(EXIT_FAILURE);
		}
	}

	struct timespec start;
	start_duration(&start);

	size_t len = sizeof(MESSAGE) - 1;
	void *buf = &MESSAGE;
	ssize_t ret;
        while (len > 0 && (ret = write(fd, buf, len)) != 0) {
		if (ret == -1) {
			if (errno == EINTR)
				continue;
			perror("write");
			exit(EXIT_FAILURE);
		}
		len -= ret;
		buf += ret;
	}

	end_duration(&start, "write");

	start_duration(&start);
	int r = fsync(fd);
	if (r == -1) {
		if (errno == EINVAL) {
			if (fdatasync(fd) == -1) {
				perror("fdatasync");
				exit(EXIT_FAILURE);
			}
		} else {
			perror("fsync");
			exit(EXIT_FAILURE);
		}
	}
	end_duration(&start, "fsync");

	start_duration(&start);
	sync();
	end_duration(&start, "sync");

	start_duration(&start);
	if (close(fd) == -1)
		perror("close");
	end_duration(&start, "close");

	return(EXIT_SUCCESS);
}
