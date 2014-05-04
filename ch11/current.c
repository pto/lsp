#include <time.h>
#include <sys/time.h>
#include <stdio.h>

clockid_t clocks[] = {
	CLOCK_REALTIME,
	CLOCK_MONOTONIC,
	CLOCK_PROCESS_CPUTIME_ID,
	CLOCK_THREAD_CPUTIME_ID,
	CLOCK_MONOTONIC_RAW,
	(clockid_t)-1
};

main() {
	time_t t;
	struct timeval tv;
	int ret, i;

	printf("current time: %ld\n", (long)time(&t));
	printf("the same value: %ld\n", (long)t);

	ret = gettimeofday(&tv, NULL);
	if (ret)
		perror("gettimeofday");
	else
		printf("seconds=%ld useconds=%ld\n", (long)tv.tv_sec, (long)tv.tv_usec);

	for (i = 0; clocks[i] != (clockid_t)-1; i++) {
		struct timespec ts;
		int ret;

		ret = clock_gettime(clocks[i], &ts);
		if (ret)
			perror("clock_gettime");
		else
			printf("clock=%d sec=%ld nsec=%ld\n",
					clocks[i], ts.tv_sec, ts.tv_nsec);
	}
}
