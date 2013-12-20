#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define display(macro) printf(#macro " is %ld\n", (long)(macro))

int main() {

#ifdef _POSIX_SOURCE
	display(_POSIX_SOURCE);
#else
	printf("no _POSIX_SOURCE\n");
#endif

#ifdef _POSIX_C_SOURCE
	display(_POSIX_C_SOURCE);
#else
	printf("no _POSIX_C_SOURCE\n");
#endif

#ifdef _XOPEN_SOURCE
	display(_XOPEN_SOURCE);
#else
	printf("no _XOPEN_SOURCE\n");
#endif

#ifdef _BSD_SOURCE
	display(_BSD_SOURCE);
#else
	printf("no _BSD_SOURCE\n");
#endif

#ifdef _SVID_SOURCE
	display(_SVID_SOURCE);
#else
	printf("no _SVID_SOURCE\n");
#endif

#ifdef _GNU_SOURCE
	display(_GNU_SOURCE);
#else
	printf("no _GNU_SOURCE\n");
#endif

#ifdef __GNUC_STDC_INLINE__
	display(__GNUC_STDC_INLINE__);
#else
	printf("no __GNUC_STDC_INLINE__\n");
#endif

#ifdef __GCC_IEC_559
	display(__GCC_IEC_559);
#else
	printf("no __GCC_IEC_559\n");
#endif

#ifdef __GCC_IEC_559_COMPLEX
	display(__GCC_IEC_559_COMPLEX);
#else
	printf("no __GCC_IEC_559_COMPLEX\n");
#endif

	exit(EXIT_SUCCESS);
}
