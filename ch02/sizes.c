#include <stdio.h>
#include <limits.h>

#define size(type) printf("sizeof(" #type ") is %zu\n", sizeof(type))

int main() {	
	size(int);
	size(size_t);
	size(ssize_t);
	size(off_t);
	size(long);
	size(long long);
	size(float);
	size(double);
	size(long double);
	size(void *);

	printf("BUFSIZ is %d\n", BUFSIZ);
	printf("LINE_MAX is %d\n", LINE_MAX);

	return 0;
}
