#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>

int main() {
	printf("hello from fcloseall\n");
	int rc = fcloseall();
	
	if (rc)
		perror("fcloseall");

	printf("rc is %d\n", rc);

	exit(EXIT_SUCCESS);
}
